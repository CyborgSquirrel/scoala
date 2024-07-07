package srv.protocol.message;

import java.io.Serializable;

public class DTOClasamentItem implements Serializable {
    int jucatorId;
    String jucatorNume;
    int punctaj;

    public DTOClasamentItem(int jucatorId, String jucatorNume, int punctaj) {
        this.jucatorId = jucatorId;
        this.jucatorNume = jucatorNume;
        this.punctaj = punctaj;
    }

    public int getJucatorId() {
        return jucatorId;
    }

    public String getJucatorNume() {
        return jucatorNume;
    }

    public int getPunctaj() {
        return punctaj;
    }
}
