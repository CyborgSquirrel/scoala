# Funcții

## Creare

```sql
CREATE FUNCTION scalar_function_name([@param_1 datatype, @param_2 datatype, ..., @param_n datatype])
RETURNS datatype AS BEGIN
	-- cod
	RETURN value;
END;
```

## Modificare

```sql
ALTER FUNCTION scalar_function_name([@param_1 datatype, @param_2 datatype, ..., @param_n datatype])
RETURNS datatype AS BEGIN
	-- cod
	RETURN value;
END;
```

## Ștergere

```sql
DROP FUNCTION scalar_function_name;
```

## Care returnează tabele

### Inline table-valued

```sql
CREATE FUNCTION ufNumeCursuri(@nr_credite INT)
RETURNS TABLE AS
	RETURN SELECT nume FROM Cursuri
	WHERE nr_credite = @nr_credite;
```

### Multi-statement table-valued

```sql
CREATE FUNCTION ufPersoaneLocalitate(@localitate NVARCHAR(30))
RETURNS @PersoaneLocalitate TABLE (nume NVARCHAR(40), prenume NVARCHAR(40)) AS BEGIN
	INSERT INTO @PersoaneLocalitate (nume, prenume)
	SELECT nume, prenume FROM Persoane WHERE localitate = @localitate;
	IF (@@ROWCOUNT = 0)
		INSERT INTO @PersoaneLocalitate (nume, prenume) VALUES
		(N'Nicio persoana din aceasta localitate', N'');
	RETURN;
END;
```

# View-uri

Stochează o interogare.

Nu se poate folosi `ORDER BY` în cadrul unui view, decât dacă este însoțit de
`TOP`, `OFFSET`, sau `FOR XML`.

```sql
CREATE VIEW view_name AS SELECT ...;
```

```sql
ALTER VIEW view_name AS SELECT ...;
```

```sql
DROP VIEW view_name;
```

```sql
CREATE VIEW vw_Produse AS
SELECT P.nume, P.pret, C.nume as categorie
FROM Produse AS P
INNER JOIN Categorii AS C
ON P.id_cat = C.id_cat;
```

```sql
ALTER VIEW vw_Produse AS
SELECT P.nume, P.pret, P.cantitate, C.nume as categorie
FROM Produse AS P
INNER JOIN Categorii AS C
ON P.id_cat = C.id_cat;
```

# Tabele sistem

Gestionate în mod automat.

Exemple:

- `sys.objects`
- `sys.columns`
- `sys.databases`

# Trigger

Procedură stocată care se execută automat atunci când are loc un anumit eveniment în baza de date.

Evenimente DML:

- `INSERT`
- `UPDATE`
- `DELETE`

Evenimente DDL:

- `CREATE`
- `ALTER`
- `DROP`

```sql
CREATE TRIGGER [dbo].[La_introducere_produs]
ON [dbo].[Produse]
FOR INSERT AS BEGIN
	SET NOCOUNT ON;
	INSERT INTO ArhivaCumparare (nume, data, cantitate)
	SELECT nume, GETDATE(), cantitate FROM inserted;
END;
```

```sql
CREATE TRIGGER [dbo].(La_stergere_produs)
ON [dbo].[Produse]
FOR DELETE AS BEGIN
	SET NOCOUNT ON;
	INSERT INTO ArhivaVanzare (nume, data, cantitate)
	SELECT nume, GETDATE(), cantitate FROM deleted;
END;
```

```sql
CREATE TRIGGER [dbo].[La_actualizare_produs]
ON [dbo].[Produse]
FOR UPDATE AS BEGIN
	SET NOCOUNT ON;
	
	INSERT INTO ArhivaVanzare (nume, data, cantitate)
	SELECT d.nume, GETDATE(), d.cantitate-i.cantitate
	FROM deleted d
	INNER JOIN inserted i ON d.cod_p=i.cod_p
	WHERE i.cantitate<d.cantitate;
	
	INSERT INTO ArhivaCumparare (nume, data, cantitate)
	SELECT i.nume, GETDATE(), i.cantitate-d.cantitate
	FROM deleted d
	INNER JOIN inserted i ON d.cod_p=i.cod_p
	WHERE i.cantitate>d.cantitate;
END;
```

# Clauza OUTPUT

Cu clauza `OUTPUT` avem acces la înregistrări modificate, șterse, sau adăugate.

```sql
UPDATE Persoane
SET nume='Pop'
OUTPUT inserted.cod_p, deleted.nume, inserted.nume, GETDATE(), SUSER_SNAME()
INTO ModificariNumePersoane (cod_p, nume_vechi, nume_nou, data_modificarii, nume_login) WHERE cod_p=5;
```

# Cursoare

```sql
DECLARE CURSOR
```
