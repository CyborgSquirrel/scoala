package service;

import domain.Friendship;
import domain.User;
import repo.RepoFriendship;
import repo.RepoUser;
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;
import service.exception.DependencyDetectedException;

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
     * @param id the user's id
     * @param name the user's name
     * @throws ItemAlreadyExistsException if a user with the provided id already exists
     */
    public void addUser(int id, String name) throws ItemAlreadyExistsException {
        User user = new User(id, name);
        this.repoUser.store(user);
    }

    /**
     * Removes the user with the provided id.
     * @param id the id of the user that will be removed
     * @throws ItemDoesntExistException if a user with provided id doesn't exist
     * @throws DependencyDetectedException if the user to-be-deleted has friendships
     */
    public void removeUser(int id) throws ItemDoesntExistException, DependencyDetectedException {
        Friendship friendships[] = repoFriendship.getAll();
        for (Friendship friendship : friendships) {
            if (friendship.getFirstUserId() == id || friendship.getSecondUserId() == id) {
                throw new DependencyDetectedException();
            }
        }
        this.repoUser.erase(id);
    }
}
