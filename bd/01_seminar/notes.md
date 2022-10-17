## Enunț

Să se creeze baza de date a unei aplicații care gestionează notele date de către utilizatori unor filme.

Entitățile de interes pentru domeniul problemei sunt:

* Utilizatori
* Companii 
* Filme

Fiecare companie are un nume și o țară. O companie poate produce mai multe filme, dar fiecare film este produs de către o singură companie. Fiecare film are un titlu, o durată, o limbă și este produs de către o singură companie. Utilizatorii pot da note mai multor filme, iar un film poate primi note de la mai mulți utilizatori. Fiecare utilizator are un nume de utilizator, o parolă și o adresă de email. Numele de utilizator și adresa de email sunt unice. Pentru numele de utilizator nu se poate specifica valoarea NULL. Fiecare utilizator poate da fiecărui film o singură notă. Valoarea notei este cuprinsă între 1 și 10.

## Rezolvare

### Creeăm tabelele

- `IDENTITY(start, increment)` alege automat valoarea pentru coloană
- `NOT NULL` coloana nu poate avea valoarea null
- `UNIQUE` valoarea coloanei nu se poate repeta

```sql
CREATE TABLE Utilizator
( id INT PRIMARY KEY IDENTITY
, nume VARCHAR(100) NOT NULL UNIQUE
, parola VARCHAR(100)
, email VARCHAR(100));
```

- `NVARCHAR` stochează text unicode

```sql
CREATE TABLE Companie
( id INT PRIMARY KEY IDENTITY(1, 1)
, nume NVARCHAR(100)
, tara NVARCHAR(100));
```

- `FOREIGN KEY` nu poate să refere un tabel dintr-o altă bază de date

```sql
CREATE TABLE Film
( id INT PRIMARY KEY IDENTITY,
, titlu NVARCHAR(200)
, durata TIME
, limba NVARCHAR(100)
, companie_id FOREIGN KEY REFERENCES Companie(id)
    ON UPDATE CASCADE
    ON DELETE CASCADE);
```

```sql
CREATE TABLE Nota
( utilizator_id INT
, film_id INT
, nota INT
, CONSTRAINT fk_UtilizatorNota FOREIGN KEY (utilizator_id) REFERENCES Utilizator(id)
, CONSTRAINT fk_FilmNota FOREIGN KEY (film_id) REFERENCES Film(id)
, CONSTRAINT pk_Nota PRIMARY KEY (utilizator_id, film_id);
```

### Constraint-uri

Am uitat să facem email-ul unic! Folosim `ALTER TABLE` ca să reparăm.

```sql
ALTER TABLE Utilizator
ADD CONSTRAINT uq_email UNIQUE (email);
```

Facem ca notele să fie între 1 și 10.

```sql
ALTER TABLE Nota
ADD CONSTRAINT ck_nota CHECK (nota >= 1 AND nota <= 10);
```

### Adăugam o coloană nouă

```sql
ALTER TABLE Nota
ADD data_si_ora_adaugarii DATETIME;
```

### Adăugăm valoare implicită

```sql
ALTER TABLE Nota
ADD CONSTRAINT df_data_si_ora_adaugarii DEFAULT GETDATE() FOR data_si_ora_adaugarii;
```

### Modificăm tipul unei coloane

Când modificăm tipul unei coloane, tipul nou trebuie să fie compatibil cu cel vechi.

```sql
ALTER TABLE Film
ALTER COLUMN titlu NVARCHAR(220);
```

### Ștergem o constrângere

```sql
ALTER TABLE Nota
DROP CONSTRAINT df_data_si_ora_adaugarii;
```

### Ștergem o coloană

```sql
ALTER TABLE Nota
DROP COLUMN data_si_ora_adaugarii;
```

### Modificăm numele unei coloane

```sql
ALTER DATABASE ProblemaFilme
MODIFY Name=NoteFilme;
```

### Ștergem o bază de date

```sql
USE master;
DROP DATABASE NoteFilme;
```
