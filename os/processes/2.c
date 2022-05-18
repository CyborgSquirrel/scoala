#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
	int n = 5;
	
	int depth = 0;
	int have_child = 0;
	for (int i = 0; i < n && !have_child; ++i) {
		pid_t pid = fork();
		if (pid != 0) {
			have_child = 1;
		} else {
			depth++;
		}
	}
	
	for (int i = 0; i < depth; ++i) {
		printf("\t");
	}
	printf("Hello world\n");
	
	if (have_child) {
		wait(0);
	}
	
	return 0;
}
