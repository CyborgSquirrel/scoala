package domain;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class FriendshipRequest {
    public static final DateTimeFormatter DATE_TIME_FORMATTER = DateTimeFormatter.ISO_LOCAL_DATE;
    private LocalDateTime createdTime;

    public FriendshipRequestId getId() {
        return id;
    }

    public FriendshipRequest(FriendshipRequestId id, LocalDateTime createdTime) {
        this.id = id;
        this.createdTime = createdTime;
    }

    private FriendshipRequestId id;

    public LocalDateTime getCreatedTime() {
        return createdTime;
    }
}
