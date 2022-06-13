/*
 * Scrieti un program C care citeste un numar n si creeaza un sir s de n
 * numere aleatoare intre 0 si 1000. Dupa ce sirul este creat, procesul
 * principal creeaza n + 1 thread-uri. Fiecare din primele n thread-uri
 * repeta urmatorii pasi pana cand sirul s este sortat ascendent:
 *   - genereaza 2 intregi aleatori intre 0 si n-1, numiti i si j
 *   - daca i < j si s[i] > s[j] interschimba s[i] si s[j]
 *   - daca i > j si s[i] < s[j] interschimba s[i] si s[j]
 * Thread-ul n+1 asteapta pana cand sirul este sortat, dupa care il
 * afiseaza. Folositi mecanisme de sincronizare corespunzatoare.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *s;
int n;

pthread_mutex_t *mutexes;

int sorted;
pthread_mutex_t mutex;
pthread_cond_t cond;

void *sorter_thread_function(void *) {
	int sorted_local = 0;
	while (1) {
		sorted_local = 1;
		pthread_mutex_lock(&mutex);
			if (!sorted) {
				for (int i = 1; i < n && sorted_local; ++i) {
					if (s[i-1] > s[i]) {
						sorted_local = 0;
					}
				}
				if (sorted_local) {
					sorted = 1;
					pthread_cond_signal(&cond);
					pthread_mutex_unlock(&mutex);
					break;
				}
			} else {
				pthread_mutex_unlock(&mutex);
				break;
			}
		pthread_mutex_unlock(&mutex);
		
		int i = random()%n;
		int j = random()%n;
		if (i > j) {
			int aux = i;
			i = j;
			j = aux;
		}
		
		if (i != j) {
			pthread_mutex_lock(&mutexes[i]);
			pthread_mutex_lock(&mutexes[j]);
				if (s[i] > s[j]) {
					int aux = s[i];
					s[i] = s[j];
					s[j] = aux;
				}
			pthread_mutex_unlock(&mutexes[i]);
			pthread_mutex_unlock(&mutexes[j]);
		}
	}
	
	return NULL;
}

void *waiter_thread_function(void *) {
	pthread_mutex_lock(&mutex);
	while (!sorted) {
		pthread_cond_wait(&cond, &mutex);
	}
	for (int i = 0; i < n; ++i) {
		printf("%d ", s[i]);
	}
	printf("\n");
	pthread_mutex_unlock(&mutex);
	
	return NULL;
}

int main(int argc, char **argv) {
	srandom(time(NULL));
	sorted = 0;
	
	scanf("%d", &n);
	
	s = malloc(n * sizeof(int));
	for (int i = 0; i < n; ++i) {
		s[i] = random()%(1000+1);
	}
	
	pthread_mutex_init(&mutex, NULL);
	mutexes = malloc(n * sizeof(pthread_mutex_t));
	for (int i = 0; i < n; ++i) {
		pthread_mutex_init(&mutexes[i], NULL);
	}
	
	pthread_t *sorter_threads = malloc(n * sizeof(pthread_t));
	for (int i = 0; i < n; ++i) {
		pthread_create(&sorter_threads[i], NULL, sorter_thread_function, NULL);
	}
	
	pthread_t waiter_thread;
	pthread_create(&waiter_thread, NULL, waiter_thread_function, NULL);
	
	for (int i = 0; i < n; ++i) {
		pthread_join(sorter_threads[i], NULL);
	}
	free(sorter_threads);
	pthread_join(waiter_thread, NULL);
	
	pthread_mutex_destroy(&mutex);
	for (int i = 0; i < n; ++i) {
		pthread_mutex_destroy(&mutexes[i]);
	}
	free(mutexes);
	free(s);
	
	return 0;
}
