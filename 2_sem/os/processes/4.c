#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int cmd_argc = argc-1;
	if (cmd_argc <= 0) {
		fprintf(stderr, "not enough arguments\n");
		exit(1);
	}
	
	char **cmd_argv_in = argv+1;
	
	char **cmd_argv = malloc((cmd_argc+1) * sizeof(char*));
	for (int i = 0; i < cmd_argc; ++i) {
		cmd_argv[i] = cmd_argv_in[i];
	}
	cmd_argv[cmd_argc] = NULL;
	char *cmd_name = cmd_argv[0];
	
	time_t start = time(NULL);
	
	pid_t pid = fork();
	if (pid == 0) {
		execvp(cmd_name, cmd_argv);
		perror("execvp");
		exit(1);
	}
	free(cmd_argv);
	wait(0);
	
	time_t end = time(NULL);
	
	double delta = difftime(end, start);
	printf("Time elapsed: %f seconds.\n", delta);
	
	return 0;
}
