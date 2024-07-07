package srv.protocol.message;

public class ResponseUpdateStartJoc extends ResponseUpdate {
    int jocId;
    UpdateStartJoc updateStartJoc;

    public ResponseUpdateStartJoc(int jocId, UpdateStartJoc updateStartJoc) {
        this.jocId = jocId;
        this.updateStartJoc = updateStartJoc;
    }

    public int getJocId() {
        return jocId;
    }

    public UpdateStartJoc getUpdateStartJoc() {
        return updateStartJoc;
    }
}
