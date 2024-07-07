package srv.protocol.message;

import domain.Jucator;

public class ResponseStartJoc {
    Jucator jucator;
    int jocId;

    public ResponseStartJoc(Jucator jucator, int jocId) {
        this.jucator = jucator;
        this.jocId = jocId;
    }

    public Jucator getJucator() {
        return jucator;
    }

    public void setJucator(Jucator jucator) {
        this.jucator = jucator;
    }

    public int getJocId() {
        return jocId;
    }

    public void setJocId(int jocId) {
        this.jocId = jocId;
    }
}
