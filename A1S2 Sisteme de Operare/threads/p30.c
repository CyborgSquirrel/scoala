/*
 *  30. Relay: Create a C program that reads a number n from the standard
 *  input and created 4 * n threads. The threads will be split into teams
 *  of 4. In each team the threads will be numbered from 0 and will run
 *  according to the relay rules:
 *
 * - Thread 0 from each theam starts, waits (usleep) between 100 and 200
 * milliseconds, then passes the control to thread 1
 *
 * - Thread 1 waits between 100 and 200 milliseconds then passes the
 * control to thread 2
 *
 * - Thread 2 waits between 100 and 200 milliseconds then passes the
 * control to thread 3
 *
 * - Thread 3 waits between 100 and 200 milliseconds, then prints a
 * message indicating that the team has finished, then terminates.
 *
 * The team from which thread 3 terminates first is considered the
 * winning team. Use appropriate synchronization mechanisms.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
	int level, team;
	int *team_level;
	pthread_mutex_t *mutex;
	pthread_cond_t *cond;
} data_t;

pthread_barrier_t barrier;

pthread_mutex_t winner_mutex;
int winner = -1;

void *f(void *arg) {
	pthread_barrier_wait(&barrier);
	
	data_t *data = (data_t*) arg;
	
	pthread_mutex_lock(data->mutex);
	while (*data->team_level != data->level) {
		pthread_cond_wait(data->cond, data->mutex);
	}
	
	int sleep_ms = random() % (100+1) + 100;
	usleep(sleep_ms);
	// printf("%d\n", sleep_ms);
	
	if (data->level == 3) {
		pthread_mutex_lock(&winner_mutex);
		if (winner == -1) {
			winner = data->team;
		}
		pthread_mutex_unlock(&winner_mutex);
	}
	
	(*data->team_level)++;
	pthread_cond_broadcast(data->cond);
	pthread_mutex_unlock(data->mutex);
	
	return NULL;
}

int main(int argc, char **argv) {
	srandom(time(NULL));
	int n;
	scanf("%d", &n);
	
	pthread_mutex_init(&winner_mutex, NULL);
	pthread_barrier_init(&barrier, NULL, 4*n);
	
	int *levels = (int*) malloc(n * sizeof(int));
	for (int i = 0; i < n; ++i) {
		levels[i] = 0;
	}
	
	pthread_mutex_t *mutexes = malloc(n * sizeof(pthread_mutex_t));
	for (int i = 0; i < n; ++i) {
		pthread_mutex_init(&mutexes[i], NULL);
	}
	
	pthread_cond_t *conds = malloc(n * sizeof(pthread_cond_t));
	for (int i = 0; i < n; ++i) {
		pthread_cond_init(&conds[i], NULL);
	}
	
	pthread_t **threads = malloc(4 * sizeof(pthread_t*));
	data_t *datas = malloc(4 * n * sizeof(data_t));
	int data_i = 0;
	for (int i = 0; i < 4; ++i) {
		threads[i] = malloc(n * sizeof(pthread_t));
		for (int j = 0; j < n; ++j) {
			datas[data_i].level = i;
			datas[data_i].team = j;
			datas[data_i].team_level = &levels[j];
			datas[data_i].mutex = &mutexes[j];
			datas[data_i].cond = &conds[j];
			pthread_create(&threads[i][j], NULL, f, (void*) &datas[data_i]);
			data_i++;
		}
	}
	
	for (int i = 0; i < n; ++i) {
		pthread_mutex_destroy(&mutexes[i]);
	}
	free(mutexes);
	
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < n; ++j) {
			pthread_join(threads[i][j], NULL);
		}
		free(threads[i]);
	}
	free(threads);
	free(datas);
	
	for (int i = 0; i < n; ++i) {
		pthread_cond_destroy(&conds[i]);
	}
	free(conds);
	
	pthread_mutex_destroy(&winner_mutex);
	pthread_barrier_destroy(&barrier);
	free(levels);
	
	printf("The winner is team %d.\n", winner+1);
	
	return 0;
}
