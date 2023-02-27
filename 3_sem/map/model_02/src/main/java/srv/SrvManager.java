package srv;

public class SrvManager {
    SrvLocation srvLocation;
    SrvHotel srvHotel;
    SrvSpecialOffer srvSpecialOffer;
    SrvClient srvClient;

    public SrvManager(SrvLocation srvLocation, SrvHotel srvHotel, SrvSpecialOffer srvSpecialOffer, SrvClient srvClient) {
        this.srvLocation = srvLocation;
        this.srvHotel = srvHotel;
        this.srvSpecialOffer = srvSpecialOffer;
        this.srvClient = srvClient;
    }

    public SrvLocation getSrvLocation() {
        return srvLocation;
    }

    public SrvHotel getSrvHotel() {
        return srvHotel;
    }

    public SrvSpecialOffer getSrvSpecialOffer() {
        return srvSpecialOffer;
    }

    public SrvClient getSrvClient() {
        return srvClient;
    }
}
