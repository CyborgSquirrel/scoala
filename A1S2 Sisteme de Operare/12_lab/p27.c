/*
 * Scrieti un program C care primeste doua numere, N si M, ca argumente la
 * linia de comanda. Programul creeaza N thread-uri care genereaza litere
 * mici ale alfabetului aleator si le adauga unui sir de caractere cu
 * 128 de pozitii. Programul mai creeaza un thread care asteapta ca toate
 * pozitiile sirului de caractere sa fie ocupate, moment in care afiseaza
 * sirul si apoi seteaza toate pozitiile sirului la NULL. Thread-urile
 * si procesul principal isi incheie executia dupa ce se genereaza M
 * astfel de siruri de caractere.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int N, M;

int m;
pthread_cond_t consumer_cond;

pthread_mutex_t string_mutex;
int the_index;
char string[128];

void *producer_thread_f(void*) {
	while (m < M) {
		pthread_mutex_lock(&string_mutex);
		if (the_index < 128-1) {
			char letter = 'a' + random()%26;
			string[the_index++] = letter;
		} else {
			pthread_cond_signal(&consumer_cond);
		}
		pthread_mutex_unlock(&string_mutex);
	}
	
	return NULL;
}

void *consumer_thread_f(void*) {
	pthread_mutex_lock(&string_mutex);
	while (m < M) {
		while (the_index < 128-1) {
			pthread_cond_wait(&consumer_cond, &string_mutex);
		}
		
		printf("%s\n", string);
		for (int i = 0; i < 128-1; ++i) {
			string[i] = '\0';
		}
		m++;
		the_index = 0;
	}
	pthread_mutex_unlock(&string_mutex);
	return NULL;
}

int main(int argc, char **argv) {
	m = 0;
	the_index = 0;
	string[127] = '\0';
	
	if (argc < 3) {
		fprintf(stderr, "prea putine argumente...\n");
		exit(1);
	}
	
	srandom(time(NULL));
	
	N = atoi(argv[1]);
	M = atoi(argv[2]);
	
	pthread_cond_init(&consumer_cond, NULL);
	pthread_mutex_init(&string_mutex, NULL);
	
	pthread_t *producer_threads = malloc(sizeof(pthread_t) * N);
	for (int i = 0; i < N; ++i) {
		pthread_create(&producer_threads[i], NULL, producer_thread_f, NULL);
	}
	
	pthread_t consumer_thread;
	pthread_create(&consumer_thread, NULL, consumer_thread_f, NULL);
	
	for (int i = 0; i < N; ++i) {
		pthread_join(producer_threads[i], NULL);
	}
	pthread_join(consumer_thread, NULL);
	free(producer_threads);
	
	pthread_cond_destroy(&consumer_cond);
	pthread_mutex_destroy(&string_mutex);
	
	return 0;
}
