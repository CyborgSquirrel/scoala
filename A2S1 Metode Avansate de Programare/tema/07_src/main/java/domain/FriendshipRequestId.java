package domain;

import java.util.Objects;
import java.util.UUID;

public class FriendshipRequestId {
    private UUID sourceUserId;
    private UUID destinationUserId;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        FriendshipRequestId that = (FriendshipRequestId) o;
        return Objects.equals(sourceUserId, that.sourceUserId) && Objects.equals(destinationUserId, that.destinationUserId);
    }

    @Override
    public int hashCode() {
        return Objects.hash(sourceUserId, destinationUserId);
    }

    public FriendshipRequestId(UUID sourceUserId, UUID destinationUserId) {
        this.sourceUserId = sourceUserId;
        this.destinationUserId = destinationUserId;
    }

    public UUID getSourceUserId() {
        return sourceUserId;
    }

    public UUID getDestinationUserId() {
        return destinationUserId;
    }
}
