SELECT COUNT()
FROM Articole AS A
INNER JOIN Jurnalisti AS J
    ON A.CodJurnalist = J.CodJurnalist
INNER JOIN Categorii AS C
    ON A.CodCategorie = C.CodCategorie
INNER JOIN Ziare AS Z
    ON J.CodZiar = Z.CodZiar
WHERE C.Denumire = "Economie" AND Z.NumeZiar = "Universul"
