### Mutex
- lock()
- unlock()

```
lock(mutex)
sectiune critica = zona de cod care foloseste resurse critice
unlock(mutex)
```

### RWLock
- rdlock()
- wrlock()
- unlock()

Sau mai multi readers, sau un singur writer.

```c
lock(&mutex)
// modifica v
if (v ...) {
	signal(c)
}
unlock(&mutex)
```

```c
lock(mutex)
while (!v ...) {
	wait(&c, &mutex)
	// echivalent cu
	// unlock(&mutex)
	// asteapta semnal
	// lock(&mutex)
}
// ...
unlock(&mutex)
```
