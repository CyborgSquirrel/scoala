/*** Definition Section ***/
%{

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "../obj.c"

int errorFound = 0;
int lineNumber = 1;

enum Code {
	CODE_NULL = 0,

	/* SPECIAL ATOMS */
	CODE_ID,
	CODE_LIT,

	/* WORD ATOMS */
	CODE_FN,
	CODE_MAIN,
	CODE_IF,
	CODE_WHILE,
	CODE_STRUCT,
	CODE_LET,
	CODE_MUT,
	CODE_PRINTLN,

	/* SYMBOL ATOMS */
	CODE_SEMI_COL,  // ;
	CODE_L_BRACKET, // {
	CODE_R_BRACKET, // }
	CODE_L_PAREN,   // (
	CODE_R_PAREN,   // )
	CODE_COL_COL,   // ::
	CODE_COL,       // :
	CODE_DOT,       // .
	CODE_COMMA,     // ,
	CODE_ADD,       // +
	CODE_SUB,       // -
	CODE_MUL,       // *
	CODE_DIV,       // /
	CODE_MOD,       // %
	CODE_LT_EQ,     // <=
	CODE_GT_EQ,     // >=
	CODE_LT,        // <
	CODE_GT,        // >
	CODE_EQ_EQ,     // ==
	CODE_NOT_EQ,    // !=
	CODE_NOT,       // !
	CODE_EQ,        // =
	CODE_REF_MUT,   // &mut
	CODE_REF,       // &
};

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

	fip_entry.has_id = atom_code == CODE_ID;
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

	fip_entry.has_lit = atom_code == CODE_LIT;
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

ID [a-zA-Z][a-zA-Z0-9_]{0,249}|_[a-zA-Z0-9_]{1,249}
LIT_INT 0b[01]+|0o[0-7]+|[0-9]+|0x[0-9a-fA-F]+
LIT_FLOAT [0-9]+"."[0-9]*
LIT_STR \"[a-zA-Z0-9{} =]*\"

/*** Rule Section ***/
%%
fn           { add_atom(yytext, yyleng, CODE_FN      ); }
main         { add_atom(yytext, yyleng, CODE_MAIN    ); }
if           { add_atom(yytext, yyleng, CODE_IF      ); }
while        { add_atom(yytext, yyleng, CODE_WHILE   ); }
struct       { add_atom(yytext, yyleng, CODE_STRUCT  ); }
let          { add_atom(yytext, yyleng, CODE_LET     ); }
mut          { add_atom(yytext, yyleng, CODE_MUT     ); }
"println!"   { add_atom(yytext, yyleng, CODE_PRINTLN ); }

{ID}          { add_atom(yytext, yyleng, CODE_ID ); }
{LIT_INT}     { add_atom(yytext, yyleng, CODE_LIT); }
{LIT_FLOAT}   { add_atom(yytext, yyleng, CODE_LIT); }
{LIT_STR}     { add_atom(yytext, yyleng, CODE_LIT); }

";"           { add_atom(yytext, yyleng, CODE_SEMI_COL ); }
"{"           { add_atom(yytext, yyleng, CODE_L_BRACKET); }
"}"           { add_atom(yytext, yyleng, CODE_R_BRACKET); }
"("           { add_atom(yytext, yyleng, CODE_L_PAREN  ); }
")"           { add_atom(yytext, yyleng, CODE_R_PAREN  ); }
"::"          { add_atom(yytext, yyleng, CODE_COL_COL  ); }
":"           { add_atom(yytext, yyleng, CODE_COL      ); }
"."           { add_atom(yytext, yyleng, CODE_DOT      ); }
","           { add_atom(yytext, yyleng, CODE_COMMA    ); }
"+"           { add_atom(yytext, yyleng, CODE_ADD      ); }
"-"           { add_atom(yytext, yyleng, CODE_SUB      ); }
"*"           { add_atom(yytext, yyleng, CODE_MUL      ); }
"/"           { add_atom(yytext, yyleng, CODE_DIV      ); }
"%"           { add_atom(yytext, yyleng, CODE_MOD      ); }
"<="          { add_atom(yytext, yyleng, CODE_LT_EQ    ); }
">="          { add_atom(yytext, yyleng, CODE_GT_EQ    ); }
"<"           { add_atom(yytext, yyleng, CODE_LT       ); }
">"           { add_atom(yytext, yyleng, CODE_GT       ); }
"=="          { add_atom(yytext, yyleng, CODE_EQ_EQ    ); }
"!="          { add_atom(yytext, yyleng, CODE_NOT_EQ   ); }
"!"           { add_atom(yytext, yyleng, CODE_NOT      ); }
"="           { add_atom(yytext, yyleng, CODE_EQ       ); }
"&mut"        { add_atom(yytext, yyleng, CODE_REF_MUT  ); }
"&"           { add_atom(yytext, yyleng, CODE_REF      ); }

[\n]     { ++lineNumber; }
[ \t]+   { ; /* eat up whitespace */ }
.        { errorFound = 1; printf("Illegal token %s at line %d !", yytext, lineNumber); printf("\n"); }
%%

/* yywrap() - wraps the above rule section */
int yywrap() {}

int main(int argc, char **argv) {
	program.fip = obj_list_new();
	program.ts_id_code = 0;
	program.ts_id = obj_dict_new();
	program.ts_lit_code = 0;
	program.ts_lit = obj_dict_new();
	
	FILE *fp;
	fp = fopen(argv[1], "r");
	
	/* yyin - takes the file pointer which contains the input*/
	yyin = fp;

	/* yylex() - this is the main flex function which runs the Rule Section*/ 
	yylex();

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
	
	obj_drop(program.fip);
	obj_drop(program.ts_id);
	obj_drop(program.ts_lit);
  
	return 0;
}
