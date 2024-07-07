#include <stdio.h>
#include <unistd.h>

void with_libc() {
	char s[64];
	char *p;
	int i;
	
	while (1) {
		p = fgets(s, 64, stdin);
		if (p == NULL) {
			break;
		} else {
			for (i = 0; i < 64 && s[i] != '\0'; ++i) {
				if (s[i] != '\n') {
					s[i] = '*';
				}
			}
			fputs(s, stdout);
		}
	}
	fflush(stdout);
}

void with_syscall() {
	char s[64];
	int i, k;
	
	while(1) {
		k = read(0, s, 64);
		if (k <= 0) break;
		for (i = 0; i < k; ++i) {
			if (s[i] != '\n') {
				s[i] = '*';
			}
		}
		write(1, s, k);
	}
}

int main (int argc, char **argv) {
	with_syscall();
	return 0;
}
