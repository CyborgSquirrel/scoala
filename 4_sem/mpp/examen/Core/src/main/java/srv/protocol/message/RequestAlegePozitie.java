package srv.protocol.message;

public class RequestAlegePozitie extends Request {
    int jocId;
    int linie;
    int coloana;

    public RequestAlegePozitie(int jocId, int linie, int coloana) {
        this.jocId = jocId;
        this.linie = linie;
        this.coloana = coloana;
    }

    public int getJocId() {
        return jocId;
    }

    public void setJocId(int jocId) {
        this.jocId = jocId;
    }

    public int getLinie() {
        return linie;
    }

    public void setLinie(int linie) {
        this.linie = linie;
    }

    public int getColoana() {
        return coloana;
    }

    public void setColoana(int coloana) {
        this.coloana = coloana;
    }
}
