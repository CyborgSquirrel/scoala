package srv;

import domain.Location;
import repo.ItemDoesntExistException;
import repo.RepoLocation;

public class SrvLocation {
    RepoLocation repoLocation;

    public SrvLocation(RepoLocation repoLocation) {
        this.repoLocation = repoLocation;
    }

    public Location findLocation(int id) throws ItemDoesntExistException {
        return repoLocation.find(id);
    }

    public Location[] getLocations() {
        return repoLocation.getAll();
    }
}
