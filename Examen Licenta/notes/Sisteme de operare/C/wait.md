```c
wait(int *wstatus)
```

Așteaptă ca un proces fiu să își încheie execuția.

Dacă nu are nici un fiu, atunci returnează -1.
Altfel, returnează PID-ul fiului care și-a încheiat execuția.

```c
// run {"compiler": "c"}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	if (fork() == 0) {
		printf("child getpid(): %d\n", getpid());
		exit(0);
	}

	for (int i = 0; i < 2; ++i) {
		int val = wait(NULL);
		printf("parent wait(): %d\n", val);
	}

	return 0;
}
```