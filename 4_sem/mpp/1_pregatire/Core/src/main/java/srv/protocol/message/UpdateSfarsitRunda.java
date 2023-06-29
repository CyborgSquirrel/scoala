package srv.protocol.message;

import java.io.Serializable;

public class UpdateSfarsitRunda implements Serializable {
    DTOJucatorUpdate[] DTOJucatorUpdates;

    public UpdateSfarsitRunda(DTOJucatorUpdate[] DTOJucatorUpdates) {
        this.DTOJucatorUpdates = DTOJucatorUpdates;
    }

    public DTOJucatorUpdate[] getRundaJucatorUpdates() {
        return DTOJucatorUpdates;
    }
}
