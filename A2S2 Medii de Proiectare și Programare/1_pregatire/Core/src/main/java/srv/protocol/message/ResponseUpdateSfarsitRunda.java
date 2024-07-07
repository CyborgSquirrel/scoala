package srv.protocol.message;

public class ResponseUpdateSfarsitRunda extends ResponseUpdate {
    int jocId;
    UpdateSfarsitRunda updateSfarsitRunda;

    public ResponseUpdateSfarsitRunda(int jocId, UpdateSfarsitRunda updateSfarsitRunda) {
        this.jocId = jocId;
        this.updateSfarsitRunda = updateSfarsitRunda;
    }

    public int getJocId() {
        return jocId;
    }

    public UpdateSfarsitRunda getUpdateSfarsitRunda() {
        return updateSfarsitRunda;
    }
}
