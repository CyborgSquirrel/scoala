package srv.protocol.message;

import java.io.Serializable;

public class DTOJucatorUpdate implements Serializable {
    int ghicitorJucatorId;
    int propunatorJucatorId;
    int punctaj;
    char litera;
    Integer[] positions;

    public DTOJucatorUpdate() {

    }

    public DTOJucatorUpdate(int ghicitorJucatorId, int propunatorJucatorId, int punctaj, char litera, Integer[] positions) {
        this.ghicitorJucatorId = ghicitorJucatorId;
        this.propunatorJucatorId = propunatorJucatorId;
        this.punctaj = punctaj;
        this.litera = litera;
        this.positions = positions;
    }

    public int getGhicitorJucatorId() {
        return ghicitorJucatorId;
    }

    public int getPropunatorJucatorId() {
        return propunatorJucatorId;
    }

    public int getPunctaj() {
        return punctaj;
    }

    public char getLitera() {
        return litera;
    }

    public Integer[] getPositions() {
        return positions;
    }
}
