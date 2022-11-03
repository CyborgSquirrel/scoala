package service;

import domain.Friendship;
import domain.User;
import repo.RepoFriendship;
import repo.RepoUser;
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;
import util.DisjointSet;

import java.util.*;

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
    public void addFriendship(UUID firstUserId, UUID secondUserId) throws ItemDoesntExistException, ItemAlreadyExistsException {
        this.repoUser.find(firstUserId);
        this.repoUser.find(secondUserId);
        Friendship friendship1 = new Friendship(firstUserId, secondUserId);
        Friendship friendship2 = new Friendship(secondUserId, firstUserId);
        this.repoFriendship.store(friendship1);
        this.repoFriendship.store(friendship2);
    }

    /**
     * @param firstUserId the id of the first user
     * @param secondUserId the id of the second user
     * @throws ItemDoesntExistException if a friendship between firstUserId and secondUserId doesn't exist
     */
    public void removeFriendship(UUID firstUserId, UUID secondUserId) throws ItemDoesntExistException {
        Friendship friendship1 = new Friendship(firstUserId, secondUserId);
        Friendship friendship2 = new Friendship(secondUserId, firstUserId);
        this.repoFriendship.erase(friendship1);
        this.repoFriendship.erase(friendship2);
    }

    /**
     * @return list of all friendships
     */
    public Friendship[] getFriendships() {
        return repoFriendship.getAll();
    }

    /**
     * Returns a {@link DisjointSet} of all the communities.
     * @return a {@link DisjointSet} of all the communities
     */
    private DisjointSet<UUID> getCommunitiesDisjointSet() {
        DisjointSet<UUID> disjointSet = new DisjointSet<>();

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
        HashMap<UUID, User> idToUser = new HashMap<>();
        User[] users = this.repoUser.getAll();
        for (User user : users) {
            idToUser.put(user.getId(), user);
        }

        DisjointSet disjointSet = getCommunitiesDisjointSet();
        Collection<ArrayList<UUID>> communitiesIds = disjointSet.getSets();
        ArrayList<ArrayList<User>> communities = new ArrayList<>();
        for (ArrayList<UUID> communityIds : communitiesIds) {
            ArrayList<User> community = new ArrayList<>();
            communities.add(community);
            for (UUID userId : communityIds) {
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

    /**
     * @return the most sociable community
     */
    public ArrayList<User> getMostSociableCommunity() {
        User[] users = this.repoUser.getAll();
        Friendship[] friendships = this.repoFriendship.getAll();

        HashMap<UUID, ArrayList<UUID>> userFriendIds = new HashMap<>();
        for (Friendship friendship : friendships) {
            if (!userFriendIds.containsKey(friendship.getFirstUserId())) {
                userFriendIds.put(friendship.getFirstUserId(), new ArrayList<>());
            }
            ArrayList<UUID> firstFriendIds = userFriendIds.get(friendship.getFirstUserId());
            firstFriendIds.add(friendship.getSecondUserId());
            
            if (!userFriendIds.containsKey(friendship.getSecondUserId())) {
                userFriendIds.put(friendship.getSecondUserId(), new ArrayList<>());
            }
            ArrayList<UUID> secondFriendIds = userFriendIds.get(friendship.getSecondUserId());
            secondFriendIds.add(friendship.getFirstUserId());
        }

        ArrayList<UUID> longestPath = new ArrayList<>();
        for (User user : users) {
            HashSet<UUID> currentUserIds = new HashSet<>();
            ArrayList<UUID> currentLongestPath = getLongestPath(
                    user.getId(),
                    currentUserIds,
                    userFriendIds
            );
            if (currentLongestPath.size() > longestPath.size()) {
                longestPath = currentLongestPath;
            }
        }

        ArrayList<User> community = new ArrayList<>();
        if (!longestPath.isEmpty()) {
            HashMap<UUID, User> usersById = new HashMap<>();
            for (User user : users) {
                usersById.put(user.getId(), user);
            }

            for (UUID id : longestPath) {
                community.add(usersById.get(id));
            }
        }

        return community;
    }

    private ArrayList<UUID> getLongestPath(
            UUID currentUserId,
            HashSet<UUID> currentUserIds,
            HashMap<UUID, ArrayList<UUID>> userFriendIds
    ) {
        currentUserIds.add(currentUserId);

        ArrayList<UUID> longestPath = new ArrayList<>();
        if (userFriendIds.containsKey(currentUserId)) {
            for (UUID otherUserId : userFriendIds.get(currentUserId)) {
                if (!currentUserIds.contains(otherUserId)) {
                    ArrayList<UUID> potentialLongestPath = getLongestPath(otherUserId, currentUserIds, userFriendIds);

                    if (potentialLongestPath.size() > longestPath.size()) {
                        longestPath = potentialLongestPath;
                    }
                }
            }
        }
        longestPath = new ArrayList<>(longestPath);
        longestPath.add(currentUserId);
        currentUserIds.remove(currentUserId);
        return longestPath;
    }
}
