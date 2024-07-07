package domain;

import javax.persistence.Column;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import java.time.LocalDateTime;
import java.util.Objects;

@javax.persistence.Entity
@javax.persistence.Table(name = "Joc")
public class Joc implements Entity<Integer> {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    int id;

    int jucatorId;
    int configuratieId;
    int incercari;
    LocalDateTime timestampInceput;
    boolean finalizat;
    boolean ghicit;

    public Joc() {

    }

    public Joc(int jucatorId,
               int configuratieId,
               int incercari,
               LocalDateTime timestampInceput,
               boolean finalizat,
               boolean ghicit) {
        this.jucatorId = jucatorId;
        this.configuratieId = configuratieId;
        this.incercari = incercari;
        this.timestampInceput = timestampInceput;
        this.finalizat = false;
        this.ghicit = false;
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

    public int getConfiguratieId() {
        return configuratieId;
    }

    public void setConfiguratieId(int configuratieId) {
        this.configuratieId = configuratieId;
    }

    public int getIncercari() {
        return incercari;
    }

    public void setIncercari(int incercari) {
        this.incercari = incercari;
    }

    public LocalDateTime getTimestampInceput() {
        return timestampInceput;
    }

    public void setTimestampInceput(LocalDateTime timestampInceput) {
        this.timestampInceput = timestampInceput;
    }

    public boolean isFinalizat() {
        return finalizat;
    }

    public void setFinalizat(boolean finalizat) {
        this.finalizat = finalizat;
    }

    public boolean isGhicit() {
        return ghicit;
    }

    public void setGhicit(boolean ghicit) {
        this.ghicit = ghicit;
    }
}
