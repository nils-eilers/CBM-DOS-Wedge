; --------- BASIC 4 ROM ROUTINES -----------------------------------------
	.macro BASIC4
BASIC	.set 4		; remember BASIC 4 selection

SCROUT	.set $e202	; output A to screen
RDOA	.set $d754	; read hex address -> $FB,$FC
RDOB	.set $d763	; read hex byte -> A
CLRSCR	.set $e015	; clear screen
CRLF	.set $d534	; move cursor to next line
FPOUT	.set $cf8d	; write floating point
INTOUT	.set $cf83	; write integer 0-65535 X.setLSB,A.setMSB
SCROLD	.set $e021	; scroll down
SCROLU	.set $e024	; scroll up
SPAC2	.set $d52e	; write 2 spaces
SPACE	.set $d531	; write space
STROUT	.set $bb24	; X.setlen, STRADR.setptr
; STROUTZ	.set $bb1d	; A.setLSB, Y.setMSB
; BASIC4 STROUTZ is broken!
WROA	.set $d717	; write hex address
HEXOUT	.set $d722	; write A as hex
WROB	.set $d731	; write hex byte
WRTWO	.set $d731	; write XA to screen

ADRFP	.set $cd7f	; uint LSB.set$5f, MSB.set$60 -> FAC1
ASCII	.set $d73a	; hex digit -> ascii hex digit
FPINT	.set $cdd1	; FAC1 -> uint $61.setMSB, $62.setLSB
FPSTR	.set $cf93	; fp -> str $0100..NUL
HEXIT	.set $d78d	; hex ascii digit A -> hex digit A
INTFP	.set $c4bc	; int Y.setLSB, A.setMSB -> FAC1
STRFP	.set $c8eb	; string -> fp
RDINT	.set $b8f6	; read basic text -> LINNUM

ABS	.set $cd8e	; FAC1 .set ABS(FAC1)
ADD	.set $c9a0	; FAC1 .set FAC1 + FAC2
ATN	.set $d32C	; FAC1 .set ATN(FAC1)
COS	.set $d282	; FAC1 .set COS(FAC1)
DIV	.set $cc48	; FAC1 .set FAC2 / FAC1
EXP	.set $d184	; FAC1 .set EXP(FAC1)
FAC12	.set $cd45	; FAC2 :.set FAC1
; TODO: add more FP routines!

ACPTR	.set $f1c0	; input IEEE -> A
CHKIN	.set $ffc6	; stdin from logical file # in X
CIOUT	.set $f19e	; output A -> IEEE
CKOUT	.set $ffc9	; stdout to logical file # in X
CLOSE	.set $f2e0	; close file
CLSEI	.set $f72f	; close and unlisten
CLRCH	.set $ffcc	; reset stdio to defaults
LISTN	.set $f0d5	; send LISTEN
LOAD	.set $f408	; LOAD
LOADOP	.set $f356	; LOAD without pointer change
FILENOTFOUND .set $f425	; FILE NOT FOUND, return to BASIC
OPEN	.set $f563	; open file
OPENI	.set $f4a5	; open file on IEEE device
SCNT	.set $f2c1	; prepare SETT for logical file A
SECND	.set $f143	; send secondary address A
SETT	.set $f2cd	; set LF,DN,SA from table
TALK	.set $f0d2	; send TALK
TWAIT	.set $f92b	; 
UNLSN	.set $f1b9	; send UNLISTEN
UNTLK	.set $f1ae	; send UNTALK

READY	.set $b3ff	; basic warm start
RESET	.set $fd16	; basic cold start
NEWSTT	.set $b74a	; set up next statement for execution
STOPEQ	.set $f335	; set Z flag if stop key pressed
STOPR	.set $ffe1	; return to basic if stop key pressed

MOVBLK	.set $b357	; move block

GRAPHIC	.set $e01b	; set graphic mode
TEXT	.set $e018	; set text mode
BEEP	.set $e02a	; beep

LINKPRG	.set $b4b6	; rechain lines
RSTXCLR	.set $b5e9	; reset TXTPTR and perform CLR
STXTPT	.set $b622	; reset TXTPTR
CLR	.set $b5f0	; perform CLR
SCRTCH	.set $b5d4	; perform NEW

MAINS	.set $b40f	; MAIN's return addr on stack for CHRGET routine

	.endmacro

