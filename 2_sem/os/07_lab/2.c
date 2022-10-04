#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int random_int(int lo, int hi) {
	long int delta = hi - lo + 1;
	return random() % delta + (long int) lo;
}

int main() {
	int status = 0;
	
	srandom(getpid());
	
	int a2b[2];
	pipe(a2b);
	
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		status = 1;
	} else if (pid == 0) {
		// B
		close(a2b[1]);
		
		int n = random_int(100, 1000);
		
		int done = 0;
		while (!done && status == 0) {
			int m;
			if (read(a2b[0], &m, sizeof(m)) == -1) {
				status = 1;
			} else {
				if (abs(n-m) < 50) {
					done = 1;
				}
			}
		}
		
		close(a2b[0]);
		return status;
	}
	
	// A
	close(a2b[0]);
	
	int writing = 1;
	while (writing) {
		int n = random_int(50, 1050);
		write(a2b[1], &n, sizeof(n));
	}
	
	wait(0);
	close(a2b[0]);
	return status;
}
