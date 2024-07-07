```c
int execl(const char *pathname, const char *arg, ...
			   /*, (char *) NULL */);
int execlp(const char *file, const char *arg, ...
			   /*, (char *) NULL */);
int execle(const char *pathname, const char *arg, ...
			   /*, (char *) NULL, char *const envp[] */);
int execv(const char *pathname, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execvpe(const char *file, char *const argv[], char *const envp[]);
```

Înlocuiește procesul curent cu unul nou, executat dintr-un fișier (care poate opțional fi găsit prin `$PATH`).

| Sufix | Descriere                                                                                                                           |
| ----- | ----------------------------------------------------------------------------------------------------------------------------------- |
| p     | Executabilul se va căuta în `$PATH`. Dacă lipsește acest sufix, se va executa fix fișierul care se găsește la path-ul dat.          |
| l     | Argumentele executabilului se dau sub formă de vararg-uri.                                                                          |
| v     | Argumentele executabilului se dau sub formă de listă.                                                                               |
| e     | Ultimul argument este o listă cu variabilele de mediu cu care se va crea procesul (de exemplu: `{ "HOME=/root", "PATH=/bin", 0 }`). |

```c
// run {"compiler": "c"}

#include <unistd.h>
#include <stdio.h>

int main() {
	printf("Process is talkin'!\n");
	int code = execlp("sh", "sh", "-c", "echo 'Shell is talkin!'", NULL);
	printf("Oh no %d\n", code);
	perror("execlp");
	printf("Process is back!\n");
	return 0;
}
```