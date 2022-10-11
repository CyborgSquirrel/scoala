CREATE DATABASE [Biblioteca];
GO

USE [Biblioteca];

CREATE TABLE Autor
( id INT PRIMARY KEY
, nume VARCHAR(100)
, prenume VARCHAR(100));

CREATE TABLE Editura
( id INT PRIMARY KEY
, nume VARCHAR(100));

CREATE TABLE Carte
( id INT PRIMARY KEY
, editura_id INT FOREIGN KEY REFERENCES Editura(id)
, titlu VARCHAR(100)
, data_publicare DATE);

CREATE TABLE Autor_Carte
( autor_id INT FOREIGN KEY REFERENCES Autor(id)
, carte_id INT FOREIGN KEY REFERENCES Carte(id)
, PRIMARY KEY (autor_id, carte_id));

CREATE TABLE Exemplar
( id INT PRIMARY KEY
, carte_id INT FOREIGN KEY REFERENCES Carte(id));

CREATE TABLE Gen
( id INT PRIMARY KEY
, nume VARCHAR(100))

CREATE TABLE Carte_Gen
( carte_id INT FOREIGN KEY REFERENCES Carte(id)
, gen_id INT FOREIGN KEY REFERENCES Gen(id)
, PRIMARY KEY (carte_id, gen_id));

CREATE TABLE Abonament
( id INT PRIMARY KEY
, detinator_nume VARCHAR(100)
, detinator_prenume VARCHAR(100));

CREATE TABLE Imprumut
( id INT PRIMARY KEY
, carte_id INT FOREIGN KEY REFERENCES Carte(id)
, abonament_id INT FOREIGN KEY REFERENCES Abonament(id)
, data_inceput DATE
, data_sfarsit DATE);

CREATE TABLE Cladire
( id INT PRIMARY KEY
, adresa VARCHAR(100));

CREATE TABLE Camera
( id INT PRIMARY KEY
, cladire_id INT FOREIGN KEY REFERENCES Cladire(id)
, nume VARCHAR(100));

CREATE TABLE Raft
( id INT PRIMARY KEY
, camera_id INT FOREIGN KEY REFERENCES Camera(id)
, latime INT
, inaltime INT);

CREATE TABLE LocRaft
( raft_id INT FOREIGN KEY REFERENCES Raft(id)
, coloana INT
, linie INT
, PRIMARY KEY (raft_id, coloana, linie)
, carte_id INT FOREIGN KEY REFERENCES Carte(id) UNIQUE);

GO
