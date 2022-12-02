package domain;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Friendship {
    public static final DateTimeFormatter DATE_TIME_FORMATTER = DateTimeFormatter.ISO_LOCAL_DATE;

    private FriendshipId id;
    private LocalDateTime friendsSince;

    public LocalDateTime getFriendsSince() {
        return friendsSince;
    }

    /**
     * Creates a new {@link Friendship}.
     * @param firstUserId the id of the first user taking part in the friendship
     * @param secondUserId the id of the second user taking part in the friendship
     * @param friendsSince the time from whence firstUser and secondUser are friends
     */
    public Friendship(FriendshipId id, LocalDateTime friendsSince) {
        this.id = id;
        this.friendsSince = friendsSince;
    }

    public FriendshipId getId() {
        return id;
    }
}
