Process:
- context
- pure:
	- code
	- constants
- impure (duplicate la fork):
	- variables
	- heap
	- stack

Thread-urile sunt in acelasi spatiu de memorie.

### mutext
mutex = mutual exclusion

```c
// no bueno
pthread_mutex_trylock()
```

### rwlock

### Variabile conditionale
- permite unor thread-uri sa astepte pana cand li se spune

```c
pthread_cont_t c;
pthread_mutex_t m;

// cel care asteapta conditia
pthread_mutex_lock(&m);
pthread_cond_wait(&c, &m);
pthread_mutex_unlock(&m);

// cel care spune ca s-a indeplinit conditia
pthread_mutex_lock(&m);
pthread_cont_signal(&c);    // trezeste unul
pthread_cont_broadcast(&c); // trezeste pe toti
pthread_mutex_unlock(&m);
```
