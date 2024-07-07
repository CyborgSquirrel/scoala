package srv;

import domain.Client;
import repo.ItemDoesntExistException;
import repo.RepoClient;

public class SrvClient {
    RepoClient repoClient;

    public SrvClient(RepoClient repoClient) {
        this.repoClient = repoClient;
    }

    public Client findClient(int id) throws ItemDoesntExistException {
        return repoClient.find(id);
    }
}
