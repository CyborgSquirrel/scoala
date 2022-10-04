#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
	srandom(getpid());
	
	int a2b[2], b2a[2];
	pipe(a2b); pipe(b2a);
	
	pid_t pid_a = fork();
	if (pid_a == -1) {
		perror("fork");
	} else if (pid_a == 0) { // A
		close(a2b[0]); close(b2a[1]);
		
		int a;
		a = random()%10 + 1;
		write(a2b[1], &a, sizeof(int));
		while (read(b2a[0], &a, sizeof(int)) > 0) {
			printf("A %d\n", a);
			if (a == 10) {
				break;
			}
			a = random()%10 + 1;
			write(a2b[1], &a, sizeof(int));
		}
		close(a2b[1]); close(b2a[0]);
		
		exit(0);
	}
	
	pid_t pid_b = fork();
	if (pid_b == -1) {
		perror("fork");
	} else if (pid_b == 0) { // B
		close(b2a[0]); close(a2b[1]);
		
		int a;
		while (read(a2b[0], &a, sizeof(int)) > 0) {
			printf("B %d\n", a);
			if (a == 10) {
				break;
			}
			a = random()%10 + 1;
			write(b2a[1], &a, sizeof(int));
		}
		close(b2a[1]); close(a2b[0]);
		
		exit(0);
	}
	
	close(a2b[0]); close(a2b[1]);
	close(b2a[0]); close(b2a[1]);
	wait(0); wait(0);
	
	return 0;
}
