%{

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "../obj.c"
#include "analyzer.h"

int error_found = 0;
extern int line_number = 1;

struct FipEntry {
	char *source;
	size_t source_len;
	int atom_code;

	uint8_t has_id;
	int ts_id_code;

	uint8_t has_lit;
	int ts_lit_code;
};

struct Program {
	struct Obj *fip;

	int64_t ts_id_code;
	struct Obj *ts_id;

	int64_t ts_lit_code;
	struct Obj *ts_lit;
};

struct Program program;

void add_atom(char *source, size_t source_len, int atom_code) {
	// printf("%.*s\n", source_len, source);
	
	struct FipEntry fip_entry;
	fip_entry.source = malloc(sizeof(char) * source_len);
	memcpy(fip_entry.source, source, sizeof(char) * source_len);
	fip_entry.source_len = source_len;
	fip_entry.atom_code = atom_code;

	fip_entry.has_id = atom_code == TOK_ID;
	fip_entry.ts_id_code = 0;
	if (fip_entry.has_id) {
		fip_entry.ts_id_code = program.ts_id_code;
		program.ts_id_code++;

		struct Obj *key = obj_str_new(source_len, source);

		struct ObjDict *ts_id_dict = obj_as_dict(program.ts_id);
		if (!obj_dict_contains(ts_id_dict, key)) {
			struct Obj *value = obj_int_new(fip_entry.ts_id_code);
			obj_dict_assign(ts_id_dict, key, value);
			obj_drop(value);
		}
		
		obj_drop(key);
	}

	fip_entry.has_lit = atom_code == TOK_LIT;
	fip_entry.ts_lit_code = 0;
	if (fip_entry.has_lit) {
		fip_entry.ts_lit_code = program.ts_lit_code;
		program.ts_lit_code++;

		struct Obj *key = obj_str_new(source_len, source);

		struct ObjDict *ts_lit_dict = obj_as_dict(program.ts_lit);
		if (!obj_dict_contains(ts_lit_dict, key)) {
			struct Obj *value = obj_int_new(fip_entry.ts_lit_code);
			obj_dict_assign(ts_lit_dict, key, value);
			obj_drop(value);
		}
		
		obj_drop(key);
	}

	struct Obj *obj = obj_bytes_new(sizeof(struct FipEntry), &fip_entry);
	struct ObjList *fip_list = obj_as_list(program.fip);
	obj_list_push(fip_list, obj);
	obj_drop(obj);
}

%}

%option noyywrap

ID [a-zA-Z][a-zA-Z0-9_]{0,249}|_[a-zA-Z0-9_]{1,249}
LIT_INT 0b[01]+|0o[0-7]+|[0-9]+|0x[0-9a-fA-F]+
LIT_FLOAT [0-9]+"."[0-9]*
LIT_STR \"[a-zA-Z0-9{} =]*\"

/*** Rule Section ***/
%%
fn           { add_atom(yytext, yyleng, TOK_FN      ); return TOK_FN      ; }
main         { add_atom(yytext, yyleng, TOK_MAIN    ); return TOK_MAIN    ; }
if           { add_atom(yytext, yyleng, TOK_IF      ); return TOK_IF      ; }
while        { add_atom(yytext, yyleng, TOK_WHILE   ); return TOK_WHILE   ; }
struct       { add_atom(yytext, yyleng, TOK_STRUCT  ); return TOK_STRUCT  ; }
let          { add_atom(yytext, yyleng, TOK_LET     ); return TOK_LET     ; }
mut          { add_atom(yytext, yyleng, TOK_MUT     ); return TOK_MUT     ; }
"println!"   { add_atom(yytext, yyleng, TOK_PRINTLN ); return TOK_PRINTLN ; }

{ID}          { add_atom(yytext, yyleng, TOK_ID ); return TOK_ID ; }
{LIT_INT}     { add_atom(yytext, yyleng, TOK_LIT); return TOK_LIT; }
{LIT_FLOAT}   { add_atom(yytext, yyleng, TOK_LIT); return TOK_LIT; }
{LIT_STR}     { add_atom(yytext, yyleng, TOK_LIT); return TOK_LIT; }

";"           { add_atom(yytext, yyleng, TOK_SEMI_COL ); return TOK_SEMI_COL ; }
"{"           { add_atom(yytext, yyleng, TOK_L_BRACKET); return TOK_L_BRACKET; }
"}"           { add_atom(yytext, yyleng, TOK_R_BRACKET); return TOK_R_BRACKET; }
"("           { add_atom(yytext, yyleng, TOK_L_PAREN  ); return TOK_L_PAREN  ; }
")"           { add_atom(yytext, yyleng, TOK_R_PAREN  ); return TOK_R_PAREN  ; }
"::"          { add_atom(yytext, yyleng, TOK_COL_COL  ); return TOK_COL_COL  ; }
":"           { add_atom(yytext, yyleng, TOK_COL      ); return TOK_COL      ; }
"."           { add_atom(yytext, yyleng, TOK_DOT      ); return TOK_DOT      ; }
","           { add_atom(yytext, yyleng, TOK_COMMA    ); return TOK_COMMA    ; }
"+"           { add_atom(yytext, yyleng, TOK_ADD      ); return TOK_ADD      ; }
"-"           { add_atom(yytext, yyleng, TOK_SUB      ); return TOK_SUB      ; }
"*"           { add_atom(yytext, yyleng, TOK_MUL      ); return TOK_MUL      ; }
"/"           { add_atom(yytext, yyleng, TOK_DIV      ); return TOK_DIV      ; }
"%"           { add_atom(yytext, yyleng, TOK_MOD      ); return TOK_MOD      ; }
"<="          { add_atom(yytext, yyleng, TOK_LT_EQ    ); return TOK_LT_EQ    ; }
">="          { add_atom(yytext, yyleng, TOK_GT_EQ    ); return TOK_GT_EQ    ; }
"<"           { add_atom(yytext, yyleng, TOK_LT       ); return TOK_LT       ; }
">"           { add_atom(yytext, yyleng, TOK_GT       ); return TOK_GT       ; }
"=="          { add_atom(yytext, yyleng, TOK_EQ_EQ    ); return TOK_EQ_EQ    ; }
"!="          { add_atom(yytext, yyleng, TOK_NOT_EQ   ); return TOK_NOT_EQ   ; }
"!"           { add_atom(yytext, yyleng, TOK_NOT      ); return TOK_NOT      ; }
"="           { add_atom(yytext, yyleng, TOK_EQ       ); return TOK_EQ       ; }
"&mut"        { add_atom(yytext, yyleng, TOK_REF_MUT  ); return TOK_REF_MUT  ; }
"&"           { add_atom(yytext, yyleng, TOK_REF      ); return TOK_REF      ; }

[\n]     { ++line_number; }
[ \t]+   { ; /* eat up whitespace */ }
.        { error_found = 1; printf("Illegal token %s at line %d !", yytext, line_number); printf("\n"); }
%%

void scan_init() {
	program.fip = obj_list_new();
	program.ts_id_code = 0;
	program.ts_id = obj_dict_new();
	program.ts_lit_code = 0;
	program.ts_lit = obj_dict_new();
}

void scan_drop() {
	obj_drop(program.fip);
	obj_drop(program.ts_id);
	obj_drop(program.ts_lit);
}

void scan_print() {
	printf("=============== FIP ===============\n");
	struct ObjList *fip_list = obj_as_list(program.fip);
	for (int i = 0; i < fip_list->len; ++i) {
		struct Obj *obj_fip_entry = obj_list_index(fip_list, i);
		struct ObjBytes *obj_fip_entry_bytes = obj_as_bytes(obj_fip_entry);
		struct FipEntry *fip_entry = obj_fip_entry_bytes->buf;

		printf(
			"%2d|%20.*s",
			fip_entry->atom_code,
			fip_entry->source_len,
			fip_entry->source);

		if (fip_entry->has_id) {
			printf("|%5d", fip_entry->ts_id_code);
		} else {
			printf("|%*c", 5, ' ');
		}

		if (fip_entry->has_lit) {
			printf("|%5d", fip_entry->ts_lit_code);
		} else {
			printf("|%*c", 5, ' ');
		}

		printf("\n");
		
		obj_drop(obj_fip_entry);
	}
	printf("\n");

	printf("=============== TS_ID ===============\n");
	struct Obj *ts_id = obj_dict_to_list(obj_as_dict(program.ts_id));
	struct ObjList *ts_id_list = obj_as_list(ts_id);
	for (int i = 0; i < ts_id_list->len; ++i) {
		struct Obj *obj = obj_list_index(ts_id_list, i);
		struct ObjList *obj_list = obj_as_list(obj);
		
		struct Obj *key = obj_list_index(obj_list, 0);
		struct ObjStr *key_str = obj_as_str(key);

		struct Obj *value = obj_list_index(obj_list, 1);
		struct ObjInt *value_int = obj_as_int(value);

		printf(
			"%2d|%20.*s\n",
			value_int->value,
			key_str->len,
			key_str->buf);
		
		obj_drop(key);
		obj_drop(value);
		obj_drop(obj);
	}
	obj_drop(ts_id);
	printf("\n");

	printf("=============== TS_LIT ===============\n");
	struct Obj *ts_lit = obj_dict_to_list(obj_as_dict(program.ts_lit));
	struct ObjList *ts_lit_list = obj_as_list(ts_lit);
	for (int i = 0; i < ts_lit_list->len; ++i) {
		struct Obj *obj = obj_list_index(ts_lit_list, i);
		struct ObjList *obj_list = obj_as_list(obj);
		
		struct Obj *key = obj_list_index(obj_list, 0);
		struct ObjStr *key_str = obj_as_str(key);

		struct Obj *value = obj_list_index(obj_list, 1);
		struct ObjInt *value_int = obj_as_int(value);

		printf(
			"%2d|%20.*s\n",
			value_int->value,
			key_str->len,
			key_str->buf);
		
		obj_drop(key);
		obj_drop(value);
		obj_drop(obj);
	}
	obj_drop(ts_lit);

	{
		struct ObjList *fip_list = obj_as_list(program.fip);
		for (int i = 0; i < fip_list->len; ++i) {
			struct Obj *obj_fip_entry = obj_list_index(fip_list, i);
			struct ObjBytes *obj_fip_entry_bytes = obj_as_bytes(obj_fip_entry);
			struct FipEntry *fip_entry = obj_fip_entry_bytes->buf;

			free(fip_entry->source);
			
			obj_drop(obj_fip_entry);
		}
	}
}
