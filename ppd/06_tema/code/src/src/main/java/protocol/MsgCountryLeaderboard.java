package protocol;

import java.io.Serializable;

public class MsgCountryLeaderboard implements Serializable {
    public MsgCountryEntry[] entries;

    public MsgCountryLeaderboard(MsgCountryEntry[] entries) {
        this.entries = entries;
    }
}
