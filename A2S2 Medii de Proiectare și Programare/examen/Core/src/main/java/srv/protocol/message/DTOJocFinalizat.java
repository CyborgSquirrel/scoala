package srv.protocol.message;

import domain.DTOPozitie;

import java.io.Serializable;

public class DTOJocFinalizat implements Serializable {
    DTOPozitie gropi[];
    DTOPozitie pozitiiPropuse[];
    int punctaj;
    int durataSecunde;

    public DTOJocFinalizat(DTOPozitie[] gropi, DTOPozitie[] pozitiiPropuse, int punctaj, int durataSecunde) {
        this.gropi = gropi;
        this.pozitiiPropuse = pozitiiPropuse;
        this.punctaj = punctaj;
        this.durataSecunde = durataSecunde;
    }

    public DTOPozitie[] getGropi() {
        return gropi;
    }

    public void setGropi(DTOPozitie[] gropi) {
        this.gropi = gropi;
    }

    public DTOPozitie[] getPozitiiPropuse() {
        return pozitiiPropuse;
    }

    public void setPozitiiPropuse(DTOPozitie[] pozitiiPropuse) {
        this.pozitiiPropuse = pozitiiPropuse;
    }

    public int getPunctaj() {
        return punctaj;
    }

    public void setPunctaj(int punctaj) {
        this.punctaj = punctaj;
    }

    public int getDurataSecunde() {
        return durataSecunde;
    }

    public void setDurataSecunde(int durataSecunde) {
        this.durataSecunde = durataSecunde;
    }
}
