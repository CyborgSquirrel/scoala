CREATE TABLE Ziare(
    CodZiar INTEGER PRIMARY KEY ASC,
    NumeZiar TEXT
);

CREATE TABLE Jurnalisti(
    CodJurnalist INTEGER PRIMARY KEY ASC,
    Nume TEXT,
    Prenume TEXT,
    CodZiar INTEGER,
    FOREIGN KEY(CodZiar) REFERENCES Ziare(CodZiar)
);

CREATE TABLE Categorii(
    CodCategorie INTEGER PRIMARY KEY ASC,
    Denumire TEXT
);

CREATE TABLE Articole(
    CodArticol INTEGER PRIMARY KEY ASC,
    Titlu TEXT,
    DataPublicare INTEGER,
    Text TEXT,
    CodJurnalist INTEGER,
    CodCategorie INTEGER,
    FOREIGN KEY(CodJurnalist) REFERENCES Jurnalisti(CodJurnalist),
    FOREIGN KEY(CodCategorie) REFERENCES Categorii(CodCategorie)
);

INSERT INTO Ziare (CodZiar, NumeZiar) VALUES (1, 'Adevarul');
INSERT INTO Ziare (CodZiar, NumeZiar) VALUES (2, 'Universul');
INSERT INTO Ziare (CodZiar, NumeZiar) VALUES (3, 'Jurnalul National');

INSERT INTO Jurnalisti (CodJurnalist, Nume, Prenume, CodZiar) VALUES (1, 'Popescu', 'Andrei', 1);
INSERT INTO Jurnalisti (CodJurnalist, Nume, Prenume, CodZiar) VALUES (2, 'Ionescu', 'Maria', 2);
INSERT INTO Jurnalisti (CodJurnalist, Nume, Prenume, CodZiar) VALUES (3, 'Georgescu', 'Ioan', 3);
INSERT INTO Jurnalisti (CodJurnalist, Nume, Prenume, CodZiar) VALUES (4, 'Dumitrescu', 'Elena', 1);
INSERT INTO Jurnalisti (CodJurnalist, Nume, Prenume, CodZiar) VALUES (5, 'Marinescu', 'Alexandru', 2);

INSERT INTO Categorii (CodCategorie, Denumire) VALUES (1, 'Politica');
INSERT INTO Categorii (CodCategorie, Denumire) VALUES (2, 'Economie');
INSERT INTO Categorii (CodCategorie, Denumire) VALUES (3, 'Sport');
INSERT INTO Categorii (CodCategorie, Denumire) VALUES (4, 'Cultura');
INSERT INTO Categorii (CodCategorie, Denumire) VALUES (5, 'Tehnologie');

INSERT INTO Articole (CodArticol, Titlu, DataPublicare, Text, CodJurnalist, CodCategorie) VALUES (1, 'Politica Externa in 2024', 20240615, 'Textul articolului despre politica externa in 2024', 1, 1);
INSERT INTO Articole (CodArticol, Titlu, DataPublicare, Text, CodJurnalist, CodCategorie) VALUES (2, 'Evolutia Economica a Romaniei', 20240616, 'Textul articolului despre evolutia economica a Romaniei', 2, 2);
INSERT INTO Articole (CodArticol, Titlu, DataPublicare, Text, CodJurnalist, CodCategorie) VALUES (3, 'Campionatul European de Fotbal', 20240617, 'Textul articolului despre campionatul european de fotbal', 3, 3);
INSERT INTO Articole (CodArticol, Titlu, DataPublicare, Text, CodJurnalist, CodCategorie) VALUES (4, 'Festivalul International de Teatru', 20240618, 'Textul articolului despre festivalul international de teatru', 4, 4);
INSERT INTO Articole (CodArticol, Titlu, DataPublicare, Text, CodJurnalist, CodCategorie) VALUES (5, 'Inovatii in Tehnologie', 20240619, 'Textul articolului despre inovatii in tehnologie', 5, 5);
INSERT INTO Articole (CodArticol, Titlu, DataPublicare, Text, CodJurnalist, CodCategorie) VALUES (6, 'Evolutia Economica a Romaniei', 20240616, 'Textul articolului despre evolutia economica a Romaniei', 2, 2);
INSERT INTO Articole (CodArticol, Titlu, DataPublicare, Text, CodJurnalist, CodCategorie) VALUES (7, 'Evolutia Economica a Romaniei', 20240616, 'Textul articolului despre evolutia economica a Romaniei', 2, 2);
INSERT INTO Articole (CodArticol, Titlu, DataPublicare, Text, CodJurnalist, CodCategorie) VALUES (8, 'Evolutia Economica a Romaniei', 20240616, 'Textul articolului despre evolutia economica a Romaniei', 2, 2);

-- a)
SELECT COUNT()
FROM Articole AS A
INNER JOIN Jurnalisti AS J
    ON A.CodJurnalist = J.CodJurnalist
INNER JOIN Categorii AS C
    ON A.CodCategorie = C.CodCategorie
INNER JOIN Ziare AS Z
    ON J.CodZiar = Z.CodZiar
WHERE C.Denumire = 'Economie' AND Z.NumeZiar = 'Universul'
