package srv.protocol.message;

import java.io.Serializable;

public class UpdateStartJoc implements Serializable {
    DTOStartJocJucator[] jucatori;

    public UpdateStartJoc(DTOStartJocJucator[] jucatori) {
        this.jucatori = jucatori;
    }

    public DTOStartJocJucator[] getJucatori() {
        return jucatori;
    }
}
