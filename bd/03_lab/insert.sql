-- cod_c este IDENTITY
-- nume este VARCHAR
INSERT INTO Categorii (nume) VALUES ('suc');
INSERT INTO Categorii (nume) VALUES ('detergent'), ('flori');

-- cod_c nu este IDENTITY
-- nume este NVARCHAR
INSERT INTO Categorii (cod_c, nume) VALUES (1, N'mâncare');
INSERT INTO Categorii (cod_c, nume) VALUES (2, N'săpun'), (3, N'pastă de dinți');
