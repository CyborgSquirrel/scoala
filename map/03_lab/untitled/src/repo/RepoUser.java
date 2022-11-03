package repo;

import domain.User;
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;

import java.util.HashMap;
import java.util.UUID;

public class RepoUser implements Repo<User, UUID> {
    private HashMap<UUID, User> users;

    public RepoUser() {
        this.users = new HashMap<>();
    }

    @Override
    public void store(User user) throws ItemAlreadyExistsException {
        if (users.containsKey(user.getId())) {
            throw new ItemAlreadyExistsException();
        }
        users.put(user.getId(), user);
    }

    @Override
    public void update(User user) throws ItemDoesntExistException {
        if (!users.containsKey(user.getId())) {
            throw new ItemDoesntExistException();
        }
        users.put(user.getId(), user);
    }

    @Override
    public void erase(UUID id) throws ItemDoesntExistException {
        if (!users.containsKey(id)) {
            throw new ItemDoesntExistException();
        }
        users.remove(id);
    }

    @Override
    public User find(UUID id) throws ItemDoesntExistException {
        if (!users.containsKey(id)) {
            throw new ItemDoesntExistException();
        }
        return users.get(id);
    }

    @Override
    public User[] getAll() {
        return users.values().toArray(new User[0]);
    }
}
