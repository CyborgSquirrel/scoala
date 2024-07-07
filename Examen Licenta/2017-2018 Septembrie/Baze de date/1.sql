CREATE TABLE Companii (
  CodC INTEGER PRIMARY KEY,
  Denumire TEXT,
  Vechime INTEGER,
  Tara TEXT,
  Continent TEXT
);

CREATE TABLE Aeroporturi (
  CodA TEXT PRIMARY KEY,
  NumeAeroport TEXT,
  Oras TEXT,
  Tara TEXT,
  Continent TEXT
);

CREATE TABLE Zboruri (
  CodZbor INTEGER PRIMARY KEY,
  CodCompanie INTEGER,
  CodAeroportPlecare TEXT,
  CodAeroportSosire TEXT,
  Data TEXT,
  Ora TEXT,
  TipAvion TEXT,
  NumarLocuri INTEGER,
  FOREIGN KEY (CodCompanie) REFERENCES Companii(CodC),
  FOREIGN KEY (CodAeroportPlecare) REFERENCES Aeroporturi(CodA),
  FOREIGN KEY (CodAeroportSosire) REFERENCES Aeroporturi(CodA)
);

INSERT INTO Companii (CodC, Denumire, Vechime, Tara, Continent)
VALUES (1, 'TAROM', 65, 'Romania', 'Europa'),
       (2, 'Lufthansa', 100, 'Germania', 'Europa'),
       (3, 'Air France', 89, 'Franta', 'Europa'),
       (4, 'KLM', 98, 'Olanda', 'Europa'),
       (5, 'Alitalia', 72, 'Italia', 'Europa');

INSERT INTO Aeroporturi (CodA, NumeAeroport, Oras, Tara, Continent)
VALUES ('OTP', 'Aeroportul Henri Coanda', 'Bucuresti', 'Romania', 'Europa'),
       ('FRA', 'Aeroportul Frankfurt', 'Frankfurt', 'Germania', 'Europa'),
       ('CDG', 'Aeroportul Charles de Gaulle', 'Paris', 'Franta', 'Europa'),
       ('AMS', 'Aeroportul Schiphol', 'Amsterdam', 'Olanda', 'Europa'),
       ('FCO', 'Aeroportul Fiumicino', 'Roma', 'Italia', 'Europa');

INSERT INTO Zboruri (CodZbor, CodCompanie, CodAeroportPlecare, CodAeroportSosire, Data, Ora, TipAvion, NumarLocuri)
VALUES (1, 1, 'OTP', 'FRA', '2024-06-30', '10:00', 'Boeing 737', 180),
       (2, 2, 'FRA', 'CDG', '2024-06-30', '12:00', 'Airbus A320', 150),
       (3, 3, 'CDG', 'AMS', '2024-06-30', '14:00', 'Embraer 190', 100),
       (4, 4, 'AMS', 'FCO', '2024-06-30', '16:00', 'ATR 72', 70),
       (5, 5, 'FCO', 'OTP', '2024-06-30', '18:00', 'Bombardier CRJ', 90),
       (6, 1, 'OTP', 'FRA', '2024-07-01', '10:00', 'Boeing 737', 180),
       (7, 2, 'FRA', 'CDG', '2024-07-01', '12:00', 'Airbus A320', 150),
       (8, 3, 'CDG', 'AMS', '2024-07-01', '14:00', 'Embraer 190', 100),
       (9, 4, 'AMS', 'FCO', '2024-07-01', '16:00', 'ATR 72', 70),
       (10, 5, 'FCO', 'OTP', '2024-07-01', '18:00', 'Bombardier CRJ', 90),
       (11, 1, 'OTP', 'FRA', '2024-07-02', '10:00', 'Boeing 737', 180);
       -- (12, 2, 'FRA', 'CDG', '2024-07-02', '12:00', 'Airbus A320', 150),
       -- (13, 3, 'CDG', 'AMS', '2024-07-02', '14:00', 'Embraer 190', 100),
       -- (14, 4, 'AMS', 'FCO', '2024-07-02', '16:00', 'ATR 72', 70),
       -- (15, 5, 'FCO', 'OTP', '2024-07-02', '18:00', 'Bombardier CRJ', 90);

SELECT
    IIF(Plecare.Count IS NULL, 0, Plecare.Count)
    + IIF(Sosire.Count IS NULL, 0, Sosire.Count),
    A.NumeAeroport
FROM Aeroporturi AS A
INNER JOIN (
    SELECT Z.CodAeroportPlecare AS Cod, COUNT() AS Count
    FROM Zboruri AS Z
    GROUP BY Z.CodAeroportPlecare
) AS Plecare ON Plecare.Cod = A.CodA
INNER JOIN (
    SELECT Z.CodAeroportSosire AS Cod, COUNT() AS Count
    FROM Zboruri AS Z
    GROUP BY Z.CodAeroportSosire
) AS Sosire ON Sosire.Cod = A.CodA
;
