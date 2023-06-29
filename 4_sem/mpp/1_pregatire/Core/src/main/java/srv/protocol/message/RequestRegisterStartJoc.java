package srv.protocol.message;

public class RequestRegisterStartJoc extends Request {
    int jocId;

    public RequestRegisterStartJoc(int jocId) {
        this.jocId = jocId;
    }

    public int getJocId() {
        return jocId;
    }
}
