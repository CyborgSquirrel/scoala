#include <stdio.h>
#include <stdlib.h>

// Sa se citeasca o matrice de numere intregi dintr-un fisier si sa se stocheze intr-un alt fisier. Matricea va fi stocata in memorie. Ambele nume de fisiere vor fi date ca argumente la linia de comanda.
// Pe prima linie a fisierului se vor afla numarul de linii si coloane ale matricii.

int main(int argc, char **argv) {
	if (argc < 3) {
		printf("Dati 2 fisiere pls...");
		exit(1);
	}
	FILE *fin = fopen(argv[1], "r");
	if (fin == NULL) {
		perror("Nu pot deschide fisierul de input...");
		exit(1);
	}
	
	int linii, coloane;
	if (fscanf(fin, "%d", &linii) != 1) {
		fclose(fin);
		perror("Fisierul de input ar trebui sa contina pe prima linie numarul de linii si numarul de coloane...");
		exit(1);
	}
	if (fscanf(fin, "%d", &coloane) != 1) {
		fclose(fin);
		perror("Fisierul de input ar trebui sa contina pe prima linie numarul de linii si numarul de coloane...");
		exit(1);
	}
	
	int size = linii * coloane;
	int *buf = NULL;
	if (size != 0) {
		buf = (int*) malloc(size * sizeof(int));
		if (buf == NULL) {
			fclose(fin);
			perror("Nu pot aloca memorie pentru buffer...");
			exit(1);
		} else {
			for (int i = 0; i < size; ++i) {
				if (fscanf(fin, "%d", &buf[i]) != 1) {
					fclose(fin);
					free(buf);
					perror("Prea putine numere in matrice...");
					exit(1);
				}
			}
		}
	}
	
	fclose(fin);
	
	FILE *fout = fopen(argv[2], "w");
	if (fout == NULL) {
		free(buf);
		perror("Nu pot deschide fisierul de output...");
		exit(1);
	}
	
	int k = 0;
	for (int i = 0; i < linii; ++i) {
		for (int j = 0; j < coloane; ++j) {
			fprintf(fout, "%4d ", buf[k++]);
		}
		fprintf(fout, "\n");
	}
	
	free(buf);
	fclose(fout);
	
	return 0;
}
