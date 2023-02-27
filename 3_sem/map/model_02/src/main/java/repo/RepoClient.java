package repo;

import domain.Client;

import java.sql.*;
import java.util.ArrayList;

public class RepoClient {
    private String url;
    private String userName;
    private String password;

    public RepoClient(String url, String userName, String password) {
        this.url = url;
        this.userName = userName;
        this.password = password;
    }

    public void store(Client client) throws ItemAlreadyExistsException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "INSERT INTO \"Client\"(name, fidelityGrade, age, hobbies) VALUES (?, ?, ?, ?)"
                );
        ) {
            statement.setString(1, client.getName());
            statement.setInt(2, client.getFidelityGrade());
            statement.setInt(3, client.getAge());
            statement.setInt(4, client.getHobbies());

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
                        "DELETE FROM \"Client\" WHERE id = ?"
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

    public Client find(int id) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT id, name, fidelityGrade, age, hobbies FROM \"Client\" WHERE id = ?"
                );
        ) {
            statement.setInt(1, id);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return Client.fromResultSet(resultSet);
            } else {
                throw new ItemDoesntExistException();
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Client[] getAll() {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement("SELECT id, name, fidelityGrade, age, hobbies FROM \"Client\"");
                ResultSet resultSet = statement.executeQuery();
        ) {
            ArrayList<Client> clients = new ArrayList<>();
            while (resultSet.next()) {
                Client client = Client.fromResultSet(resultSet);
                clients.add(client);
            }
            return clients.toArray(new Client[0]);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
