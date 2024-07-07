#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char *path1 = "./7a-fifo1";
char *path2 = "./7a-fifo2";

int main(int argc, char **argv) {
	if (mkfifo(path1, 0666) < 0) { perror("mkfifo"); exit(1); }
	if (mkfifo(path2, 0666) < 0) { perror("mkfifo"); exit(1); }
	
	int fildes_write = open(path1, O_WRONLY);
	if (fildes_write == -1) { perror("open"); exit(1); }
	
	int fildes_read = open(path2, O_RDONLY);
	if (fildes_read == -1) { perror("open"); exit(1); }
	
	srandom(getpid());
	int a;
	a = random()%10 + 1;
	write(fildes_write, &a, sizeof(int));
	while (read(fildes_read, &a, sizeof(int)) > 0) {
		printf("A %d\n", a);
		if (a == 10) {
			break;
		}
		a = random()%10 + 1;
		write(fildes_write, &a, sizeof(int));
	}
	
	close(fildes_write);
	close(fildes_read);
	unlink(path1);
	unlink(path2);
	
	return 0;
}
