%{
#include <stdio.h>
%}

%%
[0-9]+   { printf("%s\n", yytext); }  /* Print numbers */
.        ;  /* Ignore other characters */
\n       return 0;  /* Stop at newline */

%%

int main() {
    printf("Enter input: ");
    yylex();
    return 0;
}

/* Fix yywrap() error */
int yywrap() {
    return 1;
}


flex sample.l   # Generates lex.yy.c
gcc lex.yy.c -o lexer.exe -lfl  # Compile using GCC
./lexer.exe