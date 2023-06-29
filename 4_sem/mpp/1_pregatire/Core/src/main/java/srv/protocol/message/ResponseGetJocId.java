package srv.protocol.message;

public class ResponseGetJocId extends Response {
    int jocId;

    public ResponseGetJocId(int jocId) {
        this.jocId = jocId;
    }

    public int getJocId() {
        return jocId;
    }
}
