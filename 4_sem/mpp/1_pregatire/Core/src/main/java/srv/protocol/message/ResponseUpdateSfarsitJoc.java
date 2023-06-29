package srv.protocol.message;

public class ResponseUpdateSfarsitJoc extends ResponseUpdate {
    int jocId;
    UpdateSfarsitJoc updateSfarsitJoc;

    public ResponseUpdateSfarsitJoc(int jocId, UpdateSfarsitJoc updateSfarsitJoc) {
        this.jocId = jocId;
        this.updateSfarsitJoc = updateSfarsitJoc;
    }

    public int getJocId() {
        return jocId;
    }

    public UpdateSfarsitJoc getUpdateSfarsitJoc() {
        return updateSfarsitJoc;
    }
}
