### Barrier
```c
pthread_barrier_init(...)
pthread_barrier_wait(...)
```

### Semaphore
- valoare initiala
- doua operatii:
	- wait (-1), daca valoarea e 0, wait asteapta
	- post (+1)

v == 1 =>
	- semafor binar
	- wait ~ lock
	- post ~ unlock
v > 1 =>
	- wait ~ rezerva
	- post ~ elibereaza

## Metafore

### Toaleta
```c
semwait(s);
for (i=0; i<3; ++i) {
	if (trylock(m[i]) == 0) {
		...
		unlock(m[i]);
		break;
	}
}
semwait(s);
```

### Lift
```c
sem(400 kg);
lock(m);
for (i=0; i<weight; ++i) {
	semwait(s);
}
unlock(m);
```

### Trambulina
```c
lock(m);
for (i=0; i<weight; ++i) {
	semwait(kg);
}
semwait(persoane);
unlock(m);
```

### Sah
```c
// main
lock(m2);
init(T1);
init(T2);

// T1
while (1) {
	lock(m1);
	play
	unlock(m2);
}

// T2
while (1) {
	lock(m2);
	play
	unlock(m1);
}
```

### Pipe (producator/consumator)
- mutex
- full(0)
- empty(L)

```c
// producator
while (1) {
	wait(empty);
	lock(m);
	produ
	unlock(m);
	post(full);
}

// consumator
while (1) {
	wait(full);
	lock(m);
	consuma
	unlock(m);
	post(empty);
}
```

## Deadlock (impas)
```c
i = rand()%L;
j = rand()%L;

if (i > j) swap(i, j);

lock(m[i]);
lock(m[j]);

x = a[i];
y = a[j];
a[i] = x+y;
a[j] = x*y;

unlock(m[i]);
unlock(m[j]);
```

- blocati intotdeauna in aceeasi ordine
