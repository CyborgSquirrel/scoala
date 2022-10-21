package service;

import domain.Friendship;
import domain.User;
import repo.RepoFriendship;
import repo.RepoUser;
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;
import util.DisjointSet;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;

public class ServiceFriendship {
    private RepoUser repoUser;
    private RepoFriendship repoFriendship;

    public ServiceFriendship(RepoUser repoUser, RepoFriendship repoFriendship) {
        this.repoUser = repoUser;
        this.repoFriendship = repoFriendship;
    }

    public void addFriendship(int firstUserId, int secondUserId) throws ItemDoesntExistException, ItemAlreadyExistsException {
        this.repoUser.find(firstUserId);
        this.repoUser.find(secondUserId);
        Friendship friendship1 = new Friendship(firstUserId, secondUserId);
        Friendship friendship2 = new Friendship(secondUserId, firstUserId);
        this.repoFriendship.store(friendship1);
        this.repoFriendship.store(friendship2);
    }

    public void removeFriendship(int firstUserId, int secondUserId) throws ItemDoesntExistException {
        Friendship friendship1 = new Friendship(firstUserId, secondUserId);
        Friendship friendship2 = new Friendship(secondUserId, firstUserId);
        this.repoFriendship.erase(friendship1);
        this.repoFriendship.erase(friendship2);
    }

    public ArrayList<ArrayList<User>> getCommunities() {
        DisjointSet disjointSet = new DisjointSet();

        HashMap<Integer, User> idToUser = new HashMap<>();
        User[] users = this.repoUser.getAll();
        for (User user : users) {
            disjointSet.find(user.getId());
            idToUser.put(user.getId(), user);
        }

        Friendship[] friendships = this.repoFriendship.getAll();
        for (Friendship friendship : friendships) {
            disjointSet.union(friendship.getFirstUserId(), friendship.getSecondUserId());
        }

        Collection<ArrayList<Integer>> communitiesIds = disjointSet.getSets();
        ArrayList<ArrayList<User>> communities = new ArrayList<>();
        for (ArrayList<Integer> communityIds : communitiesIds) {
            ArrayList<User> community = new ArrayList<>();
            communities.add(community);
            for (int userId : communityIds) {
                community.add(idToUser.get(userId));
            }
        }

        return communities;
    }

    public int getCommunitiesCount() {
        return this.getCommunities().size();
    }

    public ArrayList<User> getMostSociableCommunity() {
        

        return new ArrayList<>();
    }
}
