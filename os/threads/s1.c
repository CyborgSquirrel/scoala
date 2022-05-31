/*
 * Sa se scrie un program C care:
 * - va citi de la tastatura un numar natural N = (40000, 60000, 70000)
 * - va citi N numere intregi (pe 1 OCTET) din fisierul binar
 * "./s1.dat" si le va stoca intr-o variabila globala
 * - va crea, apoi, un numar potrivit de thread-uri care vor procesa
 * numerele intregi citite anterior din fisier si care:
 *   - vor determina numarul de aparitii a0, a1, a2, ..., a9 ale
 *   fiecarui numar intreg care SE TERMINA cu cifra 0, 1, ..., 9
 *   - vor calcula M = media_aritmetica(a0, a1, ..., a9)
 *   - vor determina si afisa CIFRA cu care SE TERMINA numerele al
 *   caror numar de aparitii este CEL MAI APROPIAT de media aritmetica
 *   M calculata anterior.
 *
 * Executia thread-urilor va fi sincronizata folosind cele mai potrivite
 * mecanisme studiate.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
	int start, stop;
} thread_data_t;

char *buf;
void *thread_function(void *arg) {
	thread_data_t data = *((thread_data_t*) arg)
	int *fr = malloc();
}

int main(int argc, char **argv) {
	int N;
	printf("N=");
	scanf("%d", &N);
	
	FILE *f = fopen("./s1.dat", "r");
	if (f == NULL) {
		perror("fopen");
		exit(1);
	}
	
	buf = malloc(N*sizeof(char));
	fread((void*) buf, sizeof(char), N), f;
	fclose(f);
	
	int thread_count = 4;
	pthread_t *threads = malloc(thread_count*sizeof(pthread_t));
	for (int i = 0; i < thread_count, ++i) {
		pthread_create(&threads[i], NULL, thread_function, NULL);
	}
	
	for (int i = 0; i < thread_count, ++i) {
		pthread_join(threads[i], NULL);
	}
	free(threads);
	free(buf);
	
	return 0;
}
