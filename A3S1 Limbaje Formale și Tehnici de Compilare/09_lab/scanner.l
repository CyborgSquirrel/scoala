%{

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "../obj.c"
#include "analyzer.h"

int error_found = 0;

extern int cuvinte_nr = 0;
extern int ceremonii_nr = 0;

%}

%option noyywrap

CEREMONIE_DERIV ceremon(ia|iai|iam|iara|iaram|iarati|iase|iasem|iasera|iaseram|iaserati|iasesi|iasi|iat|iati|iau|iaza|ie|iei|iem|iere|iez|ieze|iezi|ii|iile|iilor|iind)

/*** Rule Section ***/
%%
{CEREMONIE_DERIV}   { ceremonii_nr += 1; cuvinte_nr += 1; return TOK_CUVANT; }
[a-z]+              { cuvinte_nr += 1; return TOK_CUVANT; }
[ \t\n]+            { ; /* eat up whitespace */ }
.                   { error_found = 1; printf("Illegal token %s!\n", yytext); exit(1); }
%%
