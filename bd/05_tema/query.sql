-- Creati 10 interogari pe baza de date creata pentru primul
-- laborator. Este necesar ca interogarile sa contine cel putin
-- urmatoarele:
-- 
-- - 5 interogari ce folosesc where
-- - 3 interogari ce folosesc group by
-- - 2 interogari ce folosesc distinct
-- - 2 interogari cu having
-- - 7 interogari ce extrag informatii din mai mult de 2 tabele
-- - 2 interogari pe tabele aflate in relatie m-n
-- 
-- Interogarile trebuie sa fie relevante pentru tema bazei de date si
-- for returna informatii utile unui potential utilizator.

-- Ramas:
--
-- 0 interogari
--
-- - 0 interogari ce folosesc where
-- - 0 interogari ce folosesc group by
-- - 0 interogari ce folosesc distinct
-- - 0 interogari cu having
-- - 0 interogari ce extrag informatii din mai mult de 2 tabele
-- - 0 interogari pe tabele aflate in relatie m-n

-- # Titlu carte cu lista de genuri
-- group by
-- mai mult de 2 tabele
-- m-n
SELECT c.titlu 'Titlu', STRING_AGG(g.nume, ' ') 'Genuri'
FROM Carte_Gen cg
INNER JOIN Carte c ON c.id = cg.carte_id
INNER JOIN Gen g ON g.id = cg.gen_id
GROUP BY c.id, c.titlu
;

-- # Toti autorii care au scris minim 2 carti
-- group by
-- having
-- m-n
SELECT 'Nume' = a.prenume  + ' ' + a.nume 
FROM Autor_Carte ac 
INNER JOIN Autor a ON a.id = ac.autor_id 
GROUP BY a.id, a.nume, a.prenume
HAVING COUNT(ac.carte_id) >= 2
;

-- # Locatia intreaga a unui exemplar
-- where
-- mai mult de 2 tabele
SELECT
	'Titlu Carte' = c3.titlu,
	'Locatia' =
		  'raftul ' + CONVERT(VARCHAR(100), r.id)
		+ ' camera ' + c.nume
		+ ', ' + c2.nume
		+ ', ' + c2.adresa
FROM Exemplar e
INNER JOIN Carte c3 ON c3.id = e.carte_id 
INNER JOIN LocRaft lr ON lr.exemplar_id = e.id 
INNER JOIN Raft r ON r.id = lr.raft_id 
INNER JOIN Camera c ON c.id = r.camera_id 
INNER JOIN Cladire c2 ON c2.id = c.cladire_id 
WHERE e.id = 4
;


-- # Rafturile care au 0 carti
-- group by
-- having
-- mai mult de 2 tabele
SELECT
	'Locatia' =
		  'raftul ' + CONVERT(VARCHAR(100), r.id)
		+ ' camera ' + c.nume
		+ ', ' + c2.nume
		+ ', ' + c2.adresa
FROM Raft r 
LEFT JOIN LocRaft lr ON lr.raft_id = r.id 
INNER JOIN Camera c ON c.id = r.camera_id 
INNER JOIN Cladire c2 ON c2.id = c.cladire_id 
GROUP BY r.id, c.nume, c2.nume, c2.adresa 
HAVING COUNT(lr.raft_id) = 0
;

-- # Toate numele distincte de carti (daca exista mai multe editii)
-- distinct
SELECT DISTINCT c.titlu 
FROM Carte c
;

-- # Toate exemplarele pentru care exista minim un imprumut
-- distinct
-- mai mult de 2 tabele
SELECT DISTINCT 'Id Exemplar' = e.id, 'Titlu' = c.titlu 
FROM Exemplar e 
INNER JOIN Imprumut i ON i.exemplar_id = e.id 
INNER JOIN Carte c ON c.id = e.carte_id 
;

-- # Imprumuturi intre doua dati, cu abonamentul asociat
-- where
-- mai mult de 2 tabele
SELECT 'Detinator' = a.detinator_prenume + ' ' + a.detinator_nume,
       'Titlu' = c.titlu 
FROM Abonament a 
INNER JOIN Imprumut i ON i.abonament_id = a.id 
INNER JOIN Exemplar e ON e.id = i.exemplar_id 
INNER JOIN Carte c ON c.id = e.carte_id 
WHERE     i.data_inceput >= DATEFROMPARTS(2010, 10, 10)
      AND i.data_sfarsit <= DATEFROMPARTS(2025, 5, 4) 
;

-- # Toate exemplarele de carti de la o editura
-- where
-- mai mult de 2 tabele
SELECT e2.id, c.titlu, e.nume 
FROM Editura e 
INNER JOIN Carte c ON c.editura_id = e.id 
INNER JOIN Exemplar e2 ON e2.carte_id = c.id 
WHERE e.id = 53 -- Modern Library
;

-- # Toate cartile care au genul fiction
-- where
-- mai mult de 2 tabele
SELECT c.titlu 
FROM Carte c 
INNER JOIN Carte_Gen cg on cg.carte_id = c.id 
INNER JOIN Gen g ON g.id = cg.gen_id 
WHERE g.id = 46 -- fiction
;

-- # Toate abonamentele care au expirat
-- where
SELECT *
FROM Abonament a 
WHERE a.data_sfarsit <= GETDATE()
;
