-- Creați operații CRUD încapsulate în proceduri stocate pentru
-- cel puțin 3 tabele din baza de date (care să includă o
-- relație many-to-many).
-- 
-- Trebuie să folosiți:
-- 
-- - parametri de intrare/ieșire
-- - funcţii (de exemplu pentru formatarea/validarea datelor de
--   intrare)
-- - constrângeri pe tabelă/coloană pentru a asigura
--   validitatea datelor
-- 
-- De asemenea, creați cel puțin 2 view-uri peste tabelele
-- selectate pentru operațiile CRUD. Pentru tabelele folosite
-- în view, creați indecși non-clustered. Pentru a vă asigura
-- că indecșii pe care i-ați creat sunt utili, puteți verifica
-- utilizarea acestora cu Dynamic Management Views. În cazul în
-- care constatați că nu vă sunt de ajutor, este necesar să
-- reconsiderați alegerea indecșilor sau să populați tabelele
-- cu mai multe date.

-- 4 * 3 proceduri
-- 2 view-uri

-- VALIDATOR

CREATE OR ALTER FUNCTION Tema5_validate_Carte_titlu
	(@titlu VARCHAR(100))
RETURNS BIT AS BEGIN 
	IF LEN(@titlu) > 0 RETURN 1;
	RETURN 0;
END

CREATE OR ALTER FUNCTION Tema5_validate_Gen_nume
	(@nume VARCHAR(100))
RETURNS BIT AS BEGIN 
	IF LEN(@nume) > 0 RETURN 1;
	RETURN 0;
END

-- CRUD

-- CARTE
CREATE OR ALTER PROCEDURE Tema5_Carte_create
	@editura_id INT,
	@titlu VARCHAR(100),
	@data_publicare DATE
AS BEGIN 
	IF dbo.Tema5_validate_Carte_titlu(@titlu) = 0 BEGIN 
		THROW 50002, 'titlu este invalid', 1;
	END
	
	INSERT INTO Carte (editura_id, titlu, data_publicare)
	VALUES (@editura_id, @titlu, @data_publicare);
END

CREATE OR ALTER PROCEDURE Tema5_Carte_read
	@id INT
AS BEGIN 
	SELECT * FROM Carte c WHERE id = @id;
END

CREATE OR ALTER PROCEDURE Tema5_Carte_update
	@id INT,
	@titlu VARCHAR(100)
AS BEGIN 
	IF dbo.Tema5_validate_Carte_titlu(@titlu) = 0 BEGIN 
		THROW 50002, 'titlu este invalid', 2;
	END
	
	UPDATE Carte SET titlu = @titlu WHERE id = @id;
END

CREATE OR ALTER PROCEDURE Tema5_Carte_delete
	@id INT
AS BEGIN 
	DELETE FROM Carte WHERE id = @id;
END

-- GEN
CREATE OR ALTER PROCEDURE Tema5_Gen_create
	@nume VARCHAR(100)
AS BEGIN 
	IF dbo.Tema5_validate_Gen_nume(@nume) = 0 BEGIN 
		THROW 50003, 'nume este invalid', 1;
	END
	
	INSERT INTO Gen (nume)
	VALUES (@nume);
END

CREATE OR ALTER PROCEDURE Tema5_Gen_read
	@id INT
AS BEGIN 
	SELECT * FROM Gen WHERE id = @id;
END

CREATE OR ALTER PROCEDURE Tema5_Gen_update
	@id INT,
	@nume VARCHAR(100)
AS BEGIN
	IF dbo.Tema5_validate_Gen_nume(@nume) = 0 BEGIN 
		THROW 50003, 'nume este invalid', 2;
	END
	
	UPDATE Gen SET nume = @nume WHERE id = @id;
END

CREATE OR ALTER PROCEDURE Tema5_Gen_delete
	@id INT
AS BEGIN 
	DELETE FROM Gen WHERE id = @id;
END

-- Carte_Gen
CREATE OR ALTER PROCEDURE Tema5_Carte_Gen_create
	@carte_id INT,
	@gen_id INT,
	@data_adaugat DATETIME
AS BEGIN
	INSERT INTO Carte_Gen (carte_id, gen_id, data_adaugat)
	VALUES (@carte_id, @gen_id, @data_adaugat);
END

CREATE OR ALTER PROCEDURE Tema5_Carte_Gen_read
	@carte_id INT,
	@gen_id INT
AS BEGIN 
	SELECT * FROM Carte_Gen cg WHERE carte_id = @carte_id AND gen_id = @gen_id;
END

CREATE OR ALTER PROCEDURE Tema5_Carte_Gen_update
	@carte_id INT,
	@gen_id INT,
	@data_adaugat DATETIME
AS BEGIN
	UPDATE Carte_Gen SET data_adaugat = @data_adaugat
	WHERE carte_id = @carte_id AND gen_id = @gen_id;
END

CREATE OR ALTER PROCEDURE Tema5_Carte_Gen_delete
	@carte_id INT,
	@gen_id INT
AS BEGIN
	DELETE FROM Carte_Gen WHERE carte_id = @carte_id AND gen_id = @gen_id;
END

DECLARE @Carte_data_publicare DATE = DATEFROMPARTS(1900, 1, 1)
DECLARE @Carte_editura_id INT = 54
EXEC Tema5_Carte_create @Carte_editura_id, '1984', @Carte_data_publicare
DECLARE @Carte_id INT = @@IDENTITY
EXEC Tema5_Carte_read @Carte_id
EXEC Tema5_Carte_update @Carte_id, 'Fooled by Randomness'
EXEC Tema5_Carte_read @Carte_id

EXEC Tema5_Gen_create 'dystopia'
DECLARE @Gen_id INT = @@IDENTITY
EXEC Tema5_Gen_read @Gen_id
EXEC Tema5_Gen_update @Gen_id, 'statistics'
EXEC Tema5_Gen_read @Gen_id

DECLARE @Carte_Gen_data_adaugat DATETIME = GETDATE()
EXEC Tema5_Carte_Gen_create @Carte_id, @Gen_id, @Carte_Gen_data_adaugat
EXEC Tema5_Carte_Gen_read @Carte_id, @Gen_id
SET @Carte_Gen_data_adaugat = DATEADD(year, 1, GETDATE())
EXEC Tema5_Carte_Gen_update @Carte_id, @Gen_id, @Carte_Gen_data_adaugat
EXEC Tema5_Carte_Gen_read @Carte_id, @Gen_id 

EXEC Tema5_Carte_Gen_delete @Carte_id, @Gen_id
EXEC Tema5_Carte_Gen_read @Carte_id, @Gen_id 

EXEC Tema5_Carte_delete @Carte_id
EXEC Tema5_Carte_read @Carte_id

EXEC Tema5_Gen_delete @Gen_id
EXEC Tema5_Gen_read @Gen_id
;

-- VIEW-URI

-- # Perechi de (titlu carte, nume gen), unde prima litera a
-- numelui genului este intre a si j
CREATE OR ALTER VIEW Tema5_View1 AS
	SELECT c.titlu 'Titlu Carte', g.nume 'Gen Carte' 
	FROM Carte c 
	INNER JOIN Carte_Gen cg on cg.carte_id = c.id 
	INNER JOIN Gen g ON g.id = cg.gen_id 
	WHERE g.nume LIKE '[a-j]%';

-- # Genuri care incep cu o litera intre a si j
CREATE OR ALTER VIEW Tema5_View2 AS
	SELECT c.titlu 
	FROM Carte c
	WHERE c.titlu LIKE '[a-j]%';

-- INDEX

CREATE INDEX Tema5_Index1 ON Gen(nume);
DROP INDEX Tema5_Index1 ON Gen;

CREATE INDEX Tema5_Index2 ON Carte(titlu);
DROP INDEX Tema5_Index2 ON Carte;

-- NO INDEX:
-- 9 : ▏ 1.00 
-- 10:  0.00
-- 11: ▇ 2.00 
-- 12: ▇▇▇ 4.00 
-- 13: ▇ 2.00 
-- 14: ▏ 1.00 
-- 15:  0.00
-- 16:  0.00

-- INDEX:
-- 9 :  0.00
-- 10:  0.00
-- 11: ▇▇▇ 4.00 
-- 12: ▇ 2.00 
-- 13: ▏ 1.00 
-- 14: ▇ 2.00 
-- 15:  0.00
-- 16: ▏ 1.00 

DBCC DROPCLEANBUFFERS;
DBCC FREEPROCCACHE;
SELECT * FROM Tema5_View1;

-- NO INDEX:
-- 23: ▇▇▇ 3.00 
-- 24:  0.00 
-- 25:  0.00 
-- 26: ▇ 1.00 
-- 27: ▇ 1.00 
-- 28: ▇▇▇ 3.00 
-- 29:  0.00 
-- 30: ▇ 1.00 
-- 31: ▇ 1.00 

-- INDEX:
-- 23: ▇ 2.00 
-- 24: ▇▇▇ 5.00 
-- 25: ▏ 1.00 
-- 26: ▏ 1.00 
-- 27:  0.00 
-- 28: ▏ 1.00 
-- 29:  0.00 
-- 30:  0.00 
-- 31:  0.00 

DBCC DROPCLEANBUFFERS;
DBCC FREEPROCCACHE;
SELECT * FROM Tema5_View2;
