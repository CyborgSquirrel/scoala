%{

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "analyzer.h"
#include "../global.h"

int error_found = 0;
extern int line_number = 1;
%}

%option noyywrap

ID [a-zA-Z][a-zA-Z0-9_]{0,249}|_[a-zA-Z0-9_]{1,249}
LIT_INT 0b[01]+|0o[0-7]+|[0-9]+|0x[0-9a-fA-F]+
LIT_FLOAT [0-9]+"."[0-9]*
LIT_STR \"[a-zA-Z0-9{} =%\\]*\"

/*** Rule Section ***/
%%
fn         { return Analyzer_Tok_Fn    ; }
main       { return Analyzer_Tok_Main  ; }
if         { return Analyzer_Tok_If    ; }
while      { return Analyzer_Tok_While ; }
let        { return Analyzer_Tok_Let   ; }
mut        { return Analyzer_Tok_Mut   ; }
"write!"   { return Analyzer_Tok_Write ; }
"read!"    { return Analyzer_Tok_Read  ; }

{ID} {
  char *text = malloc((yyleng+1) * sizeof(char));
  strncpy(text, yytext, yyleng);
  text[yyleng] = '\0';

  // TODO: Free this sometime?
  yylval.val_str = text;

  return Analyzer_Tok_Id;
}

{LIT_INT} {
  yylval.val_int = atoi(yytext);

  return Analyzer_Tok_LitInt;
}

{LIT_STR} {
  size_t len = 0;
  {
    char escape = 0;
    for (int i = 1; i < yyleng-1; ++i) {
      if (escape) {
        len += 1;
        escape = 0;
      } else {
        if (yytext[i] == '\\') {
          escape = 1;
        } else {
          len += 1;
        }
      }
    }
  }
  
  char *text = malloc((len+1) * sizeof(char));
  {
    int text_i = 0;

    char escape = 0;
    for (int i = 1; i < yyleng-1; ++i) {
      if (escape) {
        if (yytext[i] == 'n') {
          text[text_i++] = '\n';
        } else {
          text[text_i++] = yytext[i];
        }
        escape = 0;
      } else {
        if (yytext[i] == '\\') {
          escape = 1;
        } else {
          text[text_i++] = yytext[i];
        }
      }
    }
  }
  text[len] = '\0';

  int id;
  StrHashSet_Add(
    Global_LitStrHashSet,
    text,
    &id
  );
  yylval.val_int = id;
  free(text);

  return Analyzer_Tok_LitStr;
}

";"           { return Analyzer_Tok_SemiCol  ; }
"{"           { return Analyzer_Tok_LBracket ; }
"}"           { return Analyzer_Tok_RBracket ; }
"("           { return Analyzer_Tok_LParen   ; }
")"           { return Analyzer_Tok_RParen   ; }
"::"          { return Analyzer_Tok_ColCol   ; }
":"           { return Analyzer_Tok_Col      ; }
"."           { return Analyzer_Tok_Dot      ; }
","           { return Analyzer_Tok_Comma    ; }
"+"           { return Analyzer_Tok_Add      ; }
"-"           { return Analyzer_Tok_Sub      ; }
"*"           { return Analyzer_Tok_Mul      ; }
"/"           { return Analyzer_Tok_Div      ; }
"%"           { return Analyzer_Tok_Mod      ; }
"<="          { return Analyzer_Tok_LtEq     ; }
">="          { return Analyzer_Tok_GtEq     ; }
"<"           { return Analyzer_Tok_Lt       ; }
">"           { return Analyzer_Tok_Gt       ; }
"=="          { return Analyzer_Tok_EqEq     ; }
"!="          { return Analyzer_Tok_NotEq    ; }
"!"           { return Analyzer_Tok_Not      ; }
"="           { return Analyzer_Tok_Eq       ; }
"&mut"        { return Analyzer_Tok_RefMut   ; }
"&"           { return Analyzer_Tok_Ref      ; }

[\n]     { ++line_number; }
[ \t]+   { ; /* eat up whitespace */ }
.        { error_found = 1; printf("Illegal token %s at line %d !", yytext, line_number); printf("\n"); }
%%
