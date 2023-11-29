#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./target/analyzer.h"
#include "./target/scanner.h"

extern void anl();
extern int cuvinte_nr;
extern int ceremonii_nr;

extern FILE *yyin;

int main(int argc, char **argv) {
    // sets the input for flex file
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }

    anl();
    printf("The file is syntactically correct!\n");
    printf("In fisier s-au gasit %d cuvinte.\n", cuvinte_nr);
    printf("In fisier s-au gasit %d derivari ale cuvantului 'ceremonie'.\n", ceremonii_nr);

    return 0;
}
