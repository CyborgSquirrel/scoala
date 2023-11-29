/*** Definition Section ***/
%{
#include <string.h>


int errorFound = 0;
int lineNumber = 1;


typedef struct{
	char atom[100];
	int codAtom;
	int codTS;
}FIP;

typedef struct{
	char atom[100];
	int codAtomTS;
}TS;

FIP fip[300];
TS ts[300];
int codTS = 0;

void addToFIP(char atom[], int codAtom, int codTS) {

}

int addToTS(char atom[]) {
	printf("sfdsfdsf");
	return codTS;
}

void printTS() {}
void printFIP() {}


%}


REAL_NUMBER  [+-]?(0|[1-9][0-9]*)(\.[0-9]+)?
IDENTIFIER   [a-z][a-z0-9_]*
STRING       \".*\"

/*** Rule Section ***/
%%
					/* yytext is the text in the buffer */
"#include <iostream.h>"					{ printf("%s - cod ATOM: %d \n", yytext, 30); }
if                                    	{ printf("%s - cod ATOM: %d \n", yytext, 29); }
while                                   { printf("%s - cod ATOM: %d \n", yytext, 2); }
for                                    	{ printf("%s - cod ATOM: %d \n", yytext, 3); }
write                                   { printf("%s - cod ATOM: %d \n", yytext, 4); }
read                                    { printf("%s - cod ATOM: %d \n", yytext, 5); }
else                                    { printf("%s - cod ATOM: %d \n", yytext, 6); }
int                                    	{ printf("%s - cod ATOM: %d \n", yytext, 7); }
real                                   	{ printf("%s - cod ATOM: %d \n", yytext, 8); }
char									{ printf("%s - cod ATOM: %d \n", yytext, 9); }
\<                                    	{ printf("%s - cod ATOM: %d \n", yytext, 21); }
\<{2}									{ printf("%s - cod ATOM: %d \n", yytext, 10); }
\;                                    	{ printf("%s - cod ATOM: %d \n", yytext, 11); }
\(                                    	{ printf("%s - cod ATOM: %d \n", yytext, 12); }
\)                                    	{ printf("%s - cod ATOM: %d \n", yytext, 13); }
\,                                    	{ printf("%s - cod ATOM: %d \n", yytext, 14); }
\+                                    	{ printf("%s - cod ATOM: %d \n", yytext, 15); }
\-                                    	{ printf("%s - cod ATOM: %d \n", yytext, 16); }
\*                                    	{ printf("%s - cod ATOM: %d \n", yytext, 17); }
\/                                    	{ printf("%s - cod ATOM: %d \n", yytext, 18); }
\%                                    	{ printf("%s - cod ATOM: %d \n", yytext, 19); }
\>                                    	{ printf("%s - cod ATOM: %d \n", yytext, 20); }
\>=                                    	{ printf("%s - cod ATOM: %d \n", yytext, 22); }
\=                                    	{ printf("%s - cod ATOM: %d \n", yytext, 23); }
\==                                    	{ printf("%s - cod ATOM: %d \n", yytext, 24); }
\and                                    { printf("%s - cod ATOM: %d \n", yytext, 25); }
\or                                    	{ printf("%s - cod ATOM: %d \n", yytext, 26); }
\.                                    	{ printf("%s - cod ATOM: %d \n", yytext, 27); }
\!=                                    	{ printf("%s - cod ATOM: %d \n", yytext, 28); }
{IDENTIFIER}							{ printf("%s - ID: %d \n", yytext, 0); }
{REAL_NUMBER}                           { printf("%s - CONST: %d \n", yytext, 1); addToTS(yytext);}
{STRING}								{ printf("%s - CONST \n",yytext, 1); }
[\n]									{ ++lineNumber; }
[ \t\n]+             					{ ; /* eat up whitespace */ }
.                						{ errorFound = 1; printf("Illegal token %s at line %d !", yytext, lineNumber); printf("\n"); }
%%

/* yywrap() - wraps the above rule section */
int yywrap() {}

int main(int argc, char** argv) {

	FILE *fp;
	fp = fopen(argv[1], "r");
	
	/* yyin - takes the file pointer which contains the input*/
	yyin = fp;

	/* yylex() - this is the main flex function which runs the Rule Section*/ 
	yylex();
	
  
	return 0;
}
