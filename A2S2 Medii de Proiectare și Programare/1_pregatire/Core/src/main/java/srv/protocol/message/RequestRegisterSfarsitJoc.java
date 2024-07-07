package srv.protocol.message;

public class RequestRegisterSfarsitJoc extends Request {
    int jocId;

    public RequestRegisterSfarsitJoc(int jocId) {
        this.jocId = jocId;
    }

    public int getJocId() {
        return jocId;
    }
}
