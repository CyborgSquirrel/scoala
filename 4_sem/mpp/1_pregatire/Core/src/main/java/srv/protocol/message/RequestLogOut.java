package srv.protocol.message;

public class RequestLogOut extends Request {
    int jucatorId;

    public RequestLogOut(int jucatorId) {
        this.jucatorId = jucatorId;
    }

    public int getJucatorId() {
        return jucatorId;
    }
}
