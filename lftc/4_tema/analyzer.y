%{
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "./scanner.h"

extern void scan_print();

void yyerror(char *s) {
	extern char *yytext;
	extern int line_number;
	printf("Error for symbol %s at line: %d ! \n", yytext, line_number);
	scan_print();
	exit(1);
}
%}

/* SPECIAL ATOMS */
%token TOK_ID
%token TOK_LIT

/* WORD ATOMS */
%token TOK_FN
%token TOK_MAIN
%token TOK_IF
%token TOK_WHILE
%token TOK_STRUCT
%token TOK_LET
%token TOK_MUT
%token TOK_PRINTLN

/* SYMBOL ATOMS */
%token TOK_SEMI_COL  // ;
%token TOK_L_BRACKET // {
%token TOK_R_BRACKET // }
%token TOK_L_PAREN   // (
%token TOK_R_PAREN   // )
%token TOK_COL_COL   // ::
%token TOK_COL       // :
%token TOK_DOT       // .
%token TOK_COMMA     // ,
%token TOK_ADD       // +
%token TOK_SUB       // -
%token TOK_MUL       // *
%token TOK_DIV       // /
%token TOK_MOD       // %
%token TOK_LT_EQ     // <=
%token TOK_GT_EQ     // >=
%token TOK_LT        // <
%token TOK_GT        // >
%token TOK_EQ_EQ     // ==
%token TOK_NOT_EQ    // !=
%token TOK_NOT       // !
%token TOK_EQ        // =
%token TOK_REF_MUT   // &mut
%token TOK_REF       // &

%%
program: struct_list TOK_FN TOK_MAIN TOK_L_PAREN TOK_R_PAREN bloc_instr;

struct_list: |struct struct_list
struct: TOK_STRUCT TOK_ID TOK_L_BRACKET struct_inner TOK_R_BRACKET;
struct_inner: |struct_membru TOK_SEMI_COL struct_inner;
struct_membru: TOK_ID TOK_COL path;

bloc_instr: TOK_L_BRACKET bloc_instr_inner TOK_R_BRACKET;
bloc_instr_inner: | instr bloc_instr_inner;

instr:
	  TOK_SEMI_COL
	| instr_if
	| instr_while
	| instr_declarare TOK_SEMI_COL
	| instr_asignare TOK_SEMI_COL
	| instr_afisare TOK_SEMI_COL
	| expr TOK_SEMI_COL
;

instr_if: TOK_IF expr bloc_instr;

instr_while: TOK_WHILE expr bloc_instr;

instr_declarare:
	TOK_LET instr_declarare_mut TOK_ID instr_declarare_type TOK_EQ expr;
instr_declarare_mut: |TOK_MUT;
instr_declarare_type: |TOK_COL path;

instr_asignare: TOK_ID TOK_EQ expr;

instr_afisare: TOK_PRINTLN TOK_L_PAREN parametri_apel TOK_R_PAREN;

expr:
	  path
	| TOK_LIT
	| path TOK_L_PAREN parametri_apel TOK_R_PAREN
	| expr TOK_DOT TOK_ID TOK_L_PAREN parametri_apel TOK_R_PAREN
	| expr TOK_DOT TOK_ID
	| expr binop expr
	| unop expr
;

unop: TOK_NOT | TOK_REF | TOK_REF_MUT;
binop:
	 TOK_ADD|TOK_SUB|TOK_MUL|TOK_DIV|TOK_MOD
	|TOK_LT_EQ|TOK_GT_EQ|TOK_LT|TOK_GT|TOK_EQ_EQ|TOK_NOT_EQ
;

parametri_apel: | expr TOK_COMMA parametri_apel | expr;

path: TOK_ID | TOK_ID TOK_COL_COL path;
%%

void anl() {
    while (!feof(yyin)) {
        yyparse();
    }
}
