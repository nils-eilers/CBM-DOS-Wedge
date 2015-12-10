; Universal Wedge for BASIC 2 and BASIC 4
; Based on Commodore's universal wedge taken from 8050's test/demo disk
; but rewritten and enhanced by Nils Eilers
;----------------------------------------------------------------------------
	.listbytes unlimited
	.code

;----------------------------------------------------------------------------
	.include "starter.inc"		; embedd following lines in BASIC prg
	.include "detectbasic.inc" 	; --> jumps to appropiate target NOW
;----------------------------------------------------------------------------
	.include "6502.inc"		; general 6502 macros
	.include "pet.inc"		; common definitions for BASIC 2+4
	.include "stroutz.inc"		; working stroutz

;----------------------------------------------------------------------------
; ZP ADDRESSES / ROM ENTRY POINTS
;----------------------------------------------------------------------------
	B2_MOVBLK	= $c2df		; BASIC 2 block move
	B2_INTOUT	= $dcd9

	B4_MOVBLK	= $b357		; BASIC 4 block move
	B4_INTOUT	= $cf83

;----------------------------------------------------------------------------
; VARIABLES
;----------------------------------------------------------------------------
	size		= $d1

;----------------------------------------------------------------------------
; BASIC 1: UNSUPPORTED
;----------------------------------------------------------------------------
basic1:
	lday hello
	jsr STROUTZ

	lday detb1
	jsr STROUTZ
	rts

;----------------------------------------------------------------------------
; INSTALL BASIC 2 WEDGE
;----------------------------------------------------------------------------
basic2:
	lday hello			; say hello
	jsr STROUTZ

	lday detb2			; write which basic was detected
	jsr STROUTZ

	sec				; compute size of resident wedge
	lda #<b2wendplus1		; size = b4wendplus1 - b4wstart
	sbc #<b2wstart
	sta size
	lda #>b2wendplus1
	sbc #>b2wstart
	sta size+1

        lda #<b2wstart			; source start
        sta MOVSRC
        lda #>b2wstart
        sta MOVSRC+1
        lda #<b2wendplus1		; source end plus 1
        sta MOVSEND
        lda #>b2wendplus1
        sta MOVSEND+1
	lda MEMSIZ			; target end plus 1
	sta MOVTEND
	lda MEMSIZ+1
	sta MOVTEND+1
        jsr B2_MOVBLK			; move resident wedge to upper memory

	sec				; decrease MEMSIZ by size bytes
	lda MEMSIZ			; and patch CHRGET JMP address
	sbc size			; to jump into wedge
	sta MEMSIZ
	sta CHRGET+1
	lda MEMSIZ+1
	sbc size+1
	sta MEMSIZ+1
	sta CHRGET+2
	lda #$4c			; insert JMP command in CHRGET routine
	sta CHRGET

	lda #8				; init default device
	sta $73				; (unused byte in CHRGET)

	lday msg_inst			; write "wedge installed"
	jsr STROUTZ
	lday msg_mem0			; write
	jsr STROUTZ			; "memsize decreased by SIZE bytes"
	ldx size
	lda size+1
	jsr B2_INTOUT
	lday msg_mem1
	jsr STROUTZ

	rts				; exit to BASIC



;----------------------------------------------------------------------------
; INSTALL BASIC 4 WEDGE
;----------------------------------------------------------------------------
basic4:
	lday hello			; say hello
	jsr STROUTZ

	lday detb4			; write which basic was detected
	jsr STROUTZ

	sec				; compute size of resident wedge
	lda #<b4wendplus1		; size = b4wendplus1 - b4wstart
	sbc #<b4wstart
	sta size
	lda #>b4wendplus1
	sbc #>b4wstart
	sta size+1

        lda #<b4wstart			; source start
        sta MOVSRC
        lda #>b4wstart
        sta MOVSRC+1
        lda #<b4wendplus1		; source end plus 1
        sta MOVSEND
        lda #>b4wendplus1
        sta MOVSEND+1
	lda MEMSIZ			; target end plus 1
	sta MOVTEND
	lda MEMSIZ+1
	sta MOVTEND+1
        jsr B4_MOVBLK			; move resident wedge to upper memory

	sec				; decrease MEMSIZ by size bytes
	lda MEMSIZ			; and patch CHRGET JMP address
	sbc size			; to jump into wedge
	sta MEMSIZ
	sta CHRGET+1
	lda MEMSIZ+1
	sbc size+1
	sta MEMSIZ+1
	sta CHRGET+2
	lda #$4c			; insert JMP command in CHRGET routine
	sta CHRGET

	lda #8				; init default device
	sta $73				; (unused byte in CHRGET)

	lday msg_inst			; write "wedge installed"
	jsr STROUTZ
	lday msg_mem0			; write
	jsr STROUTZ			; "memsize decreased by SIZE bytes"
	ldx size
	lda size+1
	jsr B4_INTOUT
	lday msg_mem1
	jsr STROUTZ

	rts				; exit to BASIC

;----------------------------------------------------------------------------
; UNKNOWN BASIC VERSION, ABORT
;----------------------------------------------------------------------------
basicunknown:
	lday hello
	jsr STROUTZ

	lday detunknown
	jsr STROUTZ
	rts


;----------------------------------------------------------------------------
; STRING CONSTANTS
;----------------------------------------------------------------------------
detb1:		.byte "SORRY, BASIC 1 IS NOT SUPPORTED", CR, 0
detb2:		.byte "BASIC 2 DETECTED", CR, 0
detb4:		.byte "BASIC 4 DETECTED", CR, 0
detunknown:	.byte "UNABLE TO DETECT BASIC VERSION", CR, 0

hello:  	.byte CR, CR
		.byte "UNIVERSAL WEDGE (2015-12-10)", CR
		.byte "============================", CR, CR, 0
msg_inst:	.byte "WEDGE INSTALLED", CR, 0
msg_mem0:	.byte "MEMSIZ DECREASED BY", 0
msg_mem1:	.byte " BYTES", CR, 0

;----------------------------------------------------------------------------
; WEDGE CONTAINER
;----------------------------------------------------------------------------
b2wstart:	.incbin "b2wedge.bin"   ; BASIC 2 wedge
b2wendplus1:

b4wstart:	.incbin "b4wedge.bin"   ; BASIC 4 wedge
b4wendplus1:
;----------------------------------------------------------------------------
	.end

