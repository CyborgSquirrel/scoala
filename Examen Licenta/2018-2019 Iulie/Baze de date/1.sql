-- Create the Pacienti table
CREATE TABLE Pacienti (
    CodP INTEGER PRIMARY KEY,
    Nume TEXT NOT NULL,
    Prenume TEXT NOT NULL,
    Varsta INTEGER NOT NULL,
    DataNasterii DATE NOT NULL
);

-- Create the Proceduri table
CREATE TABLE Proceduri (
    CodProc INTEGER PRIMARY KEY,
    Nume TEXT NOT NULL,
    Descriere TEXT NOT NULL,
    Pret REAL NOT NULL
);

-- Create the FisePacienti table
CREATE TABLE FisePacienti (
    CodPacient INTEGER NOT NULL,
    CodProcedura INTEGER NOT NULL,
    Data DATE NOT NULL,
    NumeDoctor TEXT NOT NULL,
    PrenumeDoctor TEXT NOT NULL,
    SpecializareDoctor TEXT NOT NULL,
    VechimeDoctor INTEGER NOT NULL,
    FOREIGN KEY (CodPacient) REFERENCES Pacienti(CodP),
    FOREIGN KEY (CodProcedura) REFERENCES Proceduri(CodProc)
);

-- Insert sample data into the Pacienti table
INSERT INTO Pacienti (CodP, Nume, Prenume, Varsta, DataNasterii) VALUES
(1, 'Popescu', 'Ion', 45, '1979-03-14'),
(2, 'Ionescu', 'Maria', 30, '1993-07-21'),
(3, 'Georgescu', 'Andrei', 55, '1969-12-10'),
(4, 'Marinescu', 'Elena', 40, '1984-08-05'),
(5, 'Dumitrescu', 'Alexandru', 65, '1959-11-23');

-- Insert sample data into the Proceduri table
INSERT INTO Proceduri (CodProc, Nume, Descriere, Pret) VALUES
(1, 'Consultatie generala', 'Consultatie initiala pentru evaluare', 100.0),
(2, 'Radiografie', 'Radiografie toracica', 250.0),
(3, 'Ecografie abdominala', 'Examinare ecografica a abdomenului', 300.0),
(4, 'Analize de sange', 'Set complet de analize de sange', 150.0),
(5, 'Consultatie cardiologica', 'Consultatie specializata cardiologica', 200.0);

-- Insert sample data into the FisePacienti table
INSERT INTO FisePacienti (CodPacient, CodProcedura, Data, NumeDoctor, PrenumeDoctor, SpecializareDoctor, VechimeDoctor) VALUES
(1, 1, '2024-01-10', 'Ionescu', 'Andrei', 'Medicina Generala', 15),
(2, 2, '2024-01-12', 'Popescu', 'Ioana', 'Radiologie', 10),
(3, 3, '2024-01-15', 'Georgescu', 'Mihai', 'Ecografie', 20),
(4, 4, '2024-01-20', 'Marinescu', 'Ana', 'Laborator', 8),
(5, 5, '2024-01-22', 'Dumitrescu', 'Alexandru', 'Cardiologie', 25),
(1, 3, '2024-02-10', 'Popa', 'Daniel', 'Ecografie', 12),
(2, 1, '2024-02-14', 'Mihai', 'Adrian', 'Medicina Generala', 5),
(3, 4, '2024-03-01', 'Vasilescu', 'Elena', 'Laborator', 7),
(4, 5, '2024-03-10', 'Iliescu', 'George', 'Cardiologie', 30),
(5, 2, '2024-03-15', 'Constantinescu', 'Florin', 'Radiologie', 18);

SELECT SpecializareDoctor AS Specializare, COUNT() AS NrProceduri, SUM(Pret) AS Suma
FROM FisePacienti AS F
INNER JOIN Proceduri AS P ON F.CodProcedura = P.CodProc
GROUP BY F.SpecializareDoctor
HAVING SUM(Pret) = (
    SELECT MAX(TotalPret)
    FROM (
        SELECT SUM(Pret) AS TotalPret
        FROM FisePacienti AS F
        INNER JOIN Proceduri AS P ON F.CodProcedura = P.CodProc
        GROUP BY F.SpecializareDoctor
    )
)
