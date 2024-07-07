package srv.protocol.message;

import java.io.Serializable;
import java.time.LocalDateTime;

public class DTOClasamentItem implements Serializable {
    String aliasJucator;
    int puncte;
    int durataSecunde;
    int jocId;

    public DTOClasamentItem(String aliasJucator, int puncte, int durataSecunde, int jocId) {
        this.aliasJucator = aliasJucator;
        this.puncte = puncte;
        this.durataSecunde = durataSecunde;
        this.jocId = jocId;
    }

    public String getAliasJucator() {
        return aliasJucator;
    }

    public void setAliasJucator(String aliasJucator) {
        this.aliasJucator = aliasJucator;
    }

    public int getPuncte() {
        return puncte;
    }

    public void setPuncte(int puncte) {
        this.puncte = puncte;
    }

    public int getDurataSecunde() {
        return durataSecunde;
    }

    public void setDurataSecunde(int durataSecunde) {
        this.durataSecunde = durataSecunde;
    }

    public int getJocId() {
        return jocId;
    }

    public void setJocId(int jocId) {
        this.jocId = jocId;
    }
}
