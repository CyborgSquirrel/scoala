#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
	int n = 5;
	
	int child = 0;
	for (int i = 0; i < n && !child; ++i) {
		pid_t pid = fork();
		if (pid == 0) {
			child = 1;
		} else {
			printf("Parent { my pid: %d child pid: %d }\n", getpid(), pid);
		}
	}
	printf("Child { my pid: %d parent pid: %d }\n", getpid(), getppid());
	
	if (!child) {
		for (int i = 0; i < n; ++i) {
			wait(0);
		}
	}
	
	return 0;
}
