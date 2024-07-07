package protocol;

import java.io.Serializable;

public class MsgScoreEntry implements Serializable {
  public int id;
  public int score;
  public int countryId;

  public MsgScoreEntry(int id, int score, int countryId) {
    this.id = id;
    this.score = score;
    this.countryId = countryId;
  }

  @Override
  public String toString() {
    return "MsgScoreEntry{" +
            "id=" + id +
            ", score=" + score +
            ", countryId=" + countryId +
            '}';
  }
}
