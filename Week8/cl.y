// definitions

%{

#include <stdio.h>
void yyerror(const char* str);
int yylex();
%}

/*
<contact_list>: <contact> ENDL <contact_list>
;
//<contact>: <name> <sep> <name> <sep> <phone> <sep> <email> <sep> <age>
<contact>: NAME SEP NAME SEP PHONE SEP EMAIL SEP AGE
;
*/


// tokens

%union {
	char* str;
	int iVal;
}

%token NAME
%token SEP
%token PHONE
%token EMAIL
%token AGE
%token ENDL
%type<str> NAME
%type<str> EMAIL
%type<str> PHONE
%type<iVal> AGE


%start program

%%

program:contact_list						{;}
;

contact_list: contact						{;}
	    | contact_list contact				
;
contact: NAME SEP NAME SEP PHONE SEP EMAIL SEP AGE ENDL 		{printf("%s %s\n", $1, $3);}
;


%%

int main(int argc, char** argv) {
	yyparse();
	return 0;
}




void yyerror(const char* str) {
	// print to error string, not output stream

	fprintf(stderr, "%ERROR: %s%\n", str);
}
