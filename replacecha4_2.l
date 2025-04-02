%{
#include <stdio.h>
%}

%%
[Cc]harusat    printf("university");
.              putchar(yytext[0]); 
\n             putchar('\n');
%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

flex sample.l   # Generates lex.yy.c
gcc lex.yy.c -o lexer.exe -lfl  # Compile using GCC
./lexer.exe