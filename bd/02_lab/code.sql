CREATE DATABASE [Laborator2224-1BD2022];
GO

USE [Laborator2224-1BD2022];
-- relatie one-to-one
CREATE TABLE Persoane
(cod_persoana INT PRIMARY KEY
, nume VARCHAR(100)
, data_nasterii DATE
, cnp VARCHAR(13)
);

CREATE TABLE Buletine
(cod_buletin INT PRIMARY KEY
, numar INT
, seria VARCHAR(2)
, data_eliberarii DATE
, date_expirarii DATE
, unitate VARCHAR(100)
, cod_persoana INT FOREIGN KEY REFERENCES Persoane(cod_persoana)
);
