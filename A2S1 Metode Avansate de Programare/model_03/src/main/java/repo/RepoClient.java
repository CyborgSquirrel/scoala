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

    public Client find(String username) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT username, name FROM \"Client\" WHERE username = ?"
                );
        ) {
            statement.setString(1, username);

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
                PreparedStatement statement = connection.prepareStatement("SELECT username, name FROM \"Client\"");
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
