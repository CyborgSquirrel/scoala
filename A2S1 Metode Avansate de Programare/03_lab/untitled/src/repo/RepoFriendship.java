package repo;

import domain.Friendship;
import domain.User;
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;

public class RepoFriendship implements Repo<Friendship, Friendship> {
    private HashSet<Friendship> friendships;

    public RepoFriendship() {
        this.friendships = new HashSet<>();
    }

    @Override
    public void store(Friendship friendship) throws ItemAlreadyExistsException {
        if (friendships.contains(friendship)) {
            throw new ItemAlreadyExistsException();
        }
        friendships.add(friendship);
    }

    @Override
    public void update(Friendship friendship) throws ItemDoesntExistException {
        if (!friendships.contains(friendship)) {
            throw new ItemDoesntExistException();
        }
        friendships.add(friendship);
    }

    @Override
    public void erase(Friendship friendship) throws ItemDoesntExistException {
        if (!friendships.contains(friendship)) {
            throw new ItemDoesntExistException();
        }
        friendships.remove(friendship);
    }

    @Override
    public Friendship find(Friendship friendship) throws ItemDoesntExistException {
        if (!friendships.contains(friendship)) {
            throw new ItemDoesntExistException();
        }
        return friendship;
    }

    @Override
    public Friendship[] getAll() {
        return this.friendships.toArray(new Friendship[0]);
    }
}
