%{
#include "y.tab.h"   // Include tokens from YACC
%}

%%
i       { return IF; }
t       { return THEN; }
e       { return ELSE; }
b       { return BOOL; }
a       { return A; }
[ \t\n] ;             // Ignore whitespace
.       { return yytext[0]; }
%%

int yywrap() {
    return 1;
}
