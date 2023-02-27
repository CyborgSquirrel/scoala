`AS` poate fi omis

- `ON DELETE/UPDATE`:
	- `NO ACTION`
	- `CASCADE`
	- `SET NULL`
	- `SET DEFAULT`

### Update

Dacă se omite clauza `WHERE`, atunci se actualizează toate liniile din tabelă.

```sql
UPDATE Sectiuni
SET descriere = 'cea mai veche sectiune'
WHERE nume = 'sectiunea 1';
```

### Delete

Dacă se omite clauza `WHERE`, atunci se șterg toate liniile din tabelă.

```sql
DELETE FROM Sectiuni
WHERE nume = 'sectiunea 1';
```

### Select

```sql
SELECT * FROM Sectiuni;
```

```sql
SELECT cod_s, nume, descriere FROM Sectiuni;
```

Distinct scoate duplicate din liniile selectate.

```sql
SELECT DISTINCT varsta_min FROM Atractii;
```

Exemple de interogări cu `WHERE`.

```sql
SELECT nume, descriere
FROM Atractii
WHERE varsta_min = 12;
```

```sql
SELECT nume, varsta_min
FROM Atractii
WHERE nume <> 'Castelul Negru';
```

```sql
SELECT * FROM Atractii
WHERE varsta_min >= 14;
```

```sql
SELECT * FROM Atractii
WHERE varsta_min <= 16;
```

Exemple cu operatorul `BETWEEN`.

Atenție la float-uri!

Poate fi folosit și cu date.

```sql
SELECT * FROM Atractii
WHERE varsta_min>11 AND varsta_min<16;
-- este la fel cu:
SELECT * FROM Atractii
WHERE varsta_min BETWEEN 12 AND 15;
```

```sql
SELECT * FROM Atractii
WHERE varsta_min NOT BETWEEN 14 AND 18;
```

Exemple cu operatorul `IN`.

```sql
SELECT * FROM Atractii
WHERE varsta_min IN (12, 14, 16)
```

```sql
SELECT * FROM Atractii
WHERE varsta_min NOT IN (12, 14, 16)
```

Exemple cu operatorul `LIKE`.

- `%` înlocuiește 0 sau mai multe caractere
- `_` înlocuiește exact 1 caracter
- între `[]` se poate pune o listă de caractere
	- dacă primul caracter este `^`, se neagă

```sql
SELECT * FROM Vizitatori WHERE nume LIKE 'A%';
```

```sql
SELECT * FROM Vizitatori WHERE nume LIKE '%a';
```

```sql
SELECT * FROM Vizitatori WHERE nume LIKE '[ABC]%';
```

```sql
SELECT * FROM Vizitatori WHERE nume LIKE '[^ABC]%';
```

```sql
SELECT * FROM Vizitatori WHERE nume LIKE '[A-F]%';
```

Exemple cu valoarea null.

```sql
SELECT * FROM Vizitatori WHERE email IS NULL;
```

```sql
SELECT * FROM Vizitatori WHERE email IS NOT NULL;
```

### Join

Join         |Left      |Right
-------------|----------|----------
`INNER JOIN` |not null  |not null
`LEFT JOIN`  |maybe null|not null
`RIGHT JOIN` |not null  |maybe null
`OUTER JOIN` |maybe null|maybe null

### Agregare

Exemple de funcții de agregare:

- `COUNT()`
- `SUM()`
- `AVG()`
- `MIN()`
- `MAX()`

```sql
SELECT A.nume, AVG(nota) medie_note
FROM Atractii A
INNER JOIN Note N ON A.cod_a=N.cod_a
GROUP BY A.cod_a, A.nume
HAVING AVG(nota) > 9;
```

### Subinterogări

```sql
SELECT nume FROM Categorii
WHERE cod_c IN (SELECT cod_c FROM Vizitatori);
```
