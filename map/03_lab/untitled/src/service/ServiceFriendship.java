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
import java.util.HashSet;

public class ServiceFriendship {
    private RepoUser repoUser;
    private RepoFriendship repoFriendship;

    /**
     * Creates a new friendship service.
     * @param repoUser user repo
     * @param repoFriendship friendship repo
     */
    public ServiceFriendship(RepoUser repoUser, RepoFriendship repoFriendship) {
        this.repoUser = repoUser;
        this.repoFriendship = repoFriendship;
    }

    /**
     * Adds a friendship between the provided users' ids to the repo.
     * @param firstUserId the first user id
     * @param secondUserId the second user id
     */
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

    /**
     * Returns a {@link DisjointSet} of all the communities.
     * @return a {@link DisjointSet} of all the communities
     */
    private DisjointSet getCommunitiesDisjointSet() {
        DisjointSet disjointSet = new DisjointSet();

        User[] users = this.repoUser.getAll();
        for (User user : users) {
            disjointSet.find(user.getId());
        }

        Friendship[] friendships = this.repoFriendship.getAll();
        for (Friendship friendship : friendships) {
            disjointSet.union(friendship.getFirstUserId(), friendship.getSecondUserId());
        }

        return disjointSet;
    }

    /**
     * Returns a list of all the communities.
     * @return a list of all the communities
     */
    public ArrayList<ArrayList<User>> getCommunities() {
        HashMap<Integer, User> idToUser = new HashMap<>();
        User[] users = this.repoUser.getAll();
        for (User user : users) {
            idToUser.put(user.getId(), user);
        }

        DisjointSet disjointSet = getCommunitiesDisjointSet();
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

    /**
     * Returns the number of communities.
     * @return the number of communities
     */
    public int getCommunitiesCount() {
        return this.getCommunities().size();
    }

    public ArrayList<User> getMostSociableCommunity() {
        User[] users = this.repoUser.getAll();
        Friendship[] friendships = this.repoFriendship.getAll();

        HashMap<Integer, ArrayList<Integer>> userFriendIds = new HashMap<>();
        for (Friendship friendship : friendships) {
            if (!userFriendIds.containsKey(friendship.getFirstUserId())) {
                userFriendIds.put(friendship.getFirstUserId(), new ArrayList<>());
            }
            ArrayList<Integer> firstFriendIds = userFriendIds.get(friendship.getFirstUserId());
            firstFriendIds.add(friendship.getSecondUserId());
            
            if (!userFriendIds.containsKey(friendship.getSecondUserId())) {
                userFriendIds.put(friendship.getSecondUserId(), new ArrayList<>());
            }
            ArrayList<Integer> secondFriendIds = userFriendIds.get(friendship.getSecondUserId());
            secondFriendIds.add(friendship.getFirstUserId());
        }

        int max = 0;
        int maxUserId = -1;
        for (User user : users) {
            HashSet<Integer> currentUserIds = new HashSet<>();
            int length = getLongestPathLength(
                    user.getId(),
                    currentUserIds,
                    userFriendIds
            );
            if (length > max) {
                max = length;
                maxUserId = user.getId();
            }
        }

        ArrayList<User> community = new ArrayList<>();
        if (max > 0) {
            HashMap<Integer, User> usersById = new HashMap<>();
            for (User user : users) {
                usersById.put(user.getId(), user);
            }

            DisjointSet disjointSet = getCommunitiesDisjointSet();
            HashMap<Integer, ArrayList<Integer>> communitiesIds = disjointSet.getSetsWithCanonicalElement();
            ArrayList<Integer> communityIds = communitiesIds.get(disjointSet.find(maxUserId));
            for (int communityId : communityIds) {
                community.add(usersById.get(communityId));
            }
        }

        return community;
    }

    private int getLongestPathLength(
            int currentUserId,
            HashSet<Integer> currentUserIds,
            HashMap<Integer, ArrayList<Integer>> userFriendIds
    ) {
        int max = 0;
        if (userFriendIds.containsKey(currentUserId)) {
            for (int otherUserId : userFriendIds.get(currentUserId)) {
                if (!currentUserIds.contains(otherUserId)) {
                    currentUserIds.add(otherUserId);
                    int length = getLongestPathLength(otherUserId, currentUserIds, userFriendIds);
                    currentUserIds.remove(otherUserId);

                    max = Math.max(max, length);
                }
            }
        }
        return max+1;
    }
}
