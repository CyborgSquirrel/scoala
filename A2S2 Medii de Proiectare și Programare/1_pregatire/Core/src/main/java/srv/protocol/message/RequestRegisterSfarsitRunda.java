package srv.protocol.message;

public class RequestRegisterSfarsitRunda extends Request {
    int jocId;

    public RequestRegisterSfarsitRunda(int jocId) {
        this.jocId = jocId;
    }

    public int getJocId() {
        return jocId;
    }
}
