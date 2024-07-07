/*
 * Scrieti un program C care citeste un numar n de la tastatura si apoi
 * creeaza n thread-uri numerotate de la 0 la n - 1. Fiecare thread pune
 * un numar aleator intre 10 si 20 pe pozitia indicata de indexul sau
 * intr-un sir de intregi. Dupa ce toate thread-urile au adaugat numarul
 * in sir, fiecare thread repeta urmatorii pasi:
 *   - Verifica daca numarul din sir de pe indexul sau este mai mare ca 0.
 *   - Daca da, scade 1 din toate numerele din sir exceptand numarul de
 *   pe pozitia sa.
 *   - Daca nu, isi incheie executia.
 *   - Daca nu mai exista numere mai mari ca 0 in sir, exceptand numarul
 *  de pe pozitia sa, atunci isi incheie executia.
 * Dupa ce toate thread-urile isi incheie executia, procesul principal
 * afiseaza sirul de numere. Folositi mecanisme de sincronizare
 * corespunzatoare.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
	int index;
} data_t;

int n;
int *arr;

pthread_barrier_t barrier;
pthread_mutex_t mutex;

void *thread_function(void *arg) {
	data_t data = *((data_t*) arg);
	
	int number = random()%(20-10+1) + 10;
	arr[data.index] = number;
	
	pthread_barrier_wait(&barrier);
	
	while (1) {
		pthread_mutex_lock(&mutex);
		if (arr[data.index] > 0) {
			int stop = 1;
			for (int i = 0; i < n; ++i) {
				if (i != data.index) {
					arr[i] -= 1;
					if (arr[i] > 0) {
						stop = 0;
					}
				}
			}
			if (stop) {
				break;
			}
		} else {
			break;
		}
		pthread_mutex_unlock(&mutex);
	}
	pthread_mutex_unlock(&mutex);
	
	return NULL;
}

int main(int argc, char **argv) {
	srandom(time(NULL));
	
	scanf("%d", &n);
	
	arr = malloc(n * sizeof(int));
	
	pthread_barrier_init(&barrier, NULL, n);
	pthread_mutex_init(&mutex, NULL);
	pthread_t *threads = malloc(n * sizeof(pthread_t));
	data_t *datas = malloc(n * sizeof(data_t));
	for (int i = 0; i < n; ++i) {
		datas[i].index = i;
		pthread_create(&threads[i], NULL, thread_function, &datas[i]);
	}
	
	for (int i = 0; i < n; ++i) {
		pthread_join(threads[i], NULL);
	}
	free(threads);
	free(datas);
	
	for (int i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	free(arr);
	
	return 0;
}
