# ls -l

Datele apar în următoarea ordine:
- tipul de fișier (ex.: `-` fișier obișnuit, `d` director, etc.)
- permisiuni owner, group, others (ex.: `rwxr--r--`)
- owner (ex.: `andrei`)
- group (ex.: `users`)
- dimensiune
- data când a fost creat
- denumire, citată dacă este nevoie

Exemplu:

```
total 220K
drwxr-xr-x 3 andrei users 4.0K Jun 25 08:59  bin
-rw-r--r-- 1 andrei users 5.2K Jun 25 08:53  compile.py
-rw-r--r-- 1 andrei users 1.8K Jun 25 09:06  main.canvas
drwxr-xr-x 4 andrei users 4.0K Jun 24 20:19 'Sisteme de operare'
-rw-r--r-- 1 andrei users  658 Jun 24 19:41 'sortare prin inserție.md'
-rw-r--r-- 1 andrei users  875 Jun 24 19:35 'sortare prin selecție.md'
drwxr-xr-x 2 andrei users 4.0K Jun 25 08:59  target
-rw-r--r-- 1 andrei users 184K Jun 24 19:20  TematicaInformatica_2024_Ro.pdf
drwxr-xr-x 4 andrei users 4.0K Jun 24 20:48  test
```