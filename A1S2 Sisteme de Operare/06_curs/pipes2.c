#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	int parent = 1;
	char c = 'P';
	int n = 7;
	
	int p2a[2], a2b[2], b2p[2];
	pipe(p2a); pipe(a2b); pipe(b2p);
	
	int fr, fw;
	
	pid_t a_pid = fork();
	if (a_pid == -1) { perror("fork: "); exit(1); }
	if (a_pid == 0) { // A
		parent = 0;
		c = 'A';
		close(p2a[1]); close(a2b[0]); close(b2p[0]); close(b2p[1]);
		fr = p2a[0]; fw = a2b[1];
	}
	
	pid_t b_pid = fork();
	if (b_pid == -1) { perror("fork: "); exit(1); }
	if (b_pid == 0) { // B
		parent = 0;
		c = 'B';
		close(p2a[0]); close(p2a[1]); close(a2b[1]); close(b2p[0]);
		fr = a2b[0]; fw = b2p[1];
	}
	
	if (parent) { // P
		close(p2a[0]); close(a2b[0]); close(a2b[1]); close(b2p[1]);
		fr = b2p[0]; fw = p2a[1];
	}
	
	write(p2a[1], &n, sizeof(int));
	while (1) {
		if (read(fr, &n, sizeof(int)) <= 0) { break; }
		printf("%c: %d\n", c, n);
		if (n == 0) { break; }
		n--;
		write(fw, &n, sizeof(int));
	}
	
	close(fr); close(fw);
	if (parent) { wait(0); wait(0); }
	
	return 0;
}
