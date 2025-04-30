%{
#include <stdio.h>
#include <stdlib.h>
%}

%token IF THEN ELSE BOOL A

%%

S  : IF E THEN S S1
   | A
   ;

S1 : ELSE S
   | /* empty */
   ;

E  : BOOL
   ;

%%

int main() {
    printf("Enter the string: ");
    if (yyparse() == 0)
        printf("Valid string\n");
    else
        printf("Invalid string\n");
    return 0;
}

void yyerror(const char *s) {
    // Called when parser fails
    // No need to print anything here (handled in main)
}



//RUN COMMAND:
//yacc -d parser.y
//flex lexer.l
//gcc y.tab.c lex.yy.c -o parser
//./parser