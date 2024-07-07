package srv.protocol.message;

import java.io.Serializable;

public class DTOStartJocJucator implements Serializable {
    int id;
    int cuvantLungime;
    String nume;

    public DTOStartJocJucator(int id, int cuvantLungime, String nume) {
        this.id = id;
        this.cuvantLungime = cuvantLungime;
        this.nume = nume;
    }

    public int getId() {
        return id;
    }

    public int getCuvantLungime() {
        return cuvantLungime;
    }

    public String getNume() {
        return nume;
    }
}
