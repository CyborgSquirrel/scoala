package repo.message;

import domain.FriendshipRequest;
import domain.FriendshipRequestId;
import domain.Message;
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.UUID;

public class RepoMessageDb extends RepoMessage {
    private String url;
    private String userName;
    private String password;

    private Message readItem(ResultSet resultSet) {
        UUID id;
        try {
            id = UUID.fromString(resultSet.getString("id"));
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
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
        LocalDateTime timestamp;
        try {
            timestamp = resultSet.getTimestamp("timestamp").toLocalDateTime();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        String text = null;
        try {
            text = resultSet.getString("text");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        Message message = new Message(id, sourceUserId, destinationUserId, text, timestamp);
        return message;
    }

    public RepoMessageDb(String url, String userName, String password) {
        this.url = url;
        this.userName = userName;
        this.password = password;
    }

    @Override
    public void store(Message message) throws ItemAlreadyExistsException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "INSERT INTO \"Message\" (id, id_source_user, id_destination_user, timestamp, text) VALUES (?, ?, ?, ?, ?)"
                );
        ) {
            statement.setString(1, message.getId().toString());
            statement.setString(2, message.getSourceUserId().toString());
            statement.setString(3, message.getDestinationUserId().toString());
            statement.setTimestamp(4, Timestamp.valueOf(message.getTimestamp()));
            statement.setString(5, message.getText());

            statement.execute();
        } catch (SQLException e) {
            if (e.getSQLState().startsWith("23")) {
                throw new ItemAlreadyExistsException();
            }
            throw new RuntimeException(e);
        }
    }

    @Override
    public void update(Message message) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "UPDATE \"Message\" SET id_source_user = ?, id_destination_user = ?, timestamp = ?, text = ? WHERE id = ?"
                );
        ) {
            statement.setString(1, message.getSourceUserId().toString());
            statement.setString(2, message.getDestinationUserId().toString());
            statement.setTimestamp(3, Timestamp.valueOf(message.getTimestamp()));
            statement.setString(4, message.getText());
            statement.setString(5, message.getId().toString());

            int rowCount = statement.executeUpdate();
            if (rowCount == 0) {
                throw new ItemDoesntExistException();
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void erase(UUID id) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "DELETE FROM \"Message\" WHERE id = ?"
                );
        ) {
            statement.setString(1, id.toString());

            int rowCount = statement.executeUpdate();
            if (rowCount == 0) {
                throw new ItemDoesntExistException();
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Message find(UUID id) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT id, id_source_user, id_destination_user, timestamp, text FROM \"Message\" WHERE id = ?"
                );
        ) {
            statement.setString(1, id.toString());

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
    public Message[] getAll() {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement("SELECT id, id_source_user, id_destination_user, timestamp, text FROM \"Message\"");
                ResultSet resultSet = statement.executeQuery();
        ) {
            ArrayList<Message> messages = new ArrayList<>();
            while (resultSet.next()) {
                Message message = readItem(resultSet);
                messages.add(message);
            }
            return messages.toArray(new Message[0]);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
