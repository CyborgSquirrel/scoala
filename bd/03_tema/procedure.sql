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

GO

EXEC Tema3_1; 
EXEC Tema3_2;
EXEC Tema3_3;
EXEC Tema3_4;
EXEC Tema3_5;

EXEC Tema3_2_Undo;
