### 1
```regex
([aeiouAEIOU].*){3,}
```

### 2
`A`

### 3
```c
int p[2];
pipe(p);
int pid = fork();
if (pid == 0) {
	dup2(p[1], 1);
	printf("asdf\n");
} else {
	char s[6];
	fread(s, 1, 6, p[0]);
	printf(s);
}
```

### 4
Nu se poate sti exact ce se va tipari, pentru ca nu se poate cunoaste la ce moment va intra in actiune fiecare dintre thread-uri.

Cel mai probabil, se vor tipari 10 numere, fiecare intre 0 si 9.

### 5
Exista risc de deadlock. Daca, de exemplu, avem doua thread-uri, primul cu id=0, iar al doilea cu id=1, atunci s-ar putea sa se intample ca primul thread sa blocheze m[0], apoi sa fie intrerupt, si apoi cel de-al doilea thread sa blocheze m[1] si sa ramana asteptand deblocarea lui m[0], si cand ruleaza din nou primul thread, acesta ramane asteptand deblocarea lui m[1].

### 6
B/2/4
A/5/7
D/3/8
C/4/13

### 7
Este un tuplu format din segment, pagina, si deplasamentul in cadrul paginii. Tabelele de segmente, si de pagini, sunt implicate in calcularea adresei fizice.

### 8
Principiul vecinatatii in privinta incarcarii paginilor unui proces este ca, atunci cand se cere spre a fi incarcata o pagina, sunt incarcate si paginile apropiate de aceasta din memorie (pentru ca se considera ca exista o sansa ridicata sa fie nevoie de aceste pagini).

### 9
Cache-ul cu 2 seturi de 4 pagini ar functiona mai bine, pentru ca toate paginile ar incapea in cache, si nu ar fi nevoie sa fie inlocuita nici o pagina (la cel cu 4 seturi de 2 pagini, in schimb, ar fi nevoie sa se inlocuiasca o pagina).

### 10
Pentru ca un link hard este implementat ca o adresa spre un i-node. O partitie nu poate accesa i-node-urile unei alte partitii, si de aceea nu se poate creea un hard link de la o partitie la alta.
