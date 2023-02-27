package repo;

import domain.Friendship;
import domain.FriendshipId;
import domain.User;
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;

import java.sql.*;
import java.util.ArrayList;
import java.util.UUID;

public class RepoUserDB extends RepoUser {
    private String url;
    private String userName;
    private String password;
    private User readItem(ResultSet resultSet) {
        UUID id;
        try {
            id = UUID.fromString(resultSet.getString("id"));
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        String name;
        try {
            name = resultSet.getString("name");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        User user = new User(id, name);
        return user;
    }

    public RepoUserDB(String url, String userName, String password) {
        this.url = url;
        this.userName = userName;
        this.password = password;
    }

    @Override
    public void store(User user) throws ItemAlreadyExistsException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "INSERT INTO \"User\" (id, name) VALUES (?, ?)"
                );
        ) {
            statement.setString(1, user.getId().toString());
            statement.setString(2, user.getName());

            statement.execute();
        } catch (SQLException e) {
            if (e.getSQLState().startsWith("23")) {
                throw new ItemAlreadyExistsException();
            }
            throw new RuntimeException(e);
        }
    }

    @Override
    public void update(User user) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "UPDATE \"User\" SET name = ? WHERE id = ?"
                );
        ) {
            statement.setString(1, user.getName());
            statement.setString(2, user.getId().toString());

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
                        "DELETE FROM \"User\" WHERE id = ?"
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
    public User find(UUID id) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT id, name FROM \"User\" WHERE id = ?"
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
    public User[] getAll() {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement("SELECT id, name FROM \"User\"");
                ResultSet resultSet = statement.executeQuery();
        ) {
            ArrayList<User> users = new ArrayList<>();
            while (resultSet.next()) {
                User user = readItem(resultSet);
                users.add(user);
            }
            return users.toArray(new User[0]);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
