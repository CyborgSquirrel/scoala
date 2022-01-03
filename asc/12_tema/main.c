#include <stdio.h>
#include <string.h>

void mystrcat(char *dest, char *src);

// 6. Se citesc trei siruri de caractere. Sa se determine si sa se afiseze rezultatul concatenarii lor.

int main() {
	char s[300] = "";
	char t[100];
	
	for(int i = 1; i <= 3; ++i) {
		printf("s%d = ", i);
		fgets(t, sizeof(t), stdin);
		
		int len = strlen(t);
		if(len >= 1 && t[len-1] == '\n') {
			t[len-1] = '\0';
		}
		
		mystrcat(s, t);
	}
	
	printf("%s", s);
	fgets(t, sizeof(t), stdin);

	return 0;
}