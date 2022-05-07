#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void *f(void *arg) {
	int *fr = malloc(10 * sizeof(int));
	memset(fr, 0, 10 * sizeof(int));
	char *str = (char*) arg;
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] >= '0' && str[i] <= '9') {
			fr[str[i] - '0']++;
		}
	}
	return (void*) fr;
}

int main(int argc, char **argv) {
	int total_fr[10];
	for (int i = 0; i < 10; ++i) {
		total_fr[i] = 0;
	}
	
	pthread_t *th = (pthread_t*) malloc((argc-1) * sizeof(pthread_t));
	for (int i = 1; i < argc; ++i) {
		pthread_create(&th[i-1], NULL, f, argv[i]);
	}
	
	for (int i = 1; i < argc; ++i) {
		int *fr;
		pthread_join(th[i-1], (void*)(&fr));
		for (int i = 0; i < 10; ++i) {
			total_fr[i] += fr[i];
		}
		free(fr);
	}
	
	for (int i = 0; i < 10; ++i) {
		printf("%d %d\n", i, total_fr[i]);
	}
	
	free(th);
	
	return 0;
}
