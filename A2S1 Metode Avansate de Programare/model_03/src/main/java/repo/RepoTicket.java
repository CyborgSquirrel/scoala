package repo;

import domain.Client;
import domain.Ticket;

import java.sql.*;
import java.util.ArrayList;

public class RepoTicket {
    private String url;
    private String userName;
    private String password;

    public RepoTicket(String url, String userName, String password) {
        this.url = url;
        this.userName = userName;
        this.password = password;
    }

    public Ticket find(String username, long flightId) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT username, flightId, purchaseTime FROM \"Ticket\" WHERE username = ?, flightId = ?"
                );
        ) {
            statement.setString(1, username);
            statement.setLong(2, flightId);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return Ticket.fromResultSet(resultSet);
            } else {
                throw new ItemDoesntExistException();
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Ticket[] getAll() {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement("SELECT username, flightId, purchaseTime FROM \"Ticket\"");
                ResultSet resultSet = statement.executeQuery();
        ) {
            ArrayList<Ticket> tickets = new ArrayList<>();
            while (resultSet.next()) {
                Ticket ticket = Ticket.fromResultSet(resultSet);
                tickets.add(ticket);
            }
            return tickets.toArray(new Ticket[0]);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public void store(Ticket ticket) throws ItemAlreadyExistsException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "INSERT INTO \"Ticket\"(username, flightId, purchaseTime) VALUES (?, ?, ?)"
                );
        ) {
            statement.setString(1, ticket.getUsername());
            statement.setLong(2, ticket.getFlightId());
            statement.setTimestamp(3, Timestamp.valueOf(ticket.getPurchaseTime()));

            statement.execute();
        } catch (SQLException e) {
            if (e.getSQLState().startsWith("23")) {
                throw new ItemAlreadyExistsException();
            }
            throw new RuntimeException(e);
        }
    }
}
