package repo;

import domain.Client;
import domain.Location;

import java.sql.*;
import java.util.ArrayList;

public class RepoLocation {
    private String url;
    private String userName;
    private String password;

    public RepoLocation(String url, String userName, String password) {
        this.url = url;
        this.userName = userName;
        this.password = password;
    }

    public void store(Location location) throws ItemAlreadyExistsException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "INSERT INTO \"Location\"(name) VALUES (?)"
                );
        ) {
            statement.setString(1, location.getName());

            statement.execute();
        } catch (SQLException e) {
            if (e.getSQLState().startsWith("23")) {
                throw new ItemAlreadyExistsException();
            }
            throw new RuntimeException(e);
        }
    }

    public void erase(int id) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "DELETE FROM \"Location\" WHERE id = ?"
                );
        ) {
            statement.setInt(1, id);

            int rowCount = statement.executeUpdate();
            if (rowCount == 0) {
                throw new ItemDoesntExistException();
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Location find(int id) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT id, name FROM \"Location\" WHERE id = ?"
                );
        ) {
            statement.setInt(1, id);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return Location.fromResultSet(resultSet);
            } else {
                throw new ItemDoesntExistException();
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Location[] getAll() {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement("SELECT id, name FROM \"Location\"");
                ResultSet resultSet = statement.executeQuery();
        ) {
            ArrayList<Location> locations = new ArrayList<>();
            while (resultSet.next()) {
                Location location = Location.fromResultSet(resultSet);
                locations.add(location);
            }
            return locations.toArray(new Location[0]);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
