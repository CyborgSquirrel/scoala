#include "string_builder.h"
#include "str_hash_set.h"

extern char *Global_Header;

extern StringBuilder Global_DataSegment;
extern StringBuilder Global_CodeSegment;

extern StrHashSet *Global_LitStrHashSet;
extern StrHashSet *Global_VarHashSet;

void Global_Init();
void Global_Uninit();
