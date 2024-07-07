package srv;

import domain.Hotel;
import repo.ItemDoesntExistException;
import repo.RepoHotel;

public class SrvHotel {
    RepoHotel repoHotel;

    public SrvHotel(RepoHotel repoHotel) {
        this.repoHotel = repoHotel;
    }

    public Hotel[] getHotels() {
        return repoHotel.getAll();
    }

    public Hotel findHotel(int id) throws ItemDoesntExistException {
        return repoHotel.find(id);
    }
}
