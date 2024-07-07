#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int contains_7(int number) {
	if (number < 0) number *= -1;
	while (number > 0) {
		if (number%10 == 7) return 1;
		number /= 10;
	}
	return 0;
}

int main(int argc, char **argv) {
	srandom(getpid());
	
	int fildes_read = -1;
	int fildes_write = -1;
	
	int pipe_cycle[2];
	pipe(pipe_cycle);
	
	int n = 3;
	int root = 1;
	int leaf = 1;
	for (int i = 1; i < n && leaf; ++i) {
		int pipe_next[2];
		pipe(pipe_next);
		
		pid_t pid = fork();
		if (pid == -1) {
			perror("fork");
		} else if (pid == 0) { // child
			close(pipe_next[1]);
			if (fildes_read != -1) close(fildes_read);
			
			fildes_read = pipe_next[0];
			root = 0;
		} else { // parent
			close(pipe_next[0]);
			
			fildes_write = pipe_next[1];
			leaf = 0;
		}
	}
	
	if (!root) close(pipe_cycle[0]);
	if (!leaf) close(pipe_cycle[1]);
	
	if (leaf) fildes_write = pipe_cycle[1];
	if (root) fildes_read = pipe_cycle[0];
	
	int number = 1;
	if (root) {
		write(fildes_write, &number, sizeof(number));
	}
	
	// printf("%d %d %d %d %d\n", fildes_read, fildes_write, root, leaf, getpid());
	
	while (read(fildes_read, &number, sizeof(number)) > 0) {
		if (number == 0) {
			close(fildes_write);
			close(fildes_read);
			break;
		}
		
		number++;
		int ok = 1;
		if (number % 7 == 0 || contains_7(number)) {
			if (random() % 3 != 0) {
				printf("boltz\n");
			} else {
				// printf("inside %d %d %d\n", root, leaf, getpid());
				ok = 0;
			}
		} else {
			printf("%d\n", number);
		}
		
		if (ok) {
			write(fildes_write, &number, sizeof(number));
		} else {
			number = 0;
			write(fildes_write, &number, sizeof(number));
			close(fildes_write);
			close(fildes_read);
		}
	}
	
	// printf("before %d %d %d\n", root, leaf, getpid());
	if (!leaf) {
		wait(0);
	}
	// printf("after %d %d %d\n", root, leaf, getpid());
	
	return 0;
}
