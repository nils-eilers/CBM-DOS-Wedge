; TODO: convert commented addresses to values for BASIC 4


; --------- BASIC 2 ROM ROUTINES -----------------------------------------
	.macro BASIC2
BASIC	.set 2		; remember BASIC 2 selection

SCROUT	.set $e3d8	; output A to screen
;	RDOA		.set $d754	; read hex address -> $FB,$FC
;	RDOB		.set $d763	; read hex byte -> A
;	CLRSCR		.set $e015	; clear screen
CRLF	.set $fdd0	; move cursor to next line
;	FPOUT		.set $cf8d	; write floating point
INTOUT	.set $dcd9	; write integer 0-65535 X.setLSB,A.setMSB
;	SCROLD		.set $e021	; scroll down
;	SCROLU		.set $e024	; scroll up
;	SPAC2		.set $d52e	; write 2 spaces
;	SPACE		.set $d531	; write space
;	STROUT		.set $bb24	; X.setlen, STRADR.setptr
;	STROUTZ		.set $bb1d	; A.setLSB, Y.setMSB
;	WROA		.set $d717	; write hex address
;	HEXOUT      	.set $d722 ; write A as hex
;	WROB		.set $d731	; write hex byte
;	WRTWO		.set $d731	; write XA to screen

;	ADRFP		.set $cd7f	; uint LSB.set$5f, MSB.set$60 -> FAC1
;	ASCII		.set $d73a	; hex digit -> ascii hex digit
;	FPINT		.set $cdd1	; FAC1 -> uint $61.setMSB, $62.setLSB
;	FPSTR		.set $cf93	; fp -> str $0100..NUL
;	HEXIT		.set $d78d	; hex ascii digit A -> hex digit A
;	INTFP		.set $c4bc	; int Y.setLSB, A.setMSB -> FAC1
;	STRFP		.set $c8eb	; string -> fp
RDINT	.set $c873	; read basic text -> LINNUM

;	ABS		.set $cd8e	; FAC1 .set ABS(FAC1)
;	ADD		.set $c9a0	; FAC1 .set FAC1 + FAC2
;	ATN		.set $d32C	; FAC1 .set ATN(FAC1)
;	COS		.set $d282	; FAC1 .set COS(FAC1)
;	DIV		.set $cc48	; FAC1 .set FAC2 / FAC1
;	EXP		.set $d184	; FAC1 .set EXP(FAC1)
;	FAC12		.set $cd45	; FAC2 :.set FAC1
; TODO: add more FP routines!

ACPTR	.set $f18c	; input IEEE -> A
;	CHKIN		.set $ffc6	; stdin from logical file # in X
CIOUT	.set $f16f	; output A -> IEEE
;	CKOUT		.set $ffc9	; stdout to logical file # in X
;	CLOSE		.set $f2e0	; close file
CLSEI	.set $f6f0	; close and unlisten
;	CLRCH		.set $ffcc	; reset stdio to defaults
LISTN	.set $f0ba	; send LISTEN
;	LOAD		.set $f408	; LOAD
LOADOP	.set $f322	; LOAD without pointer change
FILENOTFOUND .set $f3e6	; FILE NOT FOUND, return to BASIC
;	OPEN		.set $f563	; open file
OPENI	.set $f466	; open file on IEEE device
;	SCNT		.set $f2c1	; prepare SETT for logical file A
SECND	.set $f128	; send secondary address A
;	SETT		.set $f2cd	; set LF,DN,SA from table
TALK	.set $f0b6	; send TALK
;	TWAIT		.set $f92b	;
UNLSN	.set $f183	; send UNLISTEN
UNTLK	.set $f17f	; send UNTALK

READY	.set $c389	; basic warm start
;	RESET		.set $fd16	; basic cold start
NEWSTT	.set $c6c4	; set up next statement for execution
STOPEQ	.set $f301	; set Z flag if stop key pressed
;	STOPR		.set $ffe1	; return to basic if stop key pressed
ERRO	.set $c36c	; BASIC error message
SYNERR	.set $ce03	; SYNTAX ERROR
IQERR	.set $d123	; ILLEGAL QUANTITY ERROR

;	MOVBLK		.set $b357	; move block

;	GRAPHIC		.set $e01b	; set graphic mode
;	TEXT		.set $e018	; set text mode
;	BEEP		.set $e02a	; beep

LINKPRG	.set $c442	; rechain lines
RSTXCLR	.set $c572 	; reset TXTPTR and perform CLR
STXTPT	.set $c5a7	; reset TXTPTR
;	CLR		.set $b5f0	; perform CLR
;	SCRTCH		.set $b5d4	; perform NEW

MAINS	.set $c39b	; MAIN's return addr on stack for CHRGET routine

	.endmacro
