del prog.lex.c
del prog.exe
del prog.lex.o
del prog.h
del prog.y.c
del prog.y.o

pause
win_bison -v -d prog.y
rename prog.tab.h prog.h
rename prog.tab.c prog.y.c
win_flex prog.l
rename lex.yy.c prog.lex.c