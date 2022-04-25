#include <aio.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
	int status = 0;
	int p[2]; pipe(p);
	
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		status = 1;
	} else if (pid == 0) {
		close(p[0]);
		
		char *path = argv[1];
		FILE *file = fopen(path, "r");
		
		if (file == NULL) {
			perror("fopen");
			status = 1;
		} else {
			int n;
			fscanf(file, "%d", &n);
			int mat[n][n];
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					fscanf(file, "%d", &mat[i][j]);
				}
			}
			fclose(file);
			
			int sum = 0;
			for (int i = 0; i < n; ++i) {
				sum += mat[i][i];
			}
			
			if (write(p[1], &sum, sizeof(sum)) == -1) {
				perror("write");
				status = 1;
			}
		}
		close(p[1]);
		
		return status;
	}
	close(p[1]);
	
	int child_status;
	wait(&child_status);
	if (WEXITSTATUS(child_status) == 0) {
		int sum;
		if (read(p[0], &sum, sizeof(sum)) == -1) {
			perror("write");
			status = 1;
		} else {
			printf("PARENT: %d\n", sum);
		}
	}
	close(p[0]);
	
	return status;
}
