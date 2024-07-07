#include <stdio.h>
#include <signal.h>

void f(int sig) {
	printf("Eee pa dracu Ctrl-C.\n");
}

int main(int argc, char **argv) {
	signal(SIGINT, f);
	while(1);
	return 0;
}
