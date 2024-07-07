#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

pid_t child;

int run;

void signal_parent(int) {
	kill(child, SIGUSR1);
	run = 0;
}

void signal_child(int) {
	run = 0;
}

void signal_zombie(int) {
	run = 0;
}

int main(int argc, char **argv) {
	run = 1;
	
	child = fork();
	if (child == -1) {
		perror("fork");
		exit(1);
	} else if (child != 0) { // parent
		printf("parent %d\n", getpid());
		signal(SIGUSR1, signal_parent);
		signal(SIGCHLD, signal_zombie);
		while (run) { }
		wait(0);
		printf("parent done\n");
	} else { // child
		printf("child %d\n", getpid());
		signal(SIGUSR1, signal_child);
		while (run) { }
		printf("child done\n");
	}
	
	return 0;
}
