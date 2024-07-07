package domain;

import java.util.Objects;
import java.util.UUID;

public class FriendshipId {
    private UUID firstUserId;
    private UUID secondUserId;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        FriendshipId that = (FriendshipId) o;
        return Objects.equals(firstUserId, that.firstUserId) && Objects.equals(secondUserId, that.secondUserId);
    }

    @Override
    public int hashCode() {
        return Objects.hash(firstUserId, secondUserId);
    }

    public FriendshipId(UUID firstUserId, UUID secondUserId) {
        this.firstUserId = firstUserId;
        this.secondUserId = secondUserId;
    }

    public UUID getFirstUserId() {
        return firstUserId;
    }

    public UUID getSecondUserId() {
        return secondUserId;
    }
}
