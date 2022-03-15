%{
#include "cl.tab.h"
#include <stdlib.h>
%}

%%

[A-Z][a-z]+			{ yylval.str=yytext; return NAME; }
\((0-9){3}\)(0-9){3}-(0-9){4}		{ yylval.str=yytext; return PHONE; }
[a-z]+@[a-z]+\.edu		{ yylval.str=yytext; return EMAIL; }
[0-9]{1,3}			{ yylval.iVal=atoi(yytext); return AGE; }
;				{ return ENDL; }
,				{ return SEP; }
[ \t\r\s\n]+			{ ; }
.				{ yyerror("YOU DONE MESSED UP, DUMMY.\n"); }


%%
