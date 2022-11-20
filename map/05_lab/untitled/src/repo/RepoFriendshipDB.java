package repo;

import domain.Friendship;
import domain.FriendshipId;
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.UUID;

public class RepoFriendshipDB extends RepoFriendship {
    private String url;
    private String userName;
    private String password;

    // TODO: take care of these exceptions.
    private Friendship readItem(ResultSet resultSet) {
        UUID firstUserId;
        try {
            firstUserId = UUID.fromString(resultSet.getString("id_user_1"));
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        UUID secondUserId;
        try {
            secondUserId = UUID.fromString(resultSet.getString("id_user_2"));
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        LocalDateTime friendsSince;
        try {
            friendsSince = resultSet.getTimestamp("friends_since").toLocalDateTime();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        Friendship friendship = new Friendship(new FriendshipId(firstUserId, secondUserId), friendsSince);
        return friendship;
    }

    public RepoFriendshipDB(String url, String userName, String password) {
        this.url = url;
        this.userName = userName;
        this.password = password;
    }

    @Override
    public void store(Friendship friendship) throws ItemAlreadyExistsException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "INSERT INTO \"Friendship\" (id_user_1, id_user_2, friends_since) VALUES (?, ?, ?)"
                );
        ) {
            statement.setString(1, friendship.getId().getFirstUserId().toString());
            statement.setString(2, friendship.getId().getSecondUserId().toString());
            statement.setTimestamp(3, Timestamp.valueOf(friendship.getFriendsSince()));

            // TODO: careful about exception here
            statement.execute();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void update(Friendship friendship) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "UPDATE \"Friendship\" SET friends_since = ? WHERE id_user_1 = ? AND id_user_2 = ?"
                );
        ) {
            statement.setTimestamp(1, Timestamp.valueOf(friendship.getFriendsSince()));
            statement.setString(2, friendship.getId().getFirstUserId().toString());
            statement.setString(3, friendship.getId().getSecondUserId().toString());

            int rowCount = statement.executeUpdate();
            if (rowCount == 0) {
                throw new ItemDoesntExistException();
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void erase(FriendshipId friendshipId) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "DELETE FROM \"Friendship\" WHERE id_user_1 = ? AND id_user_2 = ?"
                );
        ) {
            statement.setString(1, friendshipId.getFirstUserId().toString());
            statement.setString(2, friendshipId.getSecondUserId().toString());

            int rowCount = statement.executeUpdate();
            if (rowCount == 0) {
                throw new ItemDoesntExistException();
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Friendship find(FriendshipId friendshipId) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT id_user_1, id_user_2, friends_since FROM \"Friendship\" WHERE id_user_1 = ? AND id_user_2 = ?"
                );
        ) {
            statement.setString(1, friendshipId.getFirstUserId().toString());
            statement.setString(2, friendshipId.getSecondUserId().toString());

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return readItem(resultSet);
            } else {
                throw new ItemDoesntExistException();
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Friendship[] getAll() {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement("SELECT id_user_1, id_user_2, friends_since FROM \"Friendship\"");
                ResultSet resultSet = statement.executeQuery();
        ) {
            ArrayList<Friendship> friendships = new ArrayList<>();
            while (resultSet.next()) {
                Friendship friendship = readItem(resultSet);
                friendships.add(friendship);
            }
            return friendships.toArray(new Friendship[0]);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
