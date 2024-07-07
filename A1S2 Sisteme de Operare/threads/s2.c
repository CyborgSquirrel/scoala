/*
 * Sa se scrie un program care creeaza un numar N de thread-uri dat ca
 * argument in linia de comanda. Fiecare thread primeste ca argument
 * indexul I la care a fost creat (de la 0 la N-1).
 * 
 * Fiecare thread actioneaza pe un array global cu dimensiunea N*2,
 * care poate contine doar numere intregi, si efectueaza urmatoarele
 * operatii in ordine, dupa care isi incheie executia:
 *   1. adauga numere intregi random pe pozitia I si N+I (I = index-ul
 *   thread-ului)
 *   2. calculeaza S = suma tuturor numerelor din array din acel moment
 *   3. afiseaza aceasta suma S impreuna cu array-ul din acel moment
 *
 * Initial, array-ul cu dimensiune N*2 are toate valorile 0. Limitati
 * numarul de thread-uri care opereaza simultan asupra array-ului la
 * maxim 3. Folositi mecanismele de sincronizare necesare.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
	int i;
} data_t;

pthread_mutex_t mutex;
pthread_cond_t cond;
int workers;

pthread_mutex_t stdout_mutex;

int N;
int *arr;
void *thread_function(void *arg) {
	int i = ((data_t*) arg)->i;
	
	pthread_mutex_lock(&mutex);
		while (workers > 3) {
			pthread_cond_wait(&cond, &mutex);
		}
		workers++;
	pthread_mutex_unlock(&mutex);
	
	arr[i] = random() % 100;
	arr[i+N] = random() % 100;
	
	int S = 0;
	for (int i = 0; i < 2*N; ++i) {
		S += arr[i];
	}
	
	pthread_mutex_lock(&stdout_mutex);
		printf("%d\n", S);
		for (int i = 0; i < 2*N; ++i) {
			printf("%d ", arr[i]);
		}
		printf("\n");
	pthread_mutex_unlock(&stdout_mutex);
	
	pthread_mutex_lock(&mutex);
		workers--;
		pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);
	
	return NULL;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Prea putine argumente...");
		exit(1);
	}
	
	srandom(time(NULL));
	N = atoi(argv[1]);
	arr = malloc(N * 2 * sizeof(int));
	for (int i = 0; i < N*2; ++i) {
		arr[i] = 0;
	}
	
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);
	workers = 0;
	
	pthread_mutex_init(&stdout_mutex, NULL);
	pthread_mutex_init(&stdout_mutex, NULL);
	
	pthread_t *threads = malloc(N * sizeof(pthread_t));
	data_t *threads_data = malloc(N * sizeof(data_t));
	for (int i = 0; i < N; ++i) {
		threads_data[i].i = i;
		pthread_create(&threads[i], NULL, thread_function, &threads_data[i]);
	}
	
	for (int i = 0; i < N; ++i) {
		pthread_join(threads[i], NULL);
	}
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&stdout_mutex);
	free(threads);
	free(threads_data);
	free(arr);
	
	return 0;
}
