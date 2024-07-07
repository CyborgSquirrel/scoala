package protocol;

import java.io.Serializable;

public class MsgCountryEntry implements Serializable {
    public int countryId;
    public int score;

    public MsgCountryEntry(int countryId, int score) {
        this.countryId = countryId;
        this.score = score;
    }
}
