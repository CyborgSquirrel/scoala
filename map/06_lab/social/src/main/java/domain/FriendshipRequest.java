package domain;

public class FriendshipRequest {
    public FriendshipRequestId getId() {
        return id;
    }

    public FriendshipRequest(FriendshipRequestId id) {
        this.id = id;
    }

    private FriendshipRequestId id;
}
