#include <stdio.h>
#include <pthread.h>

struct Args {
	int n;
	char *name;
};

void *f(void *a) {
	struct Args *ap = (struct Args *) a;
	for (int i = 0; i < ap->n; ++i) {
		printf("%s\n", (char*) ap->name);
	}
	return NULL;
}

int main(int argc, char **argv) {
	int n = 1;
	struct Args aa, ab;
	pthread_t ta, tb;
	
	if (argc > 1) {
		sscanf(argv[1], "%d", &n);
	}
	aa.n = n; aa.name = "fa";
	ab.n = n; ab.name = "fb";
	
	pthread_create(&ta, NULL, f, &aa);
	pthread_create(&tb, NULL, f, &ab);
	for (int i = 0; i < n; ++i) {
		printf("main\n");
	}
	pthread_join(ta, NULL);
	pthread_join(tb, NULL);
	
	return 0;
}
