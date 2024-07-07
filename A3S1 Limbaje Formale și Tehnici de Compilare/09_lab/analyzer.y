%{
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "./scanner.h"

void yyerror(char *s) {
	extern char *yytext;
	printf("Error for symbol %s!\n", yytext);
	exit(1);
}
%}

%token TOK_CUVANT

%%
text: |TOK_CUVANT text;
%%

void anl() {
    while (!feof(yyin)) {
        yyparse();
    }
}
