/*
 * Scrieti un program C care primeste un numar N ca argument la linia
 * de comanda.
 *
 * Programul creeaza N thread-uri care vor genera numere aleatoare intre
 * 0 si 111111 (inclusiv) pana cand un thread va genera un numar divizibil
 * cu 1001.
 *
 * Thread-urile vor afisa numerele generate, iar ultimul numar afisat
 * trebuie sa fie cel divizibil cu 1001.
 *
 * Niciun thread nu va incepe sa genereze numere pana cand toate celelalte
 * thread-uri au fost create.
 *
 * Nu se vor folosi variabile globale.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
	int id;
	int *flag;
	pthread_mutex_t *mutex;
	pthread_barrier_t *barrier;
} data_t;

void *f(void *arg) {
	data_t data = *((data_t*) arg);
	
	pthread_barrier_wait(data.barrier);
	
	while (1) {
		int number = random() % (111111 + 1);
		pthread_mutex_lock(data.mutex);
		if (!*data.flag) {
			printf("thread %d says: %d\n", data.id, number);
			if (number % 1001 == 0) {
				*data.flag = 1;
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
		fprintf(stderr, "prea putini parametri\n");
		exit(1);
	}
	
	int thread_count = atoi(argv[1]);
	
	srandom(time(NULL));
	
	data_t data; {
		data.flag = malloc(sizeof(int));
		*data.flag = 0;
		
		data.mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(data.mutex, NULL);
		data.barrier = malloc(sizeof(pthread_barrier_t));
		pthread_barrier_init(data.barrier, NULL, thread_count);
	}
	
	data_t *args = malloc(sizeof(data_t) * thread_count); {
		for (int i = 0; i < thread_count; ++i) {
			args[i] = data;
			args[i].id = i;
		}
	}
	
	pthread_t threads[thread_count];
	for (int i = 0; i < thread_count; ++i) {
		pthread_create(&threads[i], NULL, f, (void*) (&args[i]));
	}
	for (int i = 0; i < thread_count; ++i) {
		pthread_join(threads[i], NULL);
	}
	
	free(data.flag);
	pthread_mutex_destroy(data.mutex);
	free(data.mutex);
	pthread_barrier_destroy(data.barrier);
	free(data.barrier);
	
	free(args);
	
	return 0;
}
