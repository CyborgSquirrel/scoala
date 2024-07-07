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
    RepoGhicireLitera repoGhicireLitera;
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
                                + ", nume VARCHAR(100)"
                                + ", parola VARCHAR(100)"
                                + ")"
                );
                var preparedStatementJoc = connection.prepareStatement(
                        "CREATE TABLE IF NOT EXISTS Joc"
                                + "( id INTEGER PRIMARY KEY"
                                + ", jucator0Id INTEGER"
                                + ", jucator0Cuvant VARCHAR(100)"
                                + ", jucator1Id INTEGER"
                                + ", jucator1Cuvant VARCHAR(100)"
                                + ", jucator2Id INTEGER"
                                + ", jucator2Cuvant VARCHAR(100)"
                                + ", FOREIGN KEY (jucator0Id) REFERENCES Jucator(id)"
                                + ", FOREIGN KEY (jucator1Id) REFERENCES Jucator(id)"
                                + ", FOREIGN KEY (jucator2Id) REFERENCES Jucator(id)"
                                + ")"
                );
                var preparedStatementGhicireLitera = connection.prepareStatement(
                        "CREATE TABLE IF NOT EXISTS GhicireLitera"
                                + "( jocId INTEGER"
                                + ", runda INTEGER"
                                + ", ghicitorJucatorId INTEGER"
                                + ", propunatorJucatorId INTEGER"
                                + ", litera CHARACTER(1)"
                                + ", punctaj INTEGER"
                                + ", PRIMARY KEY (jocId, runda, ghicitorJucatorId)"
                                + ", FOREIGN KEY (jocId) REFERENCES Joc(id)"
                                + ", FOREIGN KEY (ghicitorJucatorId) REFERENCES Jucator(id)"
                                + ", FOREIGN KEY (propunatorJucatorId) REFERENCES Jucator(id)"
                                + ")"
                );
        ) {
            preparedStatementJucator.execute();
            preparedStatementJoc.execute();
            preparedStatementGhicireLitera.execute();
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
        repoJoc = new RepoJocHbm(sessionFactory);
        repoGhicireLitera = new RepoGhicireLiteraHbm(sessionFactory);
    }

    public RepoGhicireLitera getRepoGhicireLitera() {
        return repoGhicireLitera;
    }

    public RepoJoc getRepoJoc() {
        return repoJoc;
    }

    public RepoJucator getRepoJucator() {
        return repoJucator;
    }
}
