100 rem this file was auto-generated from a html document
110 print "{clr}";
120 gosub 300: gosub 200
130 print "{clr}You have reached the end of the document."
140 print "Read again from start (y/n)?"
150 get k$: if k$<>"y" and k$<>"n" then 150
160 if k$="y" then run
170 print "{clr}";
180 end
190 :
200 print "{down}Press any key to continue...{up}"
210 get k$: if k$="" then 210
220 print "{clr}";
230 return
240 :
300
