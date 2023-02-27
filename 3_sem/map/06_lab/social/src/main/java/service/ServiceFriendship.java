package service;

import domain.*;
import repo.friendship.RepoFriendship;
import repo.friendship_request.RepoFriendshipRequest;
import repo.user.RepoUser;
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;
import util.DisjointSet;

import java.time.LocalDateTime;
import java.util.*;

public class ServiceFriendship {
    private RepoUser repoUser;
    private RepoFriendship repoFriendship;
    private RepoFriendshipRequest repoFriendshipRequest;

    /**
     * Creates a new friendship service.
     * @param repoUser user repo
     * @param repoFriendship friendship repo
     */
    public ServiceFriendship(RepoUser repoUser, RepoFriendship repoFriendship, RepoFriendshipRequest repoFriendshipRequest) {
        this.repoUser = repoUser;
        this.repoFriendship = repoFriendship;
        this.repoFriendshipRequest = repoFriendshipRequest;
    }

    /**
     * Adds a friendship between the provided users' ids to the repo.
     * @param firstUserId the first user id
     * @param secondUserId the second user id
     */
    public void addFriendship(UUID firstUserId, UUID secondUserId) throws ItemDoesntExistException, ItemAlreadyExistsException {
        this.repoUser.find(firstUserId);
        this.repoUser.find(secondUserId);
        LocalDateTime now = LocalDateTime.now();
        Friendship friendship1 = new Friendship(new FriendshipId(firstUserId, secondUserId), now);
        Friendship friendship2 = new Friendship(new FriendshipId(secondUserId, firstUserId), now);
        this.repoFriendship.store(friendship1);
        this.repoFriendship.store(friendship2);
    }

    /**
     * @param firstUserId the id of the first user
     * @param secondUserId the id of the second user
     * @throws ItemDoesntExistException if a friendship between firstUserId and secondUserId doesn't exist
     */
    public void removeFriendship(UUID firstUserId, UUID secondUserId) throws ItemDoesntExistException {
        FriendshipId friendshipId1 = new FriendshipId(firstUserId, secondUserId);
        FriendshipId friendshipId2 = new FriendshipId(secondUserId, firstUserId);
        this.repoFriendship.erase(friendshipId1);
        this.repoFriendship.erase(friendshipId2);
    }

    public void makeFriendshipRequest(UUID sourceUserId, UUID destinationUserId) throws ItemAlreadyExistsException {
        // TODO: make sure they aren't friends already
        FriendshipRequestId friendshipRequestId = new FriendshipRequestId(sourceUserId, destinationUserId);
        FriendshipRequest friendshipRequest = new FriendshipRequest(friendshipRequestId, LocalDateTime.now());
        this.repoFriendshipRequest.store(friendshipRequest);
    }

    public void acceptFriendshipRequest(UUID sourceUserId, UUID destinationUserId) throws ItemDoesntExistException, ItemAlreadyExistsException {
        FriendshipRequestId friendshipRequestId = new FriendshipRequestId(sourceUserId, destinationUserId);
        repoFriendshipRequest.erase(friendshipRequestId);

        FriendshipRequestId friendshipRequestIdInverse = new FriendshipRequestId(destinationUserId, sourceUserId);
        try {
            repoFriendshipRequest.erase(friendshipRequestIdInverse);
        } catch (ItemDoesntExistException e) {
            // NOTE: Do nothing if inverse request doesn't exist.
        }

        addFriendship(sourceUserId, destinationUserId);
    }

    public void removeFriendshipRequest(UUID sourceUserId, UUID destinationUserId) throws ItemDoesntExistException {
        FriendshipRequestId friendshipRequestId = new FriendshipRequestId(sourceUserId, destinationUserId);
        repoFriendshipRequest.erase(friendshipRequestId);
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
            disjointSet.union(friendship.getId().getFirstUserId(), friendship.getId().getSecondUserId());
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
            if (!userFriendIds.containsKey(friendship.getId().getFirstUserId())) {
                userFriendIds.put(friendship.getId().getFirstUserId(), new ArrayList<>());
            }
            ArrayList<UUID> firstFriendIds = userFriendIds.get(friendship.getId().getFirstUserId());
            firstFriendIds.add(friendship.getId().getSecondUserId());
            
            if (!userFriendIds.containsKey(friendship.getId().getSecondUserId())) {
                userFriendIds.put(friendship.getId().getSecondUserId(), new ArrayList<>());
            }
            ArrayList<UUID> secondFriendIds = userFriendIds.get(friendship.getId().getSecondUserId());
            secondFriendIds.add(friendship.getId().getFirstUserId());
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

    public boolean areFriends(UUID firstUserId, UUID secondUserId) {
        try {
            repoFriendship.find(new FriendshipId(firstUserId, secondUserId));
            return true;
        } catch (ItemDoesntExistException e) {
            return false;
        }
    }

    public FriendshipRequest getFriendshipRequest(UUID sourceUserId, UUID destinationUserId) throws ItemDoesntExistException {
        return repoFriendshipRequest.find(new FriendshipRequestId(sourceUserId, destinationUserId));
    }
}
