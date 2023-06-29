package srv.protocol.message;

public class RequestJucatorGhiceste extends Request {
    int jocId;
    int ghicitorJucatorId;
    int propunatorJucatorId;
    char litera;

    public RequestJucatorGhiceste(int jocId, int ghicitorJucatorId, int propunatorJucatorId, char litera) {
        this.jocId = jocId;
        this.ghicitorJucatorId = ghicitorJucatorId;
        this.propunatorJucatorId = propunatorJucatorId;
        this.litera = litera;
    }

    public int getJocId() {
        return jocId;
    }

    public int getGhicitorJucatorId() {
        return ghicitorJucatorId;
    }

    public int getPropunatorJucatorId() {
        return propunatorJucatorId;
    }

    public char getLitera() {
        return litera;
    }
}
