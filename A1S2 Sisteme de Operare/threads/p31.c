/*
 * Scrieti un program C care primeste un numar N ca argument la linia
 * de comanda. Programul creeaza N thread-uri care vor genera numere
 * aleatoare intre 0 si 111111 (inclusiv) pana cand un thread va genera
 * un numar divizibil cu 1001.
 * 
 * Thread-urile vor afisa numerele generate, iar ultimul numar afisat
 * trebuie sa fie cel divizibil cu 1001. Niciun thread nu va incepe sa
 * genereze numere pana cand toate celelalte thread-uri au fost create. Nu
 * se vor folosi variabile globale.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
	int N;
	pthread_barrier_t *barrier;
	pthread_mutex_t *mutex;
	int *finished;
} data_t;

void *thread_function(void *arg) {
	data_t data = *((data_t*) arg);
	
	pthread_barrier_wait(data.barrier);
	while (1) {
		int number = random()%(111111+1);
		pthread_mutex_lock(data.mutex);
		if (!*data.finished) {
			printf("%d\n", number);
			if (number%1001 == 0) {
				*data.finished = 1;
				break;
			}
		} else {
			break;
		}
		pthread_mutex_unlock(data.mutex);
	}
	pthread_mutex_unlock(data.mutex);
	
	return NULL;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Prea putine argumente...\n");
		exit(1);
	}
	
	srandom(time(NULL));
	
	int N = atoi(argv[1]);
	int finished = 0;
	pthread_barrier_t barrier;   pthread_barrier_init(&barrier, NULL, N);
	pthread_mutex_t mutex;       pthread_mutex_init(&mutex, NULL);
	
	pthread_t *threads = malloc(N * sizeof(pthread_t));
	data_t *datas = malloc(N * sizeof(data_t));
	for (int i = 0; i < N; ++i) {
		datas[i].N = N;
		datas[i].barrier = &barrier;
		datas[i].mutex = &mutex;
		datas[i].finished = &finished;
		pthread_create(&threads[i], NULL, thread_function, &datas[i]);
	}
	
	for (int i = 0; i < N; ++i) {
		pthread_join(threads[i], NULL);
	}
	pthread_barrier_destroy(&barrier);
	pthread_mutex_destroy(&mutex);
	free(threads);
	free(datas);
	
	return 0;
}
