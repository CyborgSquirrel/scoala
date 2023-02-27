DELETE FROM Biblioteca.dbo.Abonament;
DELETE FROM Biblioteca.dbo.Autor_Carte;
DELETE FROM Biblioteca.dbo.Carte_Gen;
DELETE FROM Biblioteca.dbo.Autor;
DELETE FROM Biblioteca.dbo.LocRaft;
DELETE FROM Biblioteca.dbo.Raft;
DELETE FROM Biblioteca.dbo.Camera;
DELETE FROM Biblioteca.dbo.Cladire;
DELETE FROM Biblioteca.dbo.Imprumut;
DELETE FROM Biblioteca.dbo.Exemplar;
DELETE FROM Biblioteca.dbo.Carte;
DELETE FROM Biblioteca.dbo.Editura;
DELETE FROM Biblioteca.dbo.Gen;

-- GEN
INSERT INTO Biblioteca.dbo.Gen
VALUES ('fiction')
DECLARE @fictionId INT = @@IDENTITY

INSERT INTO Biblioteca.dbo.Gen
VALUES ('nonfiction')
DECLARE @nonfictionId INT = @@IDENTITY

INSERT INTO Biblioteca.dbo.Gen
VALUES ('classic')
DECLARE @classicId INT = @@IDENTITY

INSERT INTO Biblioteca.dbo.Gen
VALUES ('dystopia')
DECLARE @dystopiaId INT = @@IDENTITY

INSERT INTO Biblioteca.dbo.Gen
VALUES ('informatics')
DECLARE @informaticsId INT = @@IDENTITY

-- EDITURA
INSERT INTO Biblioteca.dbo.Editura
VALUES ('Modern Library')
DECLARE @modernLibraryId INT = @@IDENTITY

INSERT INTO Biblioteca.dbo.Editura
VALUES ('Genever Benning')
DECLARE @geneverBenningId INT = @@IDENTITY

INSERT INTO Biblioteca.dbo.Editura
VALUES ('Penguin Books')
DECLARE @penguinBooksId INT = @@IDENTITY

-- AUTOR
INSERT INTO Biblioteca.dbo.Autor
(nume, prenume)
VALUES ('Dostoevsky', 'Fyodor')
DECLARE @fyodorDostoevskyId INT = @@IDENTITY

INSERT INTO Biblioteca.dbo.Autor
(nume, prenume)
VALUES ('Nystrom', 'Robert')
DECLARE @robertNystromId INT = @@IDENTITY

INSERT INTO Biblioteca.dbo.Autor
(nume, prenume)
VALUES ('Orwell', 'George')
DECLARE @georgeOrwellId INT = @@IDENTITY

-- CARTE
INSERT INTO Biblioteca.dbo.Carte
(editura_id, titlu, data_publicare)
VALUES (@modernLibraryId, 'The Idiot', datefromparts(2003, 4, 8))
DECLARE @theIdiotId INT = @@IDENTITY

INSERT INTO Biblioteca.dbo.Carte
(editura_id, titlu, data_publicare)
VALUES (@geneverBenningId, 'Game Programming Patterns', datefromparts(2011, 1, 1))
DECLARE @gameProgrammingPatternsId INT = @@IDENTITY

INSERT INTO Biblioteca.dbo.Carte
(editura_id, titlu, data_publicare)
VALUES (@geneverBenningId, 'Crafting Interpreters', datefromparts(2021, 7, 28))
DECLARE @craftingInterpretersId INT = @@IDENTITY

INSERT INTO Biblioteca.dbo.Carte
(editura_id, titlu, data_publicare)
VALUES (@penguinBooksId, '1984', datefromparts(2008, 7, 3))
DECLARE @1984Id INT = @@IDENTITY

INSERT INTO Biblioteca.dbo.Carte
(editura_id, titlu, data_publicare)
VALUES (@penguinBooksId, 'Animal Farm', datefromparts(2008, 7, 3))
DECLARE @animalFarmId INT = @@IDENTITY

-- AUTOR CARTE
INSERT INTO Biblioteca.dbo.Autor_Carte
(autor_id, carte_id)
VALUES
  (@fyodorDostoevskyId, @theIdiotId)
, (@robertNystromId, @gameProgrammingPatternsId)
, (@robertNystromId, @craftingInterpretersId)
, (@georgeOrwellId, @1984Id)
, (@georgeOrwellId, @animalFarmId)

-- CARTE GEN
INSERT INTO Biblioteca.dbo.Carte_Gen
(carte_id, gen_id)
VALUES
  (@theIdiotId, @fictionId)
, (@theIdiotId, @classicId)
, (@gameProgrammingPatternsId, @nonfictionId)
, (@gameProgrammingPatternsId, @informaticsId)
, (@craftingInterpretersId, @nonfictionId)
, (@craftingInterpretersId, @informaticsId)
, (@1984Id, @fictionId)
, (@1984Id, @classicId)
, (@1984Id, @dystopiaId)
, (@animalFarmId, @fictionId)
, (@animalFarmId, @classicId)

-- CLADIRE
INSERT INTO Biblioteca.dbo.Cladire
(nume, adresa)
VALUES ('FSEGA', 'Teodor Mihali 58-60, Cluj, Romania')
DECLARE @fsegaId INT = @@IDENTITY

INSERT INTO Biblioteca.dbo.Cladire
(nume, adresa)
VALUES ('Library of Alexandria', 'Alexandria, Egypt')
DECLARE @libraryOfAlexandriaId INT = @@IDENTITY

-- CAMERA
INSERT INTO Biblioteca.dbo.Camera
(cladire_id, nume)
VALUES (@fsegaId, 'X123')
DECLARE @x123Id INT = @@IDENTITY

INSERT INTO Biblioteca.dbo.Camera
(cladire_id, nume)
VALUES (@fsegaId, 'X124')
DECLARE @x124Id INT = @@IDENTITY

INSERT INTO Biblioteca.dbo.Camera
(cladire_id, nume)
VALUES (@libraryOfAlexandriaId, 'ABC')
DECLARE @abcId INT = @@IDENTITY

-- RAFT
INSERT INTO Biblioteca.dbo.Raft
(camera_id, latime, inaltime)
VALUES (@x123Id, 20, 6)
DECLARE @raft0 INT = @@IDENTITY

INSERT INTO Biblioteca.dbo.Raft
(camera_id, latime, inaltime)
VALUES (@x123Id, 18, 6)
DECLARE @raft1 INT = @@IDENTITY

INSERT INTO Biblioteca.dbo.Raft
(camera_id, latime, inaltime)
VALUES (@x124Id, 20, 6)
DECLARE @raft2 INT = @@IDENTITY

INSERT INTO Biblioteca.dbo.Raft
(camera_id, latime, inaltime)
VALUES (@abcId, 40, 8)
DECLARE @raft3 INT = @@IDENTITY

-- EXEMPLAR
INSERT INTO Biblioteca.dbo.Exemplar
(carte_id, data_achizitionat)
VALUES (@theIdiotId, datefromparts(2022, 2, 18))
DECLARE @exemplar0 INT = @@IDENTITY 

INSERT INTO Biblioteca.dbo.LocRaft
(raft_id, coloana, linie, exemplar_id)
VALUES (@raft0, 2, 3, @exemplar0)

INSERT INTO Biblioteca.dbo.Exemplar
(carte_id, data_achizitionat)
VALUES (@gameProgrammingPatternsId, datefromparts(2022, 2, 21))
DECLARE @exemplar1 INT = @@IDENTITY 

INSERT INTO Biblioteca.dbo.LocRaft
(raft_id, coloana, linie, exemplar_id)
VALUES (@raft2, 5, 7, @exemplar1)

INSERT INTO Biblioteca.dbo.Exemplar
(carte_id, data_achizitionat)
VALUES (@animalFarmId, datefromparts(2021, 10, 28))
DECLARE @exemplar2 INT = @@IDENTITY 

INSERT INTO Biblioteca.dbo.LocRaft
(raft_id, coloana, linie, exemplar_id)
VALUES (@raft1, 2, 4, @exemplar2)

-- ABONAMENT
INSERT INTO Biblioteca.dbo.Abonament
(detinator_nume, detinator_prenume, data_inceput, data_sfarsit)
VALUES ('Jardan', 'Andrei', datefromparts(2019, 7, 12), datefromparts(2024, 3, 8))
DECLARE @abonament0 INT = @@IDENTITY

-- IMPRUMUT
INSERT INTO Biblioteca.dbo.Imprumut
(exemplar_id, abonament_id, data_inceput, data_sfarsit)
VALUES (@exemplar0, @abonament0, datefromparts(2020, 4, 9), datefromparts(2020, 4, 19))

;
