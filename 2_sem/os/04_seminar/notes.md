IPC = inter-process communication
- intre procese locale
	- pipe
	- FIFO
	- cozi de mesaje
	- semafoare
	- zone de memorie partajata
- intre procese aflate la distanta

### pipe
pipe = flux de date unidirectional

```c
int fd[2];
pipe(fd);
```
- `fd[0]` read
- `fd[1]` write

### FIFO
FIFO = flux de date unidirectional rezident in sistemul de fisiere

```sh
mkfifo ./mypipe
mkfifo -m 0640 /tmp/mypipe

mknod ./mypipe p
mknod -m 0640 /tmp/mypipe p
```

```c
// creeaza un FIFO
mkfifo(const char *path, mode_t mode);
// sterge un FIFO
unlink(const char *path);
```

### dup2

constante pentru descriptori in c
- `STDIN_FILENO`
- `STDOUT_FILENO`
- `STDERR_FILENO`

### popen
