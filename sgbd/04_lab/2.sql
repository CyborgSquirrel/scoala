-- dirty reads

BEGIN
    SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
--     SET TRANSACTION ISOLATION LEVEL READ COMMITTED;

    BEGIN TRAN;
        SELECT * FROM Biblioteca.dbo.Carte WHERE id = 53192;
    COMMIT TRAN;
END

-- non-repeatable reads

BEGIN
    BEGIN TRAN;
        UPDATE Biblioteca.dbo.Carte
        SET titlu = 'hehehe ha'
        WHERE id = 53192;
    COMMIT TRAN;
END;

-- phantom reads

BEGIN
    BEGIN TRAN;
        INSERT INTO Biblioteca.dbo.Carte
        (editura_id, titlu, data_publicare)
        VALUES
        (54, 'Black Swan', DATEFROMPARTS(2000, 8, 15));
    COMMIT TRAN;
END;

-- deadlock

BEGIN
    SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
    BEGIN TRAN;
        UPDATE Biblioteca.dbo.Carte
        SET titlu = '3 hehehe ha'
        WHERE id = 53195;
        WAITFOR DELAY '00:00:07';
        UPDATE Biblioteca.dbo.Carte
        SET titlu = '4 hehehe ha'
        WHERE id = 53192;
    ROLLBACK TRAN;
END