CREATE TABLE Versiune 
( id INTEGER PRIMARY KEY IDENTITY
, value INTEGER);

INSERT INTO Versiune (value) VALUES (0);

GO

-- Scrieţi un script SQL care va: 
-- 1. modifica tipul unei coloane
-- 2. adauga o costrângere de “valoare implicită” pentru un câmp
-- 3. creea/şterge o tabelă
-- 4. adăuga un câmp nou
-- 5. creea/şterge o constrângere de cheie străină

-- 1. modifica tipul unei coloane

CREATE PROCEDURE Tema3_1 AS
BEGIN
	ALTER TABLE Editura 
	ALTER COLUMN nume VARCHAR(50);
	UPDATE Versiune SET value = 1;
END;

CREATE PROCEDURE Tema3_1_Undo AS
BEGIN
	ALTER TABLE Editura 
	ALTER COLUMN nume VARCHAR(100);
	UPDATE Versiune SET value = 0;
END;

-- 2. adauga o costrângere de “valoare implicită” pentru un câmp

CREATE PROCEDURE Tema3_2 AS
BEGIN
	ALTER TABLE Abonament 
	ADD CONSTRAINT DF_data_inceput
	DEFAULT GETDATE() FOR data_inceput;
	UPDATE Versiune SET value = 2;
END;

CREATE PROCEDURE Tema3_2_Undo AS
BEGIN
	ALTER TABLE Abonament 
	DROP CONSTRAINT DF_data_inceput;
	UPDATE Versiune SET value = 1;
END;

-- 3. creea/şterge o tabelă

CREATE PROCEDURE Tema3_3 AS
BEGIN
	DROP TABLE Carte_Gen;
	UPDATE Versiune SET value = 3;
END;

CREATE PROCEDURE Tema3_3_Undo AS
BEGIN	
	CREATE TABLE Carte_Gen
	( carte_id INT FOREIGN KEY REFERENCES Carte(id)
	, gen_id INT FOREIGN KEY REFERENCES Gen(id)
	, PRIMARY KEY (carte_id, gen_id));
	UPDATE Versiune SET value = 2;
END;

-- 4. adăuga un câmp nou

CREATE PROCEDURE Tema3_4 AS
BEGIN
	ALTER TABLE Editura 
	ADD data_fondata DATE;
	UPDATE Versiune SET value = 4;
END;

CREATE PROCEDURE Tema3_4_Undo AS
BEGIN
	ALTER TABLE Editura 
	DROP COLUMN data_fondata;
	UPDATE Versiune SET value = 3;
END;

-- 5. creea/şterge o constrângere de cheie străină

CREATE PROCEDURE Tema3_5 AS
BEGIN
	ALTER TABLE Carte 
	DROP CONSTRAINT FK_Carte_Editura
	UPDATE Versiune SET value = 5;
END;

CREATE PROCEDURE Tema3_5_Undo AS
BEGIN
	ALTER TABLE Carte
	ADD CONSTRAINT FK_Carte_Editura FOREIGN KEY (editura_id) REFERENCES Editura(id);
	UPDATE Versiune SET value = 4;
END;

CREATE PROCEDURE Tema3_Do
	@index INT
AS BEGIN
	/**/ IF @index = 1 EXEC Tema3_1
	ELSE IF @index = 2 EXEC Tema3_2
	ELSE IF @index = 3 EXEC Tema3_3
	ELSE IF @index = 4 EXEC Tema3_4
	ELSE IF @index = 5 EXEC Tema3_5
END;

CREATE PROCEDURE Tema3_Undo
	@index INT
AS BEGIN
	/**/ IF @index = 1 EXEC Tema3_1_Undo 
	ELSE IF @index = 2 EXEC Tema3_2_Undo 
	ELSE IF @index = 3 EXEC Tema3_3_Undo 
	ELSE IF @index = 4 EXEC Tema3_4_Undo 
	ELSE IF @index = 5 EXEC Tema3_5_Undo 
END;

CREATE PROCEDURE Tema3_SetVersiune
	@targetVersiune INT
AS BEGIN
	IF @targetVersiune < 0 OR @targetVersiune > 5 BEGIN 
		THROW 50002, 'Versiunea data este invalida', 1;
	END
	
	DECLARE @versiune INT;
	SET @versiune = (SELECT TOP 1 value FROM Versiune);
	IF @versiune < @targetVersiune BEGIN
		WHILE @versiune < @targetVersiune BEGIN
			SET @versiune = @versiune+1;
			EXEC Tema3_Do @versiune;
		END
	END ELSE IF @versiune > @targetVersiune BEGIN
		WHILE @versiune > @targetVersiune BEGIN
			EXEC Tema3_Undo @versiune;
			SET @versiune = @versiune-1;
		END
	END
END;

-- Scrieţi un script SQL care va: 
-- 1. modifica tipul unei coloane
--    Editura.nume VARCHAR(100) => VARCHAR(50)
-- 2. adauga o costrângere de “valoare implicită” pentru un câmp
--    Abonament, DF_data_inceput, GETDATE()
-- 3. creea/şterge o tabelă
--    Carte_Gen
-- 4. adăuga un câmp nou
--    Editura.data_fondata DATE
-- 5. creea/şterge o constrângere de cheie străină
--    Carte, FK_Carte_Editura

EXEC Tema3_SetVersiune 6;
