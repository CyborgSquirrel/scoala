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
    RepoConfiguratie repoConfiguratie;
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
                var preparedStatementConfiguratie = connection.prepareStatement(
                        "CREATE TABLE IF NOT EXISTS Configuratie"
                                + "( id INTEGER PRIMARY KEY"
                                + ", linie INTEGER"
                                + ", coloana INTEGER"
                                + ", indiciu VARCHAR(250)"
                                + ")"
                );
                var preparedStatementJoc = connection.prepareStatement(
                        "CREATE TABLE IF NOT EXISTS Joc"
                                + "( id INTEGER PRIMARY KEY"
                                + ", jucatorId INTEGER"
                                + ", configuratieId INTEGER"
                                + ", incercari INTEGER"
                                + ", timestampInceput INTEGER"
                                + ", finalizat INTEGER"
                                + ", ghicit INTEGER"
                                + ", FOREIGN KEY (jucatorId) REFERENCES Jucator(id)"
                                + ", FOREIGN KEY (configuratieId) REFERENCES Configuratie(id)"
                                + ")"
                );
        ) {
            preparedStatementJucator.execute();
            preparedStatementConfiguratie.execute();
            preparedStatementJoc.execute();
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
        repoConfiguratie = new RepoConfiguratieDb(url);
    }

    public RepoConfiguratie getRepoConfiguratie() {
        return repoConfiguratie;
    }

    public RepoJoc getRepoJoc() {
        return repoJoc;
    }

    public RepoJucator getRepoJucator() {
        return repoJucator;
    }
}
