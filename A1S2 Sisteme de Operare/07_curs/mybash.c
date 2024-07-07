#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	int p2g[2], g2a[2];
	
	pipe(p2g); pipe(g2a);
	
	// PS
	if (fork() == 0) {
		// read from stdin, write to p2g[1]
		close(p2g[0]); close(g2a[0]); close(g2a[1]);
		dup2(p2g[1], 1);
		execlp("ps", "ps", "-ef", NULL);
		exit(1);
	}
	
	// GREP
	if (fork() == 0) {
		// read from p2g[0], write to g2a[1]
		close(p2g[1]); close(g2a[0]);
		dup2(p2g[0], 0);
		dup2(g2a[1], 1);
		execlp("grep", "grep", "-E", "^root", NULL);
		exit(1);
	}
	
	// AWK
	if (fork() == 0) {
		// read from g2a[0], write to stdout
		close(p2g[0]); close(p2g[1]); close(g2a[1]);
		dup2(g2a[0], 0);
		execlp("awk", "awk", "{ print $2 }", NULL);
		exit(1);
	}
	
	close(p2g[0]); close(p2g[1]); close(g2a[0]); close(g2a[1]);
	wait(0); wait(0); wait(0);
	
	return 0;
}
