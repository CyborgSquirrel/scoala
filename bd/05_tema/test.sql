-- TABELE

INSERT INTO Tables (Name) VALUES
-- 1. o tabelă având un câmp ca şi cheie
--    primară şi nici o cheie străină
('Gen'),
-- 2. o tabelă având un câmp ca şi cheie
--    primară şi cel puţin o cheie străină
('Carte'),
-- 3. o tabelă având două câmpuri ca şi
--    cheie primară
('Carte_Gen');

-- VIEW-URI

INSERT INTO Views (Name)
VALUES ('View1'), ('View2'), ('View3');

-- 1. un view ce conţine o comandă SELECT
--    pe o tabelă

-- # Titlurile tuturor cartilor
CREATE OR ALTER VIEW Tema4_View1 AS
	SELECT c.titlu 'Titlu Carte' FROM Carte c;

-- 2. un view ce conţine o comandă SELECT
--    aplicată pe cel puţin două tabele

-- # Toate perechile de carte si gen al cartii,
-- # unde numele genului incepe cu litera a
CREATE OR ALTER VIEW Tema4_View2 AS
	SELECT c.titlu 'Titlu Carte', g.nume 'Gen Carte (care incepe cu litera a)' 
	FROM Carte c 
	INNER JOIN Carte_Gen cg on cg.carte_id = c.id 
	INNER JOIN Gen g ON g.id = cg.gen_id 
	WHERE g.nume LIKE 'a%';

-- 3. un view ce conţine o comandă SELECT
--    aplicată pe cel puţin două tabele şi
--    având o clauză GROUP BY

-- # Titlu carte cu lista de genuri
CREATE OR ALTER VIEW Tema4_View3 AS
	SELECT c.titlu 'Titlu Carte', STRING_AGG(g.nume, ' ') 'Genuri Carte'
	FROM Carte_Gen cg
	INNER JOIN Carte c ON c.id = cg.carte_id
	INNER JOIN Gen g ON g.id = cg.gen_id
	GROUP BY c.id, c.titlu;

-- CREATE TEST

INSERT INTO Tests (Name) VALUES ('Carte_Gen');

DECLARE @TestID_Carte_Gen INT = (SELECT TestID FROM Tests t WHERE Name = 'Carte_Gen')

DECLARE @TableID_Gen INT = (SELECT TableID FROM Tables t WHERE Name = 'Gen')
DECLARE @TableID_Carte INT = (SELECT TableID FROM Tables t WHERE Name = 'Carte')
DECLARE @TableID_Carte_Gen INT = (SELECT TableID FROM Tables t WHERE Name = 'Carte_Gen')

DECLARE @ViewID_View1 INT = (SELECT ViewID FROM Views v WHERE Name = 'View1');
DECLARE @ViewID_View2 INT = (SELECT ViewID FROM Views v WHERE Name = 'View2');
DECLARE @ViewID_View3 INT = (SELECT ViewID FROM Views v WHERE Name = 'View3');

INSERT INTO TestTables (TestID, [Position], TableID, NoOfRows) VALUES
  (@TestID_Carte_Gen, 0, @TableID_Carte_Gen, 750)
, (@TestID_Carte_Gen, 1, @TableID_Gen, 1000)
, (@TestID_Carte_Gen, 2, @TableID_Carte, 500)

INSERT INTO TestViews (TestID, ViewID) VALUES
  (@TestID_Carte_Gen, @ViewID_View1)
, (@TestID_Carte_Gen, @ViewID_View2)
, (@TestID_Carte_Gen, @ViewID_View3)

;

-- Fiecare rulare de test presupune
-- următoarele:
-- 
-- 1. ştergerea datelor din tabelele
--    asociate testului (în ordinea dată de
--    câmpul Position)
-- 2. inserarea înregistrărilor în tabele
--    în ordinea inversă dată de Position
--    (numărul de înregistrări inserate
--    este dat de câmpul NoOfRows)
-- 3. evaluarea timpului de execuţie a
--    view-urilor

-- RANDOM STUFF

CREATE OR ALTER PROCEDURE Tema4_RandVarchar
	@Length INT,
	@GenVarchar VARCHAR(100) OUTPUT
AS BEGIN 
	DECLARE @Chars VARCHAR(58) = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';

	SET @GenVarchar = '';
	DECLARE @I INT = 0;
	WHILE @I < @Length BEGIN
		DECLARE @Index INT;
		SET @Index = FLOOR(RAND() * LEN(@Chars)) + 1;
		SET @GenVarchar = CONCAT(
			@GenVarchar,
			SUBSTRING(@Chars, @Index, 1)
		);
		SET @I = @I+1;
	END
END;

CREATE OR ALTER PROCEDURE Tema4_RandDate
	@GenDate DATE OUTPUT
AS BEGIN 
	DECLARE @DateStart DATE = DATEFROMPARTS(1900, 1, 1);
	DECLARE @OffsetDays INT = FLOOR(RAND() * 365*120)
	SET @GenDate = DATEADD(day, @OffsetDays, @DateStart);
END;

-- TEST PROCEDURE

CREATE OR ALTER PROCEDURE Tema4_Test
	@TestID INT,
	@Description NVARCHAR(2000)
AS BEGIN
	DECLARE @I INT = 0;

	DECLARE @TableID INT;
	DECLARE @ViewID INT;
	DECLARE @NoOfRows INT;
	DECLARE @Name NVARCHAR(50);

	INSERT INTO TestRuns (Description, StartAt, EndAt)
	VALUES (@Description, GETDATE(), NULL);
	DECLARE @TestRuns_TestRunID INT = SCOPE_IDENTITY();

	-- 1. ştergerea datelor din tabelele
	--    asociate testului (în ordinea dată de
	--    câmpul Position)

	DECLARE procedure_cursor CURSOR FAST_FORWARD FOR
	SELECT t.Name FROM TestTables tt 
	INNER JOIN Tables t ON t.TableID = tt.TableID 
	WHERE tt.TestID = @TestID
	ORDER BY tt.[Position];

	OPEN procedure_cursor;
		FETCH NEXT FROM procedure_cursor INTO @Name
		WHILE @@FETCH_STATUS = 0 BEGIN
			/**/ IF @Name = 'Carte_Gen' DELETE FROM Carte_Gen;
			ELSE IF @Name = 'Gen' DELETE FROM Gen;
			ELSE IF @Name = 'Carte' DELETE FROM Carte;
			
			FETCH NEXT FROM procedure_cursor INTO @Name
		END
	CLOSE procedure_cursor; DEALLOCATE procedure_cursor;

	-- 2. inserarea înregistrărilor în tabele
	--    în ordinea inversă dată de Position
	--    (numărul de înregistrări inserate
	--    este dat de câmpul NoOfRows)

	-- + evaluarea timpului de executie

	DECLARE procedure_cursor CURSOR FAST_FORWARD FOR
	SELECT t.TableID, tt.NoOfRows, t.Name FROM TestTables tt 
	INNER JOIN Tables t ON t.TableID = tt.TableID 
	WHERE tt.TestID = @TestID
	ORDER BY tt.[Position] DESC;

	OPEN procedure_cursor;
		FETCH NEXT FROM procedure_cursor INTO @TableID, @NoOfRows, @Name;
		WHILE @@FETCH_STATUS = 0 BEGIN
			DECLARE @TestRunTables_StartAt DATETIME = GETDATE();
			
			/******/ IF @Name = 'Carte_Gen' BEGIN
				DECLARE @Carte_Linii INT = (SELECT COUNT(*) FROM Carte c);
				DECLARE @Gen_Linii INT = (SELECT COUNT(*) FROM Gen g);
				SET @I = 0; WHILE @I < @NoOfRows BEGIN
					-- carte_id
					DECLARE @Carte_Linie INT = FLOOR(RAND() * @Carte_Linii) + 1;
					DECLARE @Carte_Gen_CarteId INT = (
						SELECT c.id FROM
						(SELECT *, ROW_NUMBER() OVER (ORDER BY id ASC) as linie FROM Carte c) c
						WHERE c.linie = @Carte_Linie
					);
					
					-- gen_id
					DECLARE @Gen_Linie INT = FLOOR(RAND() * @Gen_Linii) + 1;
					DECLARE @Carte_Gen_GenId INT = (
						SELECT g.id FROM
						(SELECT *, ROW_NUMBER() OVER (ORDER BY id ASC) as linie FROM Gen g) g
						WHERE g.linie = @Gen_Linie
					);
					
					-- INSERT 
					DECLARE @Success INT = 1;
					BEGIN TRY
						INSERT INTO Carte_Gen (carte_id, gen_id)
						VALUES (@Carte_Gen_CarteId, @Carte_Gen_GenId);
					END TRY
					BEGIN CATCH
						SET @Success = 0;
					END CATCH;
				
					IF @Success = 1 SET @I = @I + 1;
				END
			END ELSE IF @Name = 'Gen' BEGIN
				SET @I = 0; WHILE @I < @NoOfRows BEGIN
					-- nume
					DECLARE @Gen_Nume VARCHAR(100);
					EXEC Tema4_RandVarchar 20, @GenVarchar=@Gen_Nume OUTPUT;
					
					-- INSERT
					INSERT INTO Gen (nume)
					VALUES (@Gen_Nume);
					
					SET @I = @I + 1;
				END
			END ELSE IF @Name = 'Carte' BEGIN
				DECLARE @Editura_Linii INT = (SELECT COUNT(*) FROM Editura e);
				
				SET @I = 0; WHILE @I < @NoOfRows BEGIN
					-- editura_id
					DECLARE @Editura_Linie INT = FLOOR(RAND() * @Editura_Linii) + 1;
					DECLARE @Carte_EdituraId INT = (
						SELECT e.id FROM
						(SELECT *, ROW_NUMBER() OVER (ORDER BY id ASC) as linie FROM Editura e) e
						WHERE e.linie = @Editura_Linie
					);
					
					-- titlu
					DECLARE @Carte_Titlu VARCHAR(100);
					EXEC Tema4_RandVarchar 100, @GenVarchar=@Carte_Titlu OUTPUT;

					-- data_publicare
					DECLARE @Carte_DataPublicare DATE;
					EXEC Tema4_RandDate @GenDate=@Carte_DataPublicare OUTPUT; 
				
					-- INSERT
					INSERT INTO Carte (editura_id, titlu, data_publicare)
					VALUES (@Carte_EdituraId, @Carte_Titlu, @Carte_DataPublicare);
					
					SET @I = @I + 1;
				END
			END
			
			DECLARE @TestRunTables_EndAt DATETIME = GETDATE();
			INSERT INTO TestRunTables (TestRunID, TableID, StartAt, EndAt)
			VALUES (@TestRuns_TestRunID, @TableID, @TestRunTables_StartAt, @TestRunTables_EndAt);
			
			FETCH NEXT FROM procedure_cursor INTO @TableID, @NoOfRows, @Name;
		END
	CLOSE procedure_cursor; DEALLOCATE procedure_cursor;

	-- 3. evaluarea timpului de execuţie a
	--    view-urilor

	DECLARE procedure_cursor CURSOR FAST_FORWARD FOR
	SELECT v.ViewID, v.Name FROM TestViews tv
	INNER JOIN Views v ON v.ViewID = tv.ViewID 
	WHERE tv.TestID = @TestID;

	OPEN procedure_cursor;
		FETCH NEXT FROM procedure_cursor INTO @ViewID, @Name;
		WHILE @@FETCH_STATUS = 0 BEGIN
			DECLARE @TestRunViews_StartAt DATETIME = GETDATE();
			
			/**/ IF @Name = 'View1' SELECT * FROM Tema4_View1;
			ELSE IF @Name = 'View2' SELECT * FROM Tema4_View2;
			ELSE IF @Name = 'View3' SELECT * FROM Tema4_View3;
		
			DECLARE @TestRunViews_EndAt DATETIME = GETDATE();
			INSERT INTO TestRunViews (TestRunID, ViewID, StartAt, EndAt)
			VALUES (@TestRuns_TestRunID, @ViewID, @TestRunViews_StartAt, @TestRunViews_EndAt);
			
			FETCH NEXT FROM procedure_cursor INTO @ViewID, @Name;
		END
	CLOSE procedure_cursor; DEALLOCATE procedure_cursor;

	UPDATE TestRuns 
	SET EndAt = GETDATE()
	WHERE TestRunID = @TestRuns_TestRunID;
END;

DECLARE @TestID_Carte_Gen INT = (SELECT TestID FROM Tests WHERE Name = 'Carte_Gen')
EXEC Tema4_Test @TestID_Carte_Gen, 'testing stuff';
