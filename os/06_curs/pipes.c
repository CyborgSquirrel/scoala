#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	int n = 7;
	
	int p2a[2], a2b[2], b2p[2];
	pipe(p2a); pipe(a2b); pipe(b2p);
	
	pid_t a_pid = fork();
	if (a_pid == -1) { perror("fork: "); exit(1); }
	if (a_pid == 0) { // A
		while (1) {
			if (read(p2a[0], &n, sizeof(int)) <= 0) { break; }
			printf("A: %d\n", n);
			if (n == 0) { break; }
			n--;
			write(a2b[1], &n, sizeof(int));
		}
		close(p2a[1]); close(a2b[0]); close(b2p[0]); close(b2p[1]);
		close(p2a[0]); close(a2b[1]);
		printf("A done\n");
		exit(0);
	}
	
	pid_t b_pid = fork();
	if (b_pid == -1) { perror("fork: "); exit(1); }
	if (b_pid == 0) { // B
		close(p2a[0]); close(p2a[1]); close(a2b[1]); close(b2p[0]);
		while (1) {
			if (read(a2b[0], &n, sizeof(int)) <= 0) { break; }
			printf("B: %d\n", n);
			if (n == 0) { break; }
			n--;
			write(b2p[1], &n, sizeof(int));
		}
		close(a2b[0]); close(b2p[1]);
		printf("B done\n");
		exit(0);
	}
	
	// P
	close(p2a[0]); close(a2b[0]); close(a2b[1]); close(b2p[1]);
	
	write(p2a[1], &n, sizeof(int));
	while (1) {
		if (read(b2p[0], &n, sizeof(int)) <= 0) { break; }
		printf("P: %d\n", n);
		if (n == 0) { break; }
		n--;
		write(p2a[1], &n, sizeof(int));
	}
	
	close(p2a[1]); close(b2p[0]);
	printf("P done\n");
	wait(0); wait(0);
	
	return 0;
}
