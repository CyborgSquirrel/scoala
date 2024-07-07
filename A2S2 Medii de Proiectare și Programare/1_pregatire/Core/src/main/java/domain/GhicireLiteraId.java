package domain;

import javax.persistence.Embeddable;
import java.io.Serializable;

@Embeddable
public class GhicireLiteraId implements Serializable {
    int jocId;
    int runda;
    int ghicitorJucatorId;

    public GhicireLiteraId() {

    }

    public GhicireLiteraId(int jocId, int runda, int ghicitorJucatorId) {
        this.jocId = jocId;
        this.runda = runda;
        this.ghicitorJucatorId = ghicitorJucatorId;
    }

    public int getJocId() {
        return jocId;
    }

    public void setJocId(int jocId) {
        this.jocId = jocId;
    }

    public int getRunda() {
        return runda;
    }

    public void setRunda(int runda) {
        this.runda = runda;
    }

    public int getGhicitorJucatorId() {
        return ghicitorJucatorId;
    }

    public void setGhicitorJucatorId(int ghicitorJucatorId) {
        this.ghicitorJucatorId = ghicitorJucatorId;
    }
}
