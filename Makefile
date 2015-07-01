all:    sanity mywedge romwedge doc d64 zip

sanity:
	printf "Checking requirements... "
	# Check and show all requiremens before doing anything
	rm -f error.tmp
	type -P petcat >/dev/null 2>&1 || \
	{ echo >&2 "petcat (part of VICE emulator) not found."; \
	  touch error.tmp; }
	type -P c1541 >/dev/null 2>&1 || \
	{ echo >&2 "c1541 (part of VICE emulator) not found."; \
	  touch error.tmp; }
	type -P ca65 >/dev/null 2>&1 || \
	{ echo >&2 "ca65 (part of cc65) not found."; \
	  touch error.tmp; }
	type -P cl65 >/dev/null 2>&1 || \
	{ echo >&2 "cl65 (part of cc65) not found."; \
	  touch error.tmp; }
	type -P zip >/dev/null 2>&1 || \
	{ echo >&2 "zip not found."; \
	  touch error.tmp; }
	type -P lynx >/dev/null 2>&1 || \
	{ echo >&2 "lynx not found."; \
	  touch error.tmp; }
	if [ -a error.tmp ] ; then \
		rm error.tmp ; \
		echo "Some requirements were not met, aborting." ; \
		exit 1 ; \
	else \
		echo "OK" ; \
	fi

.SILENT:	sanity

b4wedge.bin:	b4wedge.asm basic4.inc pet.inc residentwedge.inc
	ca65 -l b4wedge.asm
	ld65 -t none b4wedge.o -o b4wedge.bin

b2wedge.bin:	b2wedge.asm basic2.inc pet.inc residentwedge.inc 
	ca65 -l b2wedge.asm
	ld65 -t none b2wedge.o -o b2wedge.bin

mywedge:	b4wedge.bin b2wedge.bin wedge.asm 
	ca65 -l wedge.asm
	ld65 -t none wedge.o -o wedge 

romwedge:	b2wedge.bin b4wedge.bin romwedge.asm
	ca65 -l romwedge.asm
	ld65 -t none romwedge.o -o romwedge.bin
	printf '\000' > 9000.bin
	printf '\220' >> 9000.bin
	cat 9000.bin romwedge.bin > romwedge-9000.prg
	printf '\000' > A000.bin
	printf '\240' >> A000.bin
	cat A000.bin romwedge.bin > romwedge-A000.prg
	

doc:	wedge.htm
	# Convert HTML to plain text
	lynx -force_html -dump -nolist wedge.htm > wedge.txt
	# Delete bottom navigation bar and download area (last 6 lines)
	sed -n -e :a -e '1,6!{P;N;D;};N;ba' wedge.txt > wedge.txt.tmp
	# Delete top navigation bar (lines 5 to 8)
	# sed '5,8d' wedge.txt.tmp > wedge.txt
	# Change _ to -
	sed 's/_/-/g' wedge.txt.tmp > wedge.txt
	# mv wedge.txt.tmp wedge.txt
	# Append link to source URL
	echo "\n\n   http://petsd.net/wedge.php\n" >> wedge.txt
	# Fix arrow up character: replace ^| with ^
	sed 's/\^|/\^/g' wedge.txt > wedge.txt.tmp
	# Delete temporary file
	mv wedge.txt.tmp wedge.txt
	rm -f wedge.txt.tmp
	# Keep wedge.txt and generate a BASIC listing from it
	# Make quotes printable
	sed 's/"/";chr$$(34);"/g' wedge.txt > basic.txt.tmp
	# Embed lines in PRINT commands
	sed 's/^/print"/' basic.txt.tmp > basic.txt
	# Pause every 24 lines
	sed -f pagebreak.sed basic.txt > basic.txt.tmp
	# Merge page lister
	cat pager.bas basic.txt.tmp > basic.txt
	echo return >> basic.txt
	# Convert text file to BASIC file
	petcat -w2 -l 0401 -o wedge-manual -- basic.txt
	# Delete temporary file
	rm -f basic.txt

check:	wedge.htm
	tidy -e wedge.htm
	hunspell -H -d en_US wedge.htm

d64:	wedge
	# Create empty disk image
	c1541 -format "universal wedge,ne" d64 wedge.d64 8 
	# Copy prg to disk image
	c1541 -attach wedge.d64 -write wedge
	# Add BASIC documentation
	c1541 -attach wedge.d64 -write wedge-manual "wedge manual"
	# Add ASCII documentation as seq file
	c1541 -attach wedge.d64 -write wedge.txt "wedge manual.asc,s"
	# Add ROM versions
	c1541 -attach wedge.d64 -write romwedge-9000.prg "romwedge-9000,p"
	c1541 -attach wedge.d64 -write romwedge-A000.prg "romwedge-a000,p"

zip:	mywedge d64
	zip wedge.zip Makefile wedge *.d64 *.inc *.asm *.htm *.txt pagebreak.sed pager.bas romwedge.bin

clean:
	rm -f *.bin *.o *.lst *.lbl *.tmp

veryclean:	clean
	rm -f wedge wedge-manual wedge.zip wedge.d64 wedge.txt basic.txt basic.txt.tmp

.PHONY:	sanity clean veryclean
