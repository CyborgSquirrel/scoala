package srv.protocol.message;

import java.io.Serializable;
import java.time.LocalDateTime;

public class DTOClasamentItem implements Serializable {
    String aliasJucator;
    LocalDateTime timestampInceput;
    int incercari;
    String indiciu;

    public DTOClasamentItem(String aliasJucator, LocalDateTime timestampInceput, int incercari, String indiciu) {
        this.aliasJucator = aliasJucator;
        this.timestampInceput = timestampInceput;
        this.incercari = incercari;
        this.indiciu = indiciu;
    }

    public String getAliasJucator() {
        return aliasJucator;
    }

    public void setAliasJucator(String aliasJucator) {
        this.aliasJucator = aliasJucator;
    }

    public LocalDateTime getTimestampInceput() {
        return timestampInceput;
    }

    public void setTimestampInceput(LocalDateTime timestampInceput) {
        this.timestampInceput = timestampInceput;
    }

    public int getIncercari() {
        return incercari;
    }

    public void setIncercari(int incercari) {
        this.incercari = incercari;
    }

    public String getIndiciu() {
        return indiciu;
    }

    public void setIndiciu(String indiciu) {
        this.indiciu = indiciu;
    }
}
