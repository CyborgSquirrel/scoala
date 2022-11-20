package repo;

import domain.Friendship;
import domain.FriendshipId;
import domain.User;
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;

import java.util.*;



public class RepoFriendship implements Repo<Friendship, FriendshipId> {
    protected HashMap<FriendshipId, Friendship> friendships;

    public RepoFriendship() {
        this.friendships = new HashMap<>();
    }

    @Override
    public void store(Friendship friendship) throws ItemAlreadyExistsException {
        if (friendships.containsKey(friendship.getId())) {
            throw new ItemAlreadyExistsException();
        }
        friendships.put(friendship.getId(), friendship);
    }

    @Override
    public void update(Friendship friendship) throws ItemDoesntExistException {
        if (!friendships.containsKey(friendship.getId())) {
            throw new ItemDoesntExistException();
        }
        friendships.put(friendship.getId(), friendship);
    }

    @Override
    public void erase(FriendshipId friendshipId) throws ItemDoesntExistException {
        if (!friendships.containsKey(friendshipId)) {
            throw new ItemDoesntExistException();
        }
        friendships.remove(friendshipId);
    }

    @Override
    public Friendship find(FriendshipId friendshipId) throws ItemDoesntExistException {
        if (!friendships.containsKey(friendshipId)) {
            throw new ItemDoesntExistException();
        }
        return friendships.get(friendshipId);
    }

    @Override
    public Friendship[] getAll() {
        return this.friendships.values().toArray(new Friendship[0]);
    }
}
