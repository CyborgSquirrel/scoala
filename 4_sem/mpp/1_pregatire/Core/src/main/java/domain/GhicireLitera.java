package domain;

import javax.persistence.EmbeddedId;
import javax.persistence.Table;

@javax.persistence.Entity
@Table(name = "GhicireLitera")
public class GhicireLitera implements Entity<GhicireLiteraId> {
    @EmbeddedId
    GhicireLiteraId id;
    int propunatorJucatorId;
    char litera;
    int punctaj;

    public GhicireLitera() {

    }

    public GhicireLitera(GhicireLiteraId id, int propunatorJucatorId, char litera, int punctaj) {
        this.id = id;
        this.propunatorJucatorId = propunatorJucatorId;
        this.litera = litera;
        this.punctaj = punctaj;
    }

    @Override
    public GhicireLiteraId getId() {
        return id;
    }

    @Override
    public void setId(GhicireLiteraId id) {
        this.id = id;
    }

    public int getPropunatorJucatorId() {
        return propunatorJucatorId;
    }

    public void setPropunatorJucatorId(int propunatorJucatorId) {
        this.propunatorJucatorId = propunatorJucatorId;
    }

    public char getLitera() {
        return litera;
    }

    public void setLitera(char litera) {
        this.litera = litera;
    }

    public int getPunctaj() {
        return punctaj;
    }

    public void setPunctaj(int punctaj) {
        this.punctaj = punctaj;
    }
}
