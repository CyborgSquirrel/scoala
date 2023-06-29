package srv.protocol.message;

import java.io.Serializable;

public class UpdateSfarsitJoc implements Serializable {
    DTOClasamentItem[] clasament;

    public UpdateSfarsitJoc(DTOClasamentItem[] clasament) {
        this.clasament = clasament;
    }

    public DTOClasamentItem[] getClasament() {
        return clasament;
    }
}
