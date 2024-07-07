package srv.protocol.message;

public class RequestLogIn extends Request {
    String nume;
    String parola;

    public RequestLogIn(String nume, String parola) {
        this.nume = nume;
        this.parola = parola;
    }

    public String getNume() {
        return nume;
    }

    public String getParola() {
        return parola;
    }
}
