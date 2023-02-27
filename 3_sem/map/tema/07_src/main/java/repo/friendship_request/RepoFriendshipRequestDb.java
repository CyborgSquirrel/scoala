package repo.friendship;

import domain.Friendship;
import domain.FriendshipId;
import domain.FriendshipRequest;
import domain.FriendshipRequestId;
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;
import repo.friendship_request.RepoFriendshipRequest;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.UUID;

public class RepoFriendshipRequestDb extends RepoFriendshipRequest {
    private String url;
    private String userName;
    private String password;

    private FriendshipRequest readItem(ResultSet resultSet) {
        UUID sourceUserId;
        try {
            sourceUserId = UUID.fromString(resultSet.getString("id_source_user"));
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        UUID destinationUserId;
        try {
            destinationUserId = UUID.fromString(resultSet.getString("id_destination_user"));
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        LocalDateTime createdTime;
        try {
            createdTime = resultSet.getTimestamp("created_time").toLocalDateTime();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        FriendshipRequest friendshipRequest = new FriendshipRequest(new FriendshipRequestId(sourceUserId, destinationUserId), createdTime);
        return friendshipRequest;
    }

    public RepoFriendshipRequestDb(String url, String userName, String password) {
        this.url = url;
        this.userName = userName;
        this.password = password;
    }

    @Override
    public void store(FriendshipRequest friendshipRequest) throws ItemAlreadyExistsException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "INSERT INTO \"FriendshipRequest\" (id_source_user, id_destination_user, created_time) VALUES (?, ?, ?)"
                );
        ) {
            statement.setString(1, friendshipRequest.getId().getSourceUserId().toString());
            statement.setString(2, friendshipRequest.getId().getDestinationUserId().toString());
            statement.setTimestamp(3, Timestamp.valueOf(friendshipRequest.getCreatedTime()));

            statement.execute();
        } catch (SQLException e) {
            if (e.getSQLState().startsWith("23")) {
                throw new ItemAlreadyExistsException();
            }
            throw new RuntimeException(e);
        }
    }

    @Override
    public void update(FriendshipRequest friendshipRequest) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "UPDATE \"FriendshipRequest\" SET created_time = ? WHERE id_source_user = ? AND id_destination_user = ?"
                );
        ) {
            statement.setTimestamp(1, Timestamp.valueOf(friendshipRequest.getCreatedTime()));
            statement.setString(2, friendshipRequest.getId().getSourceUserId().toString());
            statement.setString(3, friendshipRequest.getId().getDestinationUserId().toString());

            int rowCount = statement.executeUpdate();
            if (rowCount == 0) {
                throw new ItemDoesntExistException();
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void erase(FriendshipRequestId friendshipRequestId) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "DELETE FROM \"FriendshipRequest\" WHERE id_source_user = ? AND id_destination_user = ?"
                );
        ) {
            statement.setString(1, friendshipRequestId.getSourceUserId().toString());
            statement.setString(2, friendshipRequestId.getDestinationUserId().toString());

            int rowCount = statement.executeUpdate();
            if (rowCount == 0) {
                throw new ItemDoesntExistException();
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public FriendshipRequest find(FriendshipRequestId friendshipRequestId) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT id_source_user, id_destination_user, created_time FROM \"FriendshipRequest\" WHERE id_source_user = ? AND id_destination_user = ?"
                );
        ) {
            statement.setString(1, friendshipRequestId.getSourceUserId().toString());
            statement.setString(2, friendshipRequestId.getDestinationUserId().toString());

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
    public FriendshipRequest[] getAll() {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement("SELECT id_source_user, id_destination_user, created_time FROM \"FriendshipRequest\"");
                ResultSet resultSet = statement.executeQuery();
        ) {
            ArrayList<FriendshipRequest> friendshipRequests = new ArrayList<>();
            while (resultSet.next()) {
                FriendshipRequest friendshipRequest = readItem(resultSet);
                friendshipRequests.add(friendshipRequest);
            }
            return friendshipRequests.toArray(new FriendshipRequest[0]);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
