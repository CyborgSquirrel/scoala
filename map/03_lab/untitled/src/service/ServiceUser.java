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
    public ServiceUser(RepoUser repoUser, RepoFriendship repoFriendship) {
        this.repoUser = repoUser;
        this.repoFriendship = repoFriendship;
    }

    public void addUser(int id, String name) throws ItemAlreadyExistsException {
        User user = new User(id, name);
        this.repoUser.store(user);
    }

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
