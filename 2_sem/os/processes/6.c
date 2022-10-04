#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
	srandom(getpid());
	
	if (argc < 2) {
		fprintf(stderr, "prea putine argumente\n");
		exit(1);
	}
	
	int p2a[2], a2p[2];
	pipe(p2a); pipe(a2p);
	
	int n = atoi(argv[1]);
	int *a = malloc(n * sizeof(int));
	
	for (int i = 0; i < n; ++i) {
		a[i] = random() % 500;
	}
	
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(1);
	} else if (pid == 0) { // child
		close(p2a[1]); close(a2p[0]);
		int b;
		int s = 0;
		while (read(p2a[0], &b, sizeof(int)) > 0) {
			s += b;
		}
		close(p2a[0]);
		s /= n;
		write(a2p[1], &s, sizeof(int));
		exit(0);
	} else { // parent
		close(p2a[0]); close(a2p[1]);
		for (int i = 0; i < n; ++i) {
			write(p2a[1], &a[i], sizeof(int));
		}
		close(p2a[1]);
		int s;
		read(a2p[0], &s, sizeof(int));
		close(a2p[0]);
		printf("%d\n", s);
		exit(0);
	}
	
	free(a);
	
	return 0;
}
