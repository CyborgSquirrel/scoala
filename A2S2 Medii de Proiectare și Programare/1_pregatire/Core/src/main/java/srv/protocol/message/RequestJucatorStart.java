package srv.protocol.message;

public class RequestJucatorStart extends Request {
    int jucatorId;
    String cuvant;

    public RequestJucatorStart(int jucatorId, String cuvant) {
        this.jucatorId = jucatorId;
        this.cuvant = cuvant;
    }

    public int getJucatorId() {
        return jucatorId;
    }

    public String getCuvant() {
        return cuvant;
    }
}
