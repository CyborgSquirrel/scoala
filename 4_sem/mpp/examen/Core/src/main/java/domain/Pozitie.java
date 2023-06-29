package domain;

import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@javax.persistence.Entity
@javax.persistence.Table(name = "Pozitie")
public class Pozitie implements Entity<Integer> {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    int id;
    int jocId;
    int linie;
    int coloana;

    public Pozitie() {

    }

    public Pozitie(int jocId, int linie, int coloana) {
        this.jocId = jocId;
        this.linie = linie;
        this.coloana = coloana;
    }

    @Override
    public Integer getId() {
        return id;
    }

    @Override
    public void setId(Integer id) {
        this.id = id;
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

    public DTOPozitie makeDtoPozitie() {
        return new DTOPozitie(linie, coloana);
    }
}
