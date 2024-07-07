package protocol;

import java.io.Serializable;

public class MsgFinalStatus implements Serializable {
    byte[] countryLeaderboard;
    byte[] competitorLeaderboard;

    public MsgFinalStatus(byte[] countryLeaderboard, byte[] competitorLeaderboard) {
        this.countryLeaderboard = countryLeaderboard;
        this.competitorLeaderboard = competitorLeaderboard;
    }
}
