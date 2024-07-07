package srv.protocol.message;

import domain.DTOPozitie;

import java.io.Serializable;

public class DTOSfarsitJoc implements Serializable {
    int punctaj;
    DTOPozitie[] gropi;
    int pozitieClasament;

    public DTOSfarsitJoc(int punctaj, DTOPozitie[] gropi, int pozitieClasament) {
        this.punctaj = punctaj;
        this.gropi = gropi;
        this.pozitieClasament = pozitieClasament;
    }

    public int getPunctaj() {
        return punctaj;
    }

    public void setPunctaj(int punctaj) {
        this.punctaj = punctaj;
    }

    public DTOPozitie[] getGropi() {
        return gropi;
    }

    public void setGropi(DTOPozitie[] gropi) {
        this.gropi = gropi;
    }

    public int getPozitieClasament() {
        return pozitieClasament;
    }

    public void setPozitieClasament(int pozitieClasament) {
        this.pozitieClasament = pozitieClasament;
    }
}
