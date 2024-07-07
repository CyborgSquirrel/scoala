package repo;

import org.hibernate.SessionFactory;
import org.hibernate.boot.MetadataSources;
import org.hibernate.boot.registry.StandardServiceRegistry;
import org.hibernate.boot.registry.StandardServiceRegistryBuilder;

import java.io.FileReader;
import java.io.IOException;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

public class RepoManager {
    RepoPozitie repoPozitie;
    RepoJoc repoJoc;
    RepoJucator repoJucator;

    public RepoManager() {
        Properties properties = new Properties();
        try {
            properties.load(new FileReader("bd.config"));
        } catch (IOException e) {
            System.out.println("Cannot find bd.config " + e);
        }
        String url = properties.getProperty("jdbc.url");

        try (
                var connection = DriverManager.getConnection(url);
                var preparedStatementJucator = connection.prepareStatement(
                        "CREATE TABLE IF NOT EXISTS Jucator"
                                + "( id INTEGER PRIMARY KEY"
                                + ", alias VARCHAR(100)"
                                + ")"
                );
                var preparedStatementJoc = connection.prepareStatement(
                        "CREATE TABLE IF NOT EXISTS Joc"
                                + "( id INTEGER PRIMARY KEY"
                                + ", jucatorId INTEGER"
                                + ", timestampInceput INTEGER"
                                + ", timestampSfarsit INTEGER"
                                + ", gropiLinie_0 INTEGER"
                                + ", gropiColoana_0 INTEGER"
                                + ", gropiLinie_1 INTEGER"
                                + ", gropiColoana_1 INTEGER"
                                + ", gropiLinie_2 INTEGER"
                                + ", gropiColoana_2 INTEGER"
                                + ", gropiLinie_3 INTEGER"
                                + ", gropiColoana_3 INTEGER"
                                + ", gropiLinie_4 INTEGER"
                                + ", gropiColoana_4 INTEGER"
                                + ", punctaj INTEGER"
                                + ", finalizat INTEGER"
                                + ", FOREIGN KEY (jucatorId) REFERENCES Jucator(id)"
                                + ")"
                );
                var preparedStatementPozitie = connection.prepareStatement(
                        "CREATE TABLE IF NOT EXISTS Pozitie"
                                + "( id INTEGER PRIMARY KEY"
                                + ", jocId INTEGER"
                                + ", linie INTEGER"
                                + ", coloana INTEGER"
                                + ", FOREIGN KEY (jocId) REFERENCES Joc(id)"
                                + ")"
                );
        ) {
            preparedStatementJucator.execute();
            preparedStatementJoc.execute();
            preparedStatementPozitie.execute();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        // SessionFactory
        final StandardServiceRegistry registry = new StandardServiceRegistryBuilder()
                .configure()
                .build();

        SessionFactory sessionFactory = null;
        try {
            sessionFactory = new MetadataSources(registry).buildMetadata().buildSessionFactory();
        } catch (Exception e) {
            System.err.println("Exceptie " + e);
            StandardServiceRegistryBuilder.destroy(registry);
        }

        repoJucator = new RepoJucatorDb(url);
        repoJoc = new RepoJocDb(url);
        repoPozitie = new RepoPozitieHbm(sessionFactory);
    }

    public RepoPozitie getRepoPozitie() {
        return repoPozitie;
    }

    public RepoJoc getRepoJoc() {
        return repoJoc;
    }

    public RepoJucator getRepoJucator() {
        return repoJucator;
    }
}
