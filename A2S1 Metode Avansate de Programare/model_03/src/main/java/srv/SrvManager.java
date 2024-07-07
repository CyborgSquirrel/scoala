package srv;

public class SrvManager {
    SrvClient srvClient;
    SrvFlight srvFlight;
    SrvTicket srvTicket;

    public SrvManager(SrvClient srvClient, SrvFlight srvFlight, SrvTicket srvTicket) {
        this.srvClient = srvClient;
        this.srvFlight = srvFlight;
        this.srvTicket = srvTicket;
    }

    public SrvClient getSrvClient() {
        return srvClient;
    }

    public SrvFlight getSrvFlight() {
        return srvFlight;
    }

    public SrvTicket getSrvTicket() {
        return srvTicket;
    }
}
