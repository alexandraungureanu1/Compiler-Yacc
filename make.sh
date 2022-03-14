lex lex.l
yacc -d yacc.y
g++ control.cpp variable.cpp function.cpp defined_class.cpp tables_handler.cpp y.tab.c lex.yy.c -std=c++11 -o compiler
rm lex.yy.c
rm y.tab.c
rm y.tab.h
./compiler cod.txt