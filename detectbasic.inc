;----------------------------------------------------------------------------
; DETECTBASIC -- detect BASIC version and jump to corresponding labels
; --> basic1
; --> basic2
; --> basic4
; --> basicunknown
;
; Inspired by code from Michael Sachse found at
; http://www.cbmhardware.de/cbmwiki/index.php/Detect_CBM but rewritten
;----------------------------------------------------------------------------

detectbasic:
	lda $e1c4	; check first '#' of "### commodore basic ###"
	cmp #$23
	bne @basic4or1
	jmp basic2	; match: BASIC 2 detected

@basic4or1:
	lda $e180	; check first '*' of "*** commodore basic ***"
	cmp #$2a
	bne @basic4
	jmp basic1	; match: BASIC 1 detected

@basic4:
	lda $dea4	; check first '*' of "*** commodore basic 4.0 ***"
	cmp #$2a
	bne @unknown
	jmp basic4	; match: BASIC 4 detected

@unknown:
	jmp basicunknown
