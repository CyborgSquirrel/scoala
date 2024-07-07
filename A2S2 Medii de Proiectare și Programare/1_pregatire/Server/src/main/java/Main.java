import org.hibernate.SessionFactory;
import org.hibernate.boot.MetadataSources;
import org.hibernate.boot.registry.StandardServiceRegistry;
import org.hibernate.boot.registry.StandardServiceRegistryBuilder;
import repo.*;
import srv.SrvApplication;
import srv.SrvApplicationConcurrentObjectServer;
import srv.SrvApplicationImpl;

import java.io.FileReader;
import java.io.IOException;
import java.rmi.ServerException;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

public class Main {
    public static void main(String[] args) {
        RepoManager repoManager = new RepoManager();

        SrvApplication srvApplication = new SrvApplicationImpl(repoManager.getRepoJucator(),
                repoManager.getRepoJoc(),
                repoManager.getRepoGhicireLitera());
        SrvApplicationConcurrentObjectServer server = new SrvApplicationConcurrentObjectServer(4100, srvApplication);
        try {
            server.start();
        } catch (ServerException e) {
            throw new RuntimeException(e);
        }
    }
}
