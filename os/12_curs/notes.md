# Procese

## Fazele unui proces
- prezentare
- HOLD
- READY
- RUN
- FINISH
- eliberare resurse

## Deadlock
```
// p1     // p2
lock(X) | lock(Y)
lock(Y) | lock(X)
```

- iesire din deadlock
- detectare de deadlock
- prevenire

### Iesire
- alege un proces (thread) victima si opreste-l
- daca am avea posibilitatea de a salva un savepoint, am putea cere unui proces sa revina la starea anterioara (fara sa-l oprim)
	- risc de livelock

### Prevenire
- ce il face posibil
	1. Mutual exclusion
	2. Hold (lock) and wait
	3. Non-preemption
	4. Asteptarea circulara (dezactivata prin blocarea resurselor in aceeasi ordine)

### Cum eviti deadlock???
Prin blocarea resurselor in aceeasi ordine.

## Planificarea proceselor (scheduling)
- FCFS (First Come First Served)
- SJF (Shortest Job First)
	- clientul trebuie sa dea o estimare a duratei programului
	- risc de starvation pentru taskurile mari
- prioritati
- deadline scheduling
	- mai multe task-uri, fiecare cu o durata si un termen
- round robin
	- se aloca fiecarui proces cate o cuanta de timp

# Gestiunea memoriei
- alocare
- inlocuire
- plasare

## Alocare
- alocare reala
	- sisteme single-tasking   (1)
	- sisteme multi-tasking
		- partitii fixe
			- absolute         (2)
			- relocabile       (3)
		- partitii variabile   (4)
- alocare virtuala
	- paginata                 (5)
	- segmentata               (6)
	- paginat-segementata      (7)
