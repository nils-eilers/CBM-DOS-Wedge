;----------------------------------------------------------------------------
; STROUTZ:  output zero terminated string of any size
; in:       A -- lsb pointer to string
;           Y -- msb pointer to string
; out:      A = 0
;           Y = 0
; changes:  STRADR, STRADR + 1
;----------------------------------------------------------------------------

STROUTZ:    sta     STRADR          ; store pointer to string
            sty     STRADR + 1
            ldy     #0

@next:      lda     (STRADR),y      ; get next character
            beq     @return         ; return on zero character
            jsr     BSOUT           ; output character
            inc     STRADR          ; advance pointer
            bne     @next
            inc     STRADR + 1
            bne     @next           ; and again

@return:    rts

