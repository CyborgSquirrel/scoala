#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./target/analyzer.h"
#include "./target/scanner.h"

extern void scan_init();
extern void scan_print();
extern void scan_drop();
extern void anl();

extern FILE *yyin;

int main(int argc, char **argv) {
    // sets the input for flex file
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }

    scan_init();

    anl();
    printf("The file is syntactically correct!\n");
    scan_print();

    scan_drop();

    return 0;
}
