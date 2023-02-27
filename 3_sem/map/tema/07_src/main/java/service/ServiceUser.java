package service;

import domain.Friendship;
import domain.User;
import repo.friendship.RepoFriendship;
import repo.user.RepoUser;
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;
import service.exception.DependencyDetectedException;

import java.util.ArrayList;
import java.util.UUID;

public class ServiceUser {
    private RepoUser repoUser;
    private RepoFriendship repoFriendship;

    /**
     * Creates a new user service.
     * @param repoUser user repo
     * @param repoFriendship friendship repo
     */
    public ServiceUser(RepoUser repoUser, RepoFriendship repoFriendship) {
        this.repoUser = repoUser;
        this.repoFriendship = repoFriendship;
    }

    /**
     * Adds a new user.
     * @param name the user's name
     * @throws ItemAlreadyExistsException if a user with the provided id already exists
     */
    public void addUser(String name) throws ItemAlreadyExistsException {
        User user = new User(UUID.randomUUID(), name);
        this.repoUser.store(user);
    }

    /**
     * Removes the user with the provided id.
     * @param id the id of the user that will be removed
     * @throws ItemDoesntExistException if a user with provided id doesn't exist
     * @throws DependencyDetectedException if the user to-be-deleted has friendships
     */
    public void removeUser(UUID id) throws ItemDoesntExistException, DependencyDetectedException {
        Friendship friendships[] = repoFriendship.getAll();
        for (Friendship friendship : friendships) {
            if (friendship.getId().getFirstUserId().equals(id) || friendship.getId().getSecondUserId().equals(id)) {
                throw new DependencyDetectedException();
            }
        }
        this.repoUser.erase(id);
    }

    /**
     * @return all the users
     */
    public User[] getUsers() {
        return repoUser.getAll();
    }

    /**
     * @param name the name with which to filter
     * @return the list of users which have a similar name to the provided name
     */
    public ArrayList<User> findUsersByName(String name) {
        ArrayList<User> filteredUsers = new ArrayList<>();
        User[] users = repoUser.getAll();
        for (User user : users) {
            if (user.getName().contains(name)) {
                filteredUsers.add(user);
            }
        }
        return filteredUsers;
    }

    /**
     * @param id the id of the user
     * @return the user with the provided id
     * @throws ItemDoesntExistException if the user isn't found
     */
    public User findById(UUID id) throws ItemDoesntExistException {
        return repoUser.find(id);
    }

    public User findByName(String name) throws ItemDoesntExistException {
        User[] users = repoUser.getAll();
        for (User user : users) {
            if (user.getName().equals(name)) {
                return user;
            }
        }
        throw new ItemDoesntExistException();
    }
}
