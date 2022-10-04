#include <pthread.h>
#include <stdio.h>

pthread_mutex_t m;

int n = 0;

void *f(void *) {
	for (int i = 0; i < 1000000; ++i) {
		pthread_mutex_lock(&m);
		n++;
		pthread_mutex_unlock(&m);
	}
	return NULL;
}

int main(int argc, char **argv) {
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
