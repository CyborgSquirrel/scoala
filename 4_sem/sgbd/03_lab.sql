CREATE OR ALTER FUNCTION Lab3_validate_carte_titlu(@Carte_titlu VARCHAR(100))
RETURNS BIT AS BEGIN
	IF LEN(@Carte_titlu) <= 0 RETURN 0;
	RETURN 1;
END;

CREATE OR ALTER FUNCTION Lab3_validate_autor_nume(@Autor_nume VARCHAR(100))
RETURNS BIT AS BEGIN
	IF LEN(@Autor_nume) <= 0 RETURN 0;
	RETURN 1;
END;

CREATE OR ALTER FUNCTION Lab3_validate_autor_prenume(@Autor_prenume VARCHAR(100))
RETURNS BIT AS BEGIN
	IF LEN(@Autor_prenume) <= 0 RETURN 0;
	RETURN 1;
END;

SELECT * FROM Carte;
SELECT * FROM Autor_Carte;
SELECT * FROM Autor;

-- 1. Creaţi o procedură stocată ce inserează date
--    pentru entităţi ce se află într-o relaţie m-n.
--    Dacă o operaţie de inserare eşuează, trebuie
--    făcut roll-back pe întreaga procedură stocată.
--    (5 puncte)

CREATE OR ALTER PROCEDURE Lab3_1
	@Carte_editura_id INT,
	@Carte_titlu VARCHAR(100),
	@Carte_data_publicare DATE,
	@Autor_nume VARCHAR(100),
	@Autor_prenume VARCHAR(100)
AS BEGIN
	IF dbo.Lab3_validate_carte_titlu(@Carte_titlu) = 0 BEGIN		
		RAISERROR(50001, 1, 1, 'Carte titlu nevalid');
	END
	IF dbo.Lab3_validate_autor_nume(@Autor_nume) = 0 BEGIN		
		RAISERROR(50002, 1, 1, 'Autor nume nevalid');
	END
	IF dbo.Lab3_validate_autor_prenume(@Autor_prenume) = 0 BEGIN		
		RAISERROR(50003, 1, 1, 'Autor prenume nevalid');
	END

	BEGIN TRY
		BEGIN TRANSACTION;
			-- Carte
			DECLARE @Carte_inserted TABLE (
			    id INT
			);
			
			INSERT INTO Carte (editura_id, titlu, data_publicare)
			OUTPUT INSERTED.id INTO @Carte_inserted
			VALUES (@Carte_editura_id, @Carte_titlu, @Carte_data_publicare);
		
			DECLARE @Carte_id INT;
			SELECT TOP 1 @Carte_id = id FROM @Carte_inserted;
		
			-- Autor
			DECLARE @Autor_inserted TABLE (
				id INT
			);
			
			INSERT INTO Autor (nume, prenume)
			OUTPUT INSERTED.id INTO @Autor_inserted
			VALUES (@Autor_nume, @Autor_prenume);
		
			DECLARE @Autor_id INT;
			SELECT TOP 1 @Autor_id = id FROM @Autor_inserted;
		
			-- Autor_Carte
			INSERT INTO Autor_Carte (autor_id, carte_id)
			VALUES (@Autor_id, @Carte_id);
		COMMIT;
	END TRY
	BEGIN CATCH
		ROLLBACK;
		PRINT('eroare');
	END CATCH
END

DECLARE @date DATE = DATEFROMPARTS(1901, 1, 1)
EXEC Lab3_1 50, 'War and Peace', @date, 'Jane', 'Austen';

DECLARE @date DATE = DATEFROMPARTS(1901, 1, 1)
EXEC Lab3_1 54, 'War and Peace', @date, 'Jane', 'Austen';

DECLARE @date DATE = DATEFROMPARTS(1901, 1, 1)
EXEC Lab3_1 54, '', @date, 'Jane', 'Austen';

-- 2. Creaţi o procedură stocată ce inserează date
--    pentru entităţi ce se află într-o relaţie m-n.
--    Dacă o operaţie de inserare eşuează va trebui să
--    se păstreze cât mai mult posibil din ceea ce s-a
--    modificat până în acel moment. De exemplu, dacă
--    se încearcă inserarea unei cărţi şi a autorilor
--    acesteia, iar autorii au fost inseraţi cu succes
--    însă apare o problemă la inserarea cărţii,
--    atunci să se facă roll-back la inserarea de
--    carte însă autorii acesteia să rămână în baza de
--    date. (4 puncte)

CREATE OR ALTER PROCEDURE Lab3_2
	@Carte_editura_id INT,
	@Carte_titlu VARCHAR(100),
	@Carte_data_publicare DATE,
	@Autor_nume VARCHAR(100),
	@Autor_prenume VARCHAR(100)
AS BEGIN
	IF dbo.Lab3_validate_carte_titlu(@Carte_titlu) = 0 BEGIN		
		RAISERROR(50001, 1, 1, 'Carte titlu nevalid');
	END
	IF dbo.Lab3_validate_autor_nume(@Autor_nume) = 0 BEGIN		
		RAISERROR(50002, 1, 1, 'Autor nume nevalid');
	END
	IF dbo.Lab3_validate_autor_prenume(@Autor_prenume) = 0 BEGIN		
		RAISERROR(50003, 1, 1, 'Autor prenume nevalid');
	END
	
	BEGIN TRY
		BEGIN TRANSACTION;
			-- Autor
			DECLARE @Autor_inserted TABLE (
				id INT
			);
			
			INSERT INTO Autor (nume, prenume)
			OUTPUT INSERTED.id INTO @Autor_inserted
			VALUES (@Autor_nume, @Autor_prenume);
		
			DECLARE @Autor_id INT;
			SELECT TOP 1 @Autor_id = id FROM @Autor_inserted;
		COMMIT;
	END TRY
	BEGIN CATCH
		ROLLBACK;
		PRINT('eroare');
		RETURN;
	END CATCH
	
	BEGIN TRY
		BEGIN TRANSACTION;
			-- Carte
			DECLARE @Carte_inserted TABLE (
			    id INT
			);
			
			INSERT INTO Carte (editura_id, titlu, data_publicare)
			OUTPUT INSERTED.id INTO @Carte_inserted
			VALUES (@Carte_editura_id, @Carte_titlu, @Carte_data_publicare);
		
			DECLARE @Carte_id INT;
			SELECT TOP 1 @Carte_id = id FROM @Carte_inserted;
		COMMIT;
	END TRY
	BEGIN CATCH
		ROLLBACK;
		PRINT('eroare');
		RETURN;
	END CATCH
	
	BEGIN TRY
		BEGIN TRANSACTION;
			-- Autor_Carte
			INSERT INTO Autor_Carte (autor_id, carte_id)
			VALUES (@Autor_id, @Carte_id);
		COMMIT;
	END TRY
	BEGIN CATCH
		ROLLBACK;
		PRINT('eroare');
		RETURN;
	END CATCH
END

DECLARE @date DATE = DATEFROMPARTS(1901, 1, 1)
EXEC Lab3_2 50, 'ABC', @date, 'owo', 'owo';

DECLARE @date DATE = DATEFROMPARTS(1901, 1, 1)
EXEC Lab3_2 54, 'XYZ', @date, 'uwu', 'uwu';
