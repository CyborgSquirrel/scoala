#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

pthread_mutex_t m;

int n = 500;

void *f(void *) {
	while (1) {
		pthread_mutex_lock(&m);
		if (n < 0 || n > 1000) {
			pthread_mutex_unlock(&m);
			break;
		}
		n += random() % 1001 - 500;
		// printf("%d\n", n);
		pthread_mutex_unlock(&m);
	}
	return NULL;
}

int main(int argc, char **argv) {
	srandom(time(0));
	
	pthread_t th[2];
	
	pthread_mutex_init(&m, NULL);
	
	pthread_create(&th[0], NULL, f, NULL);
	pthread_create(&th[1], NULL, f, NULL);
	
	pthread_join(th[0], NULL);
	pthread_join(th[1], NULL);
	
	pthread_mutex_destroy(&m);
	
	printf("%d\n", n);
	
	return 0;
}
