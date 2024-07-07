package domain;

import java.io.Serializable;
import java.util.Objects;

public class DTOPozitie implements Serializable {
    int linie;
    int coloana;

    public DTOPozitie() {

    }

    public DTOPozitie(int linie, int coloana) {
        this.linie = linie;
        this.coloana = coloana;
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

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        DTOPozitie that = (DTOPozitie) o;
        return linie == that.linie && coloana == that.coloana;
    }

    @Override
    public int hashCode() {
        return Objects.hash(linie, coloana);
    }
}
