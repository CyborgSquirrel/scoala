#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./target/analyzer.h"
#include "./target/scanner.h"
#include "global.h"

void Analyzer_Analyze();

extern FILE *yyin;

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("not enough arguments\n");
        exit(1);
    }

    // input for flex
    FILE *fin = fopen(argv[1], "r");
    yyin = fin;

    // do it
    Global_Init();

    StringBuilder_Append(
        &Global_CodeSegment,
        "section .text\n"
        "main:\n"
    );

    Analyzer_Analyze();
    printf("The file is syntactically correct!\n");

    StringBuilder_Append(
        &Global_CodeSegment,
        "    push dword 0\n"
        "    call exit\n"
    );

    // data segment
    StringBuilder_Append(&Global_DataSegment, "section .data\n");
    for (int i = 0; i < StrHashSet_Size; ++i) {
        char *value = Global_LitStrHashSet->values[i];
        if (value == NULL) {
            continue;
        }

        StringBuilder_Append   (&Global_DataSegment, "    str_");
        StringBuilder_AppendInt(&Global_DataSegment, i);
        StringBuilder_Append   (&Global_DataSegment, " db ");
        for (int i = 0; value[i] != '\0'; ++i) {
            StringBuilder_AppendInt(&Global_DataSegment, value[i]);
            StringBuilder_Append   (&Global_DataSegment, ",");
        }
        StringBuilder_Append   (&Global_DataSegment, "0\n");
    }
    for (int i = 0; i < StrHashSet_Size; ++i) {
        char *value = Global_VarHashSet->values[i];
        if (value == NULL) {
            continue;
        }

        StringBuilder_Append(&Global_DataSegment, "    var_");
        StringBuilder_Append(&Global_DataSegment, value);
        StringBuilder_Append(&Global_DataSegment, " dd 0\n");
    }

    // write everything
    {
        FILE *fout = fopen(argv[2], "w");

        fputs(Global_Header, fout);
        fputs("\n", fout);

        char *data_segment;
        StringBuilder_Build(&Global_DataSegment, &data_segment);
        fputs(data_segment, fout);
        fputs("\n", fout);
        free(data_segment);

        char *code_segment;
        StringBuilder_Build(&Global_CodeSegment, &code_segment);
        fputs(code_segment, fout);
        fputs("\n", fout);
        free(code_segment);

        fclose(fout);
    }

    Global_Uninit();

    return 0;
}
