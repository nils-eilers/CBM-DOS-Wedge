; Universal Wedge for BASIC 2 and BASIC 4
; Based on Commodore's universal wedge taken from 8050's test/demo disk
; but rewritten and enhanced by Nils Eilers
; ROM version
;----------------------------------------------------------------------------
	START = $9000			; uncomment one of the addresses
;	START = $A000
; BASIC	.set 4				; uncomment appropiate BASIC version
BASIC .set 2
;----------------------------------------------------------------------------
	.listbytes unlimited
	.code
	.org START
	jmp install_wedge
	.include "6502.inc"		; general 6502 macros
	.include "pet.inc"		; common definitions for BASIC 2+4
	.include "stroutz.inc"		; working stroutz
; FIXME: use BASIC 2 STROUTZ
	.if BASIC=2
	  .include "basic2.inc"
	.elseif BASIC=4
	  .include "basic4.inc"
	.else
	  .error "Unknown BASIC version"
	.endif

;----------------------------------------------------------------------------
; VARIABLES
;----------------------------------------------------------------------------
	size		= $d1

;----------------------------------------------------------------------------
; INSTALL WEDGE
;----------------------------------------------------------------------------
install_wedge:
	lda #<resident_wedge		; patch CHRGET JMP address
	sta CHRGET+1 			; to jump into wedge
	lda #>resident_wedge
	sta CHRGET+2
	lda #$4c			; insert JMP command in CHRGET routine
	sta CHRGET

	lda #8				; init default device
	sta $73				; (unused byte in CHRGET)

	lday msg_inst			; write "wedge installed"
	jsr STROUTZ

	rts				; exit to BASIC

;----------------------------------------------------------------------------
; STRING CONSTANTS
;----------------------------------------------------------------------------
msg_inst: 	.byte CR, CR
		.byte "BASIC ", '0'+BASIC, " "
		.byte "ROM WEDGE (2012-09-17) INSTALLED", CR, CR, 0

;----------------------------------------------------------------------------
; WEDGE CONTAINER
;----------------------------------------------------------------------------
resident_wedge:
		.if BASIC=2
b2wstart:	.incbin "b2wedge.bin"   ; BASIC 2 wedge
b2wendplus1:
		.elseif BASIC=4
b4wstart:	.incbin "b4wedge.bin"   ; BASIC 4 wedge
b4wendplus1:
		.endif

	.end

