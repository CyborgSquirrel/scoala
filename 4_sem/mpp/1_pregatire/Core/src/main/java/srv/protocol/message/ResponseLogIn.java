package srv.protocol.message;

import domain.Jucator;

public class ResponseLogIn extends Response {
    Jucator jucator;

    public ResponseLogIn(Jucator jucator) {
        this.jucator = jucator;
    }

    public Jucator getJucator() {
        return jucator;
    }
}
