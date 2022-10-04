#include <unistd.h>
#include <stdio.h>

int main() {
	printf("%d\n", STDIN_FILENO);
	printf("%d\n", STDOUT_FILENO);
	printf("%d\n", STDERR_FILENO);
	
	return 0;
}
