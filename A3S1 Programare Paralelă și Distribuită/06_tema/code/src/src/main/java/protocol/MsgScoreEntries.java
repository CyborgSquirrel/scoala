package protocol;

import java.io.Serializable;
import java.util.Arrays;

public class MsgScoreEntries implements Serializable {
    public MsgScoreEntry[] msgScoreEntries;

    public MsgScoreEntries(MsgScoreEntry[] msgScoreEntries) {
        this.msgScoreEntries = msgScoreEntries;
    }

    @Override
    public String toString() {
        return "MsgScoreEntries{" +
                "msgScoreEntries=" + Arrays.toString(msgScoreEntries) +
                '}';
    }
}
