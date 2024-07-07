stdin  - 0
stdout - 1
stderr - 2

```sh
# face symbolic link
ln -s
```

# mybash
```sh
# cum face bash???
ps -ef | grep -E '^root' | awk '{ print $2 }'
```

```c
// copiaza descriptorul oldfd
int dup(int oldfd)

// copiaza descriptorul oldfd in newfd (si inchide newfd daca era deschis)
int dup2(int oldfd, int newfd)
```

La `fork` si `exec` se pastreaza descriptorii (cred).

# ipc
```sh
ipcmk # creeaza un ipc
ipcs  # afiseaza toate ipc-urile
ipcrm # sterge un ipc
```

```c
shmget() // creeaza sau deschide shm
shmat()  // se ataseaza de o zona shm
shmdt()  // se detaseaza de o zona shm
shmctl() // controleaza o zona shm
```

# threads
```c
pthread_create() // creeaza un thread
pthread_join()   // asteapta dupa un thread
```

Ca sa compilezi un program cu thread-uri, iti trebuie biblioteca pthread.
```sh
gcc -lpthread ...
# sau
gcc -pthread ...
```
