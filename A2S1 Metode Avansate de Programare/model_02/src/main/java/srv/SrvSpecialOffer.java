package srv;

import domain.Client;
import domain.SpecialOffer;
import repo.RepoSpecialOffer;

import java.util.Arrays;
import java.util.Date;

public class SrvSpecialOffer {
    RepoSpecialOffer repoSpecialOffer;

    public SrvSpecialOffer(RepoSpecialOffer repoSpecialOffer) {
        this.repoSpecialOffer = repoSpecialOffer;
    }

    public SpecialOffer[] getSpecialOffersInRangeForHotel(int hotelId, Date startDate, Date endDate) {
        return Arrays.stream(repoSpecialOffer.getAll())
                .filter(specialOffer ->
                        (specialOffer.getStartDate().equals(startDate) || specialOffer.getStartDate().after(startDate))
                        && (specialOffer.getEndDate().equals(endDate) || specialOffer.getEndDate().before(endDate))
                        && specialOffer.getHotelId() == hotelId)
                .toArray(SpecialOffer[]::new);
    }

    public SpecialOffer[] getClientEligibleSpecialOffers(Client client) {
        return Arrays.stream(repoSpecialOffer.getAll())
                .filter(specialOffer -> client.getFidelityGrade() > specialOffer.getPercents())
                .toArray(SpecialOffer[]::new);
    }

    public SpecialOffer[] getSpecialOffers() {
        return repoSpecialOffer.getAll();
    }
}
