del parser.h
del parser.c
del lexer.c

win_bison -v -t -d -v --report=lookahead -d parser.y
rename parser.tab.h parser.h
rename parser.tab.c parser.c
win_flex lexer.l
rename lex.yy.c lexer.c