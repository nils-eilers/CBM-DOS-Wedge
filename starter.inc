;----------------------------------------------------------------------------
; BASIC STARTER
;----------------------------------------------------------------------------
	.code
	.org $0400 - 2	
origin:	.word $0400			; start address
	.byte $00			; for BASIC 1 
	.word @eol                      ; pointer to next line
	.word 10			; line number
	.byte TK_SYS, "1037", 0		; SYS 1037
@eol:   .byte 0,0			; end of basic program marker
