#include "./8.h"

int main(int argc, char **argv) {
	if (mkfifo(a2b, 0666) < 0) { perror("mkfifo"); exit(1); }
	if (mkfifo(b2a, 0666) < 0) { perror("mkfifo"); exit(1); }
	
	int fildes_write = open(a2b, O_WRONLY);
	if (fildes_write < 0) { perror("open"); exit(1); }
	int fildes_read = open(b2a, O_RDONLY);
	if (fildes_read < 0) { perror("open"); exit(1); }
	
	char ans[2048];
	char buf[128];
	
	for (int i = 0; i < argc; ++i) {
		int size = strlen(argv[i]);
		write(fildes_write, argv[i], size);
	}
}
