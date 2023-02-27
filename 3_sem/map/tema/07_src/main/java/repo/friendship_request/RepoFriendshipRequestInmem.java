package repo.friendship_request;

import domain.FriendshipRequest;
import domain.FriendshipRequestId;
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;

import java.util.HashMap;

public class RepoFriendshipRequestInmem extends RepoFriendshipRequest {
    protected HashMap<FriendshipRequestId, FriendshipRequest> friendshipRequests;

    public RepoFriendshipRequestInmem() {
        this.friendshipRequests = new HashMap<>();
    }

    @Override
    public void store(FriendshipRequest friendshipRequest) throws ItemAlreadyExistsException {
        if (friendshipRequests.containsKey(friendshipRequest.getId())) {
            throw new ItemAlreadyExistsException();
        }
        friendshipRequests.put(friendshipRequest.getId(), friendshipRequest);
    }

    @Override
    public void update(FriendshipRequest friendshipRequest) throws ItemDoesntExistException {
        if (!friendshipRequests.containsKey(friendshipRequest.getId())) {
            throw new ItemDoesntExistException();
        }
        friendshipRequests.put(friendshipRequest.getId(), friendshipRequest);
    }

    @Override
    public void erase(FriendshipRequestId id) throws ItemDoesntExistException {
        if (!friendshipRequests.containsKey(id)) {
            throw new ItemDoesntExistException();
        }
        friendshipRequests.remove(id);
    }

    @Override
    public FriendshipRequest find(FriendshipRequestId id) throws ItemDoesntExistException {
        if (!friendshipRequests.containsKey(id)) {
            throw new ItemDoesntExistException();
        }
        return friendshipRequests.get(id);
    }

    @Override
    public FriendshipRequest[] getAll() {
        return this.friendshipRequests.values().toArray(new FriendshipRequest[0]);
    }
}
