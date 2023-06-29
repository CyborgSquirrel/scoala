-- dirty reads

BEGIN
    BEGIN TRAN;
        UPDATE Biblioteca.dbo.Carte
        SET titlu = 'War and Peace'
        WHERE id = 53192;
    COMMIT TRAN;
    BEGIN TRAN;
        UPDATE Biblioteca.dbo.Carte
        SET titlu = 'hehehe ha'
        WHERE id = 53192;
        WAITFOR DELAY '00:00:7';
    ROLLBACK TRAN;
END;

-- non-repeatable reads

BEGIN
    SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
--     SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;

    BEGIN TRAN;
        UPDATE Biblioteca.dbo.Carte
        SET titlu = 'War and Peace'
        WHERE id = 53192;
    COMMIT TRAN;
    BEGIN TRAN;
        SELECT * FROM Biblioteca.dbo.Carte;
        WAITFOR DELAY '00:00:07';
        SELECT * FROM Biblioteca.dbo.Carte;
    COMMIT TRAN;
END;

-- phantom reads

BEGIN
    SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
--     SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;

    BEGIN TRAN;
        DELETE Biblioteca.dbo.Carte
        WHERE titlu = 'Black Swan';
    COMMIT TRAN;
    BEGIN TRAN;
        SELECT * FROM Biblioteca.dbo.Carte WHERE id >= 50000 AND id <= 55000;
        WAITFOR DELAY '00:00:07';
        SELECT * FROM Biblioteca.dbo.Carte WHERE id >= 50000 AND id <= 55000;
    COMMIT TRAN;
END;

-- deadlock

-- solutie: accesarea resurselor in aceeasi ordine
BEGIN
    BEGIN TRAN;
        UPDATE Biblioteca.dbo.Carte
        SET titlu = '1 hehehe ha'
        WHERE id = 53192;
        WAITFOR DELAY '00:00:07';
        UPDATE Biblioteca.dbo.Carte
        SET titlu = '2 hehehe ha'
        WHERE id = 53195;
    ROLLBACK TRAN;
END