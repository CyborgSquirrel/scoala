#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
	// for (int i = 0; i < argc; ++i) {
		// printf("%s\n", argv[i]);
	// }
	if (argc >= 2) {
		printf("Hello %s", argv[1]);
	} else {
		printf("Ce faci domne???");
		exit(1);
	}
	return 0;
}
