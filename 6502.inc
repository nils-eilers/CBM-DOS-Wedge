;----------------------------------------------------------------------------
; LDAY addr -- load immediate 16 bit value lsb to A, msb to Y
;----------------------------------------------------------------------------
	.macro lday addr
	.if .paramcount <> 1
	.error "LDAY requires 16 bit value"
	.endif
	lda #<addr
	ldy #>addr
	.endmacro

;----------------------------------------------------------------------------
; LDXA addr -- load immediate 16 bit value lsb to X, msb to A
;----------------------------------------------------------------------------
	.macro ldxa addr
	.if .paramcount <> 1
	.error "LDXA requires 16 bit value"
	.endif
	ldx #<addr
	lda #>addr
	.endmacro

