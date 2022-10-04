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
	int **matrice = NULL;
	if (size != 0) {
		matrice = (int**) malloc(linii * sizeof(int*));
		if (matrice == NULL) {
			fclose(fin);
			perror("Nu pot aloca memorie pentru matrice...");
			exit(1);
		} else {
			for (int i = 0; i < linii; ++i) {
				matrice[i] = (int*) malloc(coloane * sizeof(int));
				if (matrice == NULL) {
					for (int j = 0; j < i; ++j) free(matrice[j]);
					free(matrice);
					fclose(fin);
					perror("Nu pot aloca memorie pentru matrice...");
					exit(1);
				}
			}
			for (int i = 0; i < linii; ++i) {
				for (int j = 0; j < coloane; ++j) {
					if (fscanf(fin, "%d", &matrice[i][j]) != 1) {
						fclose(fin);
						for (int i = 0; i < linii; ++i) free(matrice[i]);
						free(matrice);
						perror("Prea putine numere in matrice...");
						exit(1);
					}
				}
			}
		}
	}
	
	fclose(fin);
	
	FILE *fout = fopen(argv[2], "w");
	if (fout == NULL) {
		for (int i = 0; i < linii; ++i) free(matrice[i]);
		free(matrice);
		perror("Nu pot deschide fisierul de output...");
		exit(1);
	}
	
	for (int i = 0; i < linii; ++i) {
		for (int j = 0; j < coloane; ++j) {
			fprintf(fout, "%4d ", matrice[i][j]);
		}
		fprintf(fout, "\n");
	}
	
	for (int i = 0; i < linii; ++i) free(matrice[i]);
	free(matrice);
	fclose(fout);
	
	return 0;
}
