#include "global.h"
#include "str_hash_set.h"
#include "string_builder.h"

extern char *Global_Header = (
  "global main\n"
  "extern exit\n"
  "extern printf\n"
  "extern scanf\n"
);

StringBuilder Global_DataSegment;
StringBuilder Global_CodeSegment;

StrHashSet *Global_LitStrHashSet;
StrHashSet *Global_VarHashSet;

void Global_Init() {
  Global_DataSegment = StringBuilder_New();
  Global_CodeSegment = StringBuilder_New();
  Global_LitStrHashSet = StrHashSet_New();
  Global_VarHashSet = StrHashSet_New();
}

void Global_Uninit() {
  StringBuilder_Drop(Global_DataSegment);
  StringBuilder_Drop(Global_CodeSegment);
  StrHashSet_Drop(Global_LitStrHashSet);
  StrHashSet_Drop(Global_VarHashSet);
}
