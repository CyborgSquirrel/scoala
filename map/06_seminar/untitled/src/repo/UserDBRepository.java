package repo;

import domain.User;

import java.sql.*;
import java.util.HashSet;
import java.util.Set;

public class UserDBRepository implements Repo<Long, User> {
    private String url;
    private String userName;
    private String password;

    public UserDBRepository(String url, String userName, String password) {
        this.url = url;
        this.userName = userName;
        this.password = password;
    }

    @Override
    public User findOne(Long id) {
        return null;
    }

    @Override
    public Iterable<User> findAll() {
        Set<User> users = new HashSet<>();
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement("SELECT * FROM \"User\"");
                ResultSet resultSet = statement.executeQuery();
        ) {
            while (resultSet.next()) {
                long id = resultSet.getLong("id");
                String firstName = resultSet.getString("first_name");
                String lastName = resultSet.getString("last_name");
                User user = new User(id, firstName, lastName);
                users.add(user);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return users;
    }

    @Override
    public User save(User entity) {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement("INSERT INTO \"User\" (first_name, last_name) VALUES (?, ?)");
        ) {
            statement.setString(1, entity.getFirstName());
            statement.setString(2, entity.getLastName());
            statement.execute();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return null;
    }

    @Override
    public User delete(Long aLong) {
        return null;
    }

    @Override
    public User update(User entity) {
        return null;
    }
}
