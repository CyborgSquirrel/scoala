package domain;

import javax.persistence.Column;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import java.time.LocalDateTime;
import java.util.Objects;

public class Joc implements Entity<Integer> {
    int id;

    int jucatorId;
    LocalDateTime timestampInceput;
    LocalDateTime timestampSfarsit;
    DTOPozitie[] gropi;
    int punctaj;
    boolean finalizat;

    public Joc() {

    }

    public Joc(int jucatorId,
               LocalDateTime timestampInceput,
               LocalDateTime timestampSfarsit,
               DTOPozitie[] gropi,
               int punctaj,
               boolean finalizat) {
        this.jucatorId = jucatorId;
        this.timestampInceput = timestampInceput;
        this.timestampSfarsit = timestampSfarsit;
        this.gropi = gropi;
        this.punctaj = punctaj;
        this.finalizat = finalizat;
    }

    @Override
    public Integer getId() {
        return id;
    }

    @Override
    public void setId(Integer id) {
        this.id = id;
    }

    public int getJucatorId() {
        return jucatorId;
    }

    public void setJucatorId(int jucatorId) {
        this.jucatorId = jucatorId;
    }

    public LocalDateTime getTimestampInceput() {
        return timestampInceput;
    }

    public void setTimestampInceput(LocalDateTime timestampInceput) {
        this.timestampInceput = timestampInceput;
    }

    public LocalDateTime getTimestampSfarsit() {
        return timestampSfarsit;
    }

    public void setTimestampSfarsit(LocalDateTime timestampSfarsit) {
        this.timestampSfarsit = timestampSfarsit;
    }

    public DTOPozitie[] getGropi() {
        return gropi;
    }

    public void setGropi(DTOPozitie[] gropi) {
        this.gropi = gropi;
    }

    public int getPunctaj() {
        return punctaj;
    }

    public void setPunctaj(int punctaj) {
        this.punctaj = punctaj;
    }

    public boolean isFinalizat() {
        return finalizat;
    }

    public void setFinalizat(boolean finalizat) {
        this.finalizat = finalizat;
    }
}
