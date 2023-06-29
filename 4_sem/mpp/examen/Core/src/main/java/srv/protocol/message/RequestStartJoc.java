package srv.protocol.message;

public class RequestStartJoc extends Request {
    String alias;

    public RequestStartJoc(String alias) {
        this.alias = alias;
    }

    public String getAlias() {
        return alias;
    }

    public void setAlias(String alias) {
        this.alias = alias;
    }
}
