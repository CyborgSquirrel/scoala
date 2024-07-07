package srv;

import domain.Client;
import repo.ItemDoesntExistException;
import repo.RepoClient;

public class SrvClient {
    RepoClient repoClient;

    public SrvClient(RepoClient repoClient) {
        this.repoClient = repoClient;
    }

    public Client findClient(String username) throws ItemDoesntExistException {
        return repoClient.find(username);
    }
}
