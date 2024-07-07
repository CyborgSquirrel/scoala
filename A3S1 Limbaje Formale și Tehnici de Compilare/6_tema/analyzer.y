%union {
	int val_int;
	char *val_str;
}

%{
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "./scanner.h"
#include "../common.h"
#include "../global.h"

enum {
	Analyzer_OpTermen_Add,
	Analyzer_OpTermen_Sub,
};

enum {
	Analyzer_OpFactor_Mul,
	Analyzer_OpFactor_Div,
};

void yyerror(char *s) {
	extern char *yytext;
	extern int line_number;
	printf("Error for symbol %s at line: %d ! \n", yytext, line_number);
	exit(1);
}

%}

/* SPECIAL ATOMS */
%token <val_str> Analyzer_Tok_Id
%token <val_int> Analyzer_Tok_LitInt
%token <val_int> Analyzer_Tok_LitStr

/* WORD ATOMS */
%token Analyzer_Tok_Fn
%token Analyzer_Tok_Main
%token Analyzer_Tok_If
%token Analyzer_Tok_While
%token Analyzer_Tok_Let
%token Analyzer_Tok_Mut
%token Analyzer_Tok_Write
%token Analyzer_Tok_Read

/* SYMBOL ATOMS */
%token Analyzer_Tok_SemiCol    // ;
%token Analyzer_Tok_LBracket   // {
%token Analyzer_Tok_RBracket   // }
%token Analyzer_Tok_LParen     // (
%token Analyzer_Tok_RParen     // )
%token Analyzer_Tok_ColCol     // ::
%token Analyzer_Tok_Col        // :
%token Analyzer_Tok_Dot        // .
%token Analyzer_Tok_Comma      // ,
%token Analyzer_Tok_Add        // +
%token Analyzer_Tok_Sub        // -
%token Analyzer_Tok_Mul        // *
%token Analyzer_Tok_Div        // /
%token Analyzer_Tok_Mod        // %
%token Analyzer_Tok_LtEq       // <=
%token Analyzer_Tok_GtEq       // >=
%token Analyzer_Tok_Lt         // <
%token Analyzer_Tok_Gt         // >
%token Analyzer_Tok_EqEq       // ==
%token Analyzer_Tok_NotEq      // !=
%token Analyzer_Tok_Not        // !
%token Analyzer_Tok_Eq         // =
%token Analyzer_Tok_RefMut     // &mut
%token Analyzer_Tok_Ref        // &

%%

program: Analyzer_Tok_Fn Analyzer_Tok_Main Analyzer_Tok_LParen Analyzer_Tok_RParen bloc_instr

bloc_instr: Analyzer_Tok_LBracket bloc_instr_inner Analyzer_Tok_RBracket
bloc_instr_inner: | instr bloc_instr_inner

instr:
	  Analyzer_Tok_SemiCol
	| instr_if
	| instr_while
	| instr_asignare Analyzer_Tok_SemiCol
	| instr_declarare Analyzer_Tok_SemiCol
	| instr_afisare Analyzer_Tok_SemiCol
	| instr_citire Analyzer_Tok_SemiCol

instr_if: Analyzer_Tok_If expr bloc_instr

instr_while: Analyzer_Tok_While expr bloc_instr

// declarare
instr_declarare:
{
	StringBuilder_Append(&Global_CodeSegment, "    ; declarare\n");
}
	Analyzer_Tok_Let instr_declarare_mut Analyzer_Tok_Id[id] instr_declarare_type Analyzer_Tok_Eq expr
{
	StrHashSet_Add(
		Global_VarHashSet,
		$id,
		NULL
	);
	
	StringBuilder_Append(&Global_CodeSegment, "    pop dword [var_");
	StringBuilder_Append(&Global_CodeSegment, $id);
	StringBuilder_Append(&Global_CodeSegment, "]\n\n");

	free($id);
}
instr_declarare_mut: |Analyzer_Tok_Mut
instr_declarare_type: |Analyzer_Tok_Col Analyzer_Tok_Id[id]
{
	free($id);
}

// asignare
instr_asignare:
{
	StringBuilder_Append(&Global_CodeSegment, "    ; asignare\n");
}
Analyzer_Tok_Id[id] Analyzer_Tok_Eq expr
{
	StringBuilder_Append(&Global_CodeSegment, "    pop dword [var_");
	StringBuilder_Append(&Global_CodeSegment, $id);
	StringBuilder_Append(&Global_CodeSegment, "]\n\n");

	free($id);
}

// afisare
instr_afisare:
{
	StringBuilder_Append(&Global_CodeSegment, "    ; afisare\n");
}
Analyzer_Tok_Write Analyzer_Tok_LParen Analyzer_Tok_LitStr[format] instr_afisare_params[params_no] Analyzer_Tok_RParen
{
	StringBuilder_Append(&Global_CodeSegment, "    push dword str_");
	StringBuilder_AppendInt(&Global_CodeSegment, $format);
	StringBuilder_Append(&Global_CodeSegment, "\n");
	StringBuilder_Append(&Global_CodeSegment, "    call printf\n");
	StringBuilder_Append(&Global_CodeSegment, "    add esi,4*");
	StringBuilder_AppendInt(&Global_CodeSegment, $<val_int>params_no+1);
	StringBuilder_Append(&Global_CodeSegment, "\n\n");
}

instr_afisare_params: 
{
	$<val_int>$ = 0;
}
|
Analyzer_Tok_Comma Analyzer_Tok_Id[id] instr_afisare_params[params_no]
{
	StringBuilder_Append(&Global_CodeSegment, "    push dword [var_");
	StringBuilder_Append(&Global_CodeSegment, $id);
	StringBuilder_Append(&Global_CodeSegment, "]\n");

	$<val_int>$ = $<val_int>params_no + 1;

	free($id);
}

// citire
instr_citire:
{
	StringBuilder_Append(&Global_CodeSegment, "    ; citire\n");
}
Analyzer_Tok_Read Analyzer_Tok_LParen Analyzer_Tok_LitStr[format] instr_citire_params[params_no] Analyzer_Tok_RParen
{
	StringBuilder_Append(&Global_CodeSegment, "    push dword str_");
	StringBuilder_AppendInt(&Global_CodeSegment, $format);
	StringBuilder_Append(&Global_CodeSegment, "\n");
	StringBuilder_Append(&Global_CodeSegment, "    call scanf\n");
	StringBuilder_Append(&Global_CodeSegment, "    add esi,4*");
	StringBuilder_AppendInt(&Global_CodeSegment, $<val_int>params_no+1);
	StringBuilder_Append(&Global_CodeSegment, "\n\n");
}

instr_citire_params:
{
	$<val_int>$ = 0;
}
|
Analyzer_Tok_Comma Analyzer_Tok_RefMut Analyzer_Tok_Id[id] instr_citire_params[params_no]
{
	StringBuilder_Append(&Global_CodeSegment, "    push dword var_");
	StringBuilder_Append(&Global_CodeSegment, $id);
	StringBuilder_Append(&Global_CodeSegment, "\n");
	
	$<val_int>$ = $<val_int>params_no + 1;

	free($id);
}

expr_primara:
Analyzer_Tok_Id[id]
{
	StringBuilder_Append(&Global_CodeSegment, "    push dword [var_");
	StringBuilder_Append(&Global_CodeSegment, $id);
	StringBuilder_Append(&Global_CodeSegment, "]\n");

	free($id);
}
|
Analyzer_Tok_LitInt[val]
{
	StringBuilder_Append(&Global_CodeSegment, "    push dword ");
	// Yes, I know val gets converted back and forth from string to int. So what
	// @_@.
	StringBuilder_AppendInt(&Global_CodeSegment, $val);
	StringBuilder_Append(&Global_CodeSegment, "\n");
}

op_factor:
  Analyzer_Tok_Mul { $<val_int>$ = Analyzer_OpFactor_Mul; }
| Analyzer_Tok_Div { $<val_int>$ = Analyzer_OpFactor_Div; }
	
expr_factor:
  expr_primara
| expr_primara op_factor[op] expr_factor
{
	StringBuilder_Append(
		&Global_CodeSegment,
		"    pop ebx\n"
		"    pop eax\n"
	);
	
	switch ($<val_int>op) {
		case Analyzer_OpFactor_Mul: {
			StringBuilder_Append(&Global_CodeSegment, "    mul ebx\n");
			break;
		}
		case Analyzer_OpFactor_Div: {
			StringBuilder_Append(&Global_CodeSegment, "    div ebx\n");
			break;
		}
		default: {
			assert(0);
		}
	}
	
	StringBuilder_Append(
		&Global_CodeSegment,
		"    push eax\n"
	);
}

op_termen:
  Analyzer_Tok_Add { $<val_int>$ = Analyzer_OpTermen_Add; }
| Analyzer_Tok_Sub { $<val_int>$ = Analyzer_OpTermen_Sub; }

expr_termen:
  expr_factor
| expr_factor op_termen[op] expr_termen
{
	StringBuilder_Append(
		&Global_CodeSegment,
		"    pop ebx\n"
		"    pop eax\n"
	);
	
	switch ($<val_int>op) {
		case Analyzer_OpTermen_Add: {
			StringBuilder_Append(&Global_CodeSegment, "    add eax, ebx\n");
			break;
		}
		case Analyzer_OpTermen_Sub: {
			StringBuilder_Append(&Global_CodeSegment, "    sub eax, ebx\n");
			break;
		}
		default: {
			assert(0);
		}
	}
	
	StringBuilder_Append(
		&Global_CodeSegment,
		"    push eax\n"
	);
}

expr: expr_termen
%%

void Analyzer_Analyze() {
    while (!feof(yyin)) {
        yyparse();
    }
}
