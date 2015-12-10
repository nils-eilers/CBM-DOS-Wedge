; Resident part of the universal DOS wedge
;----------------------------------------------------------------------------

	wedge_unit	= $73		; default device, unused byte in CHRGET
	wedge_char	= $b3		; 0 if @># else load/run char / ^


	inc TXTPTR				; increment text pointer
	bne :+
	inc TXTPTR + 1
:

; if MAINS is stacked, CHRGET is called from direct mode
; abort if not called from there
	stx wedge_char		; save X
	tsx
	lda $101,x
	cmp #<MAINS
	bne restabort
	lda $102,x
	cmp #>MAINS
	bne restabort
; abort if textpointer doesn't point to $0200
	lda TXTPTR
	bne abort
	lda TXTPTR + 1
	cmp #2
	bne abort

	ldy #0				; NUL when @>#
	sty wedge_char		; else load/run character /^

testchar:
	lda (TXTPTR),y
	cmp #' '			; skip leading spaces
	bne nospace
	inc TXTPTR
	bne testchar
nospace:
	cmp #'>'			; '>'
	beq command_or_status
	cmp #'@'			; '@'
	beq command_or_status
	cmp #'#'			; '#'
	beq default_device
	iny
	sta wedge_char		; save load/run character
	cmp #'/'			; '/'
	beq to_prepare_fn
	cmp #'^'			; '^'
	beq to_prepare_fn
	bne abort

restabort:
	ldx wedge_char		; restore X
abort:
	jmp CHRGOT

;----------------------------------------------------------------------------
syntax_err: 		jmp SYNERR
illegal_qty_err: 	jmp IQERR
;----------------------------------------------------------------------------

command_or_status:
	iny
	lda (TXTPTR),y
	beq get_status
	cmp #'$'			; '$'
	beq prepare_fn
	bne send_cmd

;----------------------------------------------------------------------------
; SET DEVICE
;----------------------------------------------------------------------------
default_device:
	inc TXTPTR
	lda (TXTPTR),y		; Y is still 0
	bne set_device			; parameter given -> set device number

	ldx wedge_unit		; show current device number
	tya
	jsr INTOUT
	jsr CRLF
	jmp READY

set_device:
	cmp #'0'			; numeric parameter?
	bcc syntax_err
	cmp #('9' + 1)
	bcs syntax_err
	; prerequsites for RDINT:
	; - TXTPTR $77/$78 point to first char
	; - A contains that first char
	; - Carry is cleared
	clc
	jsr RDINT			; convert string to unsigned int
	lda LINNUM			; LSB of converted number
	cmp #4
	bcc illegal_qty_err
	cmp #(30 + 1)
	bcs illegal_qty_err
	sta wedge_unit
	jmp READY

;----------------------------------------------------------------------------
; SEND COMMAND
;----------------------------------------------------------------------------
	send_cmd:
	lda wedge_unit
	sta DN
	lda #$6f			; DATA SA 15
	sta SA
	jsr LISTN			; LISTEN
	lda SA
	jsr SECND			; send secondary address

@nextchar:
	inc TXTPTR
	ldy #0
	lda (TXTPTR),y
	beq @done
	jsr CIOUT			; send char to IEEE
	clv
	bvc @nextchar		; branch always

@done:
	jsr UNLSN

;	jmp READY
	clc
	bcc get_status

;----------------------------------------------------------------------------
; 6502 wasn't made for writing relative code :(
to_prepare_fn:	beq		prepare_fn

;----------------------------------------------------------------------------
; GET STATUS
;----------------------------------------------------------------------------
get_status:
	sty TXTPTR
	lda wedge_unit
	sta DN
	jsr TALK			; TALK
	lda #$6f			; DATA SA 15
	sta SA
	jsr SECND			; send secondary address

@nextchar:
	jsr ACPTR			; read byte from IEEE bus
	cmp #CR				; last byte = CR?
	beq @done
	jsr SCROUT			; write char to screen
	clv
	bvc @nextchar		; branch always

@done:
	jsr SCROUT			; write char to screen
	jsr UNTLK			; UNTALK
	jmp READY

;----------------------------------------------------------------------------
; TODO: if we have quotes in our string, then they should handled here
prepare_fn:
	iny				; count filename length
	lda (TXTPTR),y
	bne prepare_fn
	dey
	sty FNLEN			; store length
	ldx TXTPTR
	inx
	stx FNADR
	lda TXTPTR + 1
	sta FNADR + 1
	lda wedge_unit
	sta DN
	lda wedge_char		; load/run?
	bne to_loadrun		; yes
;----------------------------------------------------------------------------
; DIRECTORY
;----------------------------------------------------------------------------
	lda #0
	sta STATUS
	lda #$60			; DATA SA 0
	sta SA
	jsr OPENI			; open file
	jsr TALK
	lda SA
	jsr SECND

	ldy #3
list_blocks:
	sty FNLEN
	jsr ACPTR
	sta MEMUSS			; store blocks LSB
	ldy STATUS
	bne to_stoplisting
	jsr ACPTR
	sta MEMUSS + 1		; store blocks MSB
	ldy STATUS
	bne to_stoplisting
	ldy FNLEN
	dey
	bne list_blocks
	ldx MEMUSS
	lda MEMUSS + 1
	jsr INTOUT			; write #blocks to screen
	lda #' '
	bne listing			; branch always

;----------------------------------------------------------------------------
; 6502 wasn't made for writing relative code :(
to_loadrun:	bne loadrun
to_stoplisting:	bne stoplisting
to_list_blocks:	bne list_blocks
;----------------------------------------------------------------------------

listing:
	jsr SCROUT
@next:	jsr ACPTR			; read byte from IEEE
	ldx STATUS
	bne stoplisting
	cmp #0
	beq newline
	jsr SCROUT			; write filename and type
	jsr STOPEQ			; abort listing with STOP key
	beq stoplisting
	jsr GETIN			; pause listing with SPACE key
	beq @next			; no key pressed -> continue
	cmp #' '			; =space?
	bne @next			; only space pauses listing
:	jsr GETIN
	beq :-				; wait for any key
	bne @next			; then continue

newline:
	lda #CR
	jsr SCROUT
	ldy #2
	bne to_list_blocks

stoplisting:
	jsr CLSEI			; close file with $E0, unlisten
	jsr CRLF
	pla
	pla
	jmp READY			; BASIC warm start
;----------------------------------------------------------------------------
; LOAD / RUN
;----------------------------------------------------------------------------
loadrun:
	lda #0
	sta STATUS
	sta LVFLAG			; LOAD=0, VERIFY=1
	jsr LOADOP			; LOAD without pointer change
	lda STATUS
	and #$10
	bne loaderr

	.if BASIC=1
; Fix for first original BASIC PET with BASIC 1 -04 ROMs needed:
; Increment end of BASIC pointer by one (EAL)
; Refer to COMPUTE! ISSUE 23 / APRIL 1982 / PAGE 135
; http://www.atarimagazines.com/compute/issue23/057_1_The_Bug_In_The_Universal_Wedge.php
	lda $f384			; check if we have BASIC 1 -04 ROM set
	bmi @dontfix
	inc EAL
	bne @dontfix
	inc EAL+1
@dontfix:
	.endif

	; VARTAB = EAL
	lda EAL+1			; end of program MSB
	sta VARTAB+1			; start of basic variables MSB
	lda EAL				; end of program LSB
	sta VARTAB			; start of basic variables LSB

	jsr CRLF
	jsr RSTXCLR			; reset TXTPTR and perform CLR
	jsr LINKPRG			; rebuild chaining of BASIC lines
	lda wedge_char
	cmp #'/'			; if '/' then load only, omit RUN
	bne startprg			; '^' --> RUN
	jmp READY			; load only, exit with BASIC warm start
startprg:
	jsr STXTPT			; reset TXTPTR
	jmp NEWSTT			; RUN
loaderr:
	jmp FILENOTFOUND		; FILE NOT FOUND, return to basic

