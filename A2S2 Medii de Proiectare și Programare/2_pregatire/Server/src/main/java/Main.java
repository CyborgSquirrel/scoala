import repo.*;
import srv.SrvApplication;
import srv.SrvApplicationConcurrentObjectServer;
import srv.SrvApplicationImpl;

import java.rmi.ServerException;

public class Main {
    public static void main(String[] args) {
        RepoManager repoManager = new RepoManager();

        SrvApplication srvApplication = new SrvApplicationImpl(repoManager.getRepoJucator(),
                repoManager.getRepoJoc(),
                repoManager.getRepoConfiguratie());
        SrvApplicationConcurrentObjectServer server = new SrvApplicationConcurrentObjectServer(4100, srvApplication);
        try {
            server.start();
        } catch (ServerException e) {
            throw new RuntimeException(e);
        }
    }
}
