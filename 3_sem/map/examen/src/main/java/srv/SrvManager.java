package srv;

public class SrvManager {
    SrvPersoana srvPersoana;
    SrvNevoie srvNevoie;

    public SrvManager(SrvPersoana srvPersoana, SrvNevoie srvNevoie) {
        this.srvPersoana = srvPersoana;
        this.srvNevoie = srvNevoie;
    }

    public SrvPersoana getSrvPersoana() {
        return srvPersoana;
    }

    public SrvNevoie getSrvNevoie() {
        return srvNevoie;
    }
}
