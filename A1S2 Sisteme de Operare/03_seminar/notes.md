```c
pid_t pid = fork();
if (pid == -1) { // eroare
	perror("fork() error");
	exit(EXIT_FAILURE);
}
if (pid == 0) { // copil
	
} else { // parinte
	
}
```

Ce returneaza fork?
- eroare: -1
- parinte: PID-ul procesului copil
- copil: 0

Doua tipuri de procese:
- orfan
- zombie (nu poti sa-l omori)

Ca sa nu ai procese zombie:
```c
signal(SIGCHLD, SIG_IGN);
```
