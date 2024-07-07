### 1
```sh
grep '[01]{2,}100' a.txt
```

### 2
```sh
sed -E 's/([13579])([aeiou])/\2\1/g' a.txt
```

### 3
```sh
sort a.txt | uniq
```

### 4
```sh
ps -e -o euser | sort | uniq -c
```

### 5
```sh
#!/bin/sh
total_files_txt=$( find -type f -a -name '*.txt' | wc -l )
total_directories=$( find -type d | wc -l )
echo $( expr "$total_files_txt" / "$total_directories" )
```

### 6
6

### 7
A
|
B
|
C
|
D

### 8
```
ABC
```

### 9
Asteapta pana se elibereaza destul spatiu.

### 10
Se blocheaza la open, pentru ca pentru a face operatii de scriere / citire cu un FIFO, ambele capete trebuie sa fie deschise.

Aici se dechide doar capatul de scriere, iar in enunt se spune ca capatul de citire nu va fi deschis de nimeni.

### 11
Devin orfani, apoi sunt re-parentate la procesul cu PID 1, care apeleaza wait pe ele.

### 12
```c
int n = 0;
pthread_mutex_t m;

void* f(void* p) {
	pthread_mutex_lock(&m);
	
	n++;
	
	pthread_mutex_unlock(&m);
	return NULL;
}
```

### 13
CBA

### 14
avantaj: se intampla mult mai rar situatia in care doua blocuri sunt distribuite pe acelasi slot, si trebuie sa fie reincarcate frecvent in cache
dezavantaj: este mai complicat, si necesita mai mult spatiu, necesita politica de inlocuire

### 15
Categoria 00=0, paginile care nu au fost nici citite recent, nici scrise recent

### 16
```c
int n = 0;
pthread_mutex_t m[3];
void* f(void* p) {
	int id = (int)p;
		if (id == 0 || id == 2) pthread_mutex_lock(&m[id]);
	pthread_mutex_lock(&m[id]);
	n += id;
	printf("%d ", n);
	pthread_mutex_unlock(&m[(id+1) % 3]);
	return NULL;
}
int main() {
	int i;
	pthread_t t[3];
	for (i=0; i<3; ++i) {
		pthread_mutex_init(&m[i], NULL);
	}
	for (i=0; i<3; ++i) {
		pthread_create(&t[i], NULL, f, (void*)i);
	}
	for (i=0; i<3; ++i) {
		pthread_join(t[i], NULL);
	}
	for (i=0; i<3; ++i) {
		pthread_mutex_destroy(&m[i]);
	}
	return 0;
}
```

### 17
Cache-ul cu 4 seturi de 2 pagini va da rezultate mai bune, pentru ca, cu aceasta secventa de pagini, fiecare pagina va fi pe prima pozitie din setul in care este repartizata, si nu va mai fi nevoie sa fie verificate celelalte pozitii.

La cache-ul cu 2 seturi de 4 pagini, paginile 16 si 1 vor lua un pic mai mult timp sa fie accesate.

### 18
(B/A)^3

### 19
Link-ul ramane valid.

### 20
Sa se blocheze mutecsii intotdeauna in aceeasi ordine.