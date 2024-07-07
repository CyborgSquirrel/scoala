package repo;

import domain.Client;
import domain.Flight;

import java.sql.*;
import java.util.ArrayList;

public class RepoFlight {
    private String url;
    private String userName;
    private String password;

    public RepoFlight(String url, String userName, String password) {
        this.url = url;
        this.userName = userName;
        this.password = password;
    }

    public Flight find(long id) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT id, ffrom, fto, departureTime, landingTime, seats FROM \"Flight\" WHERE id = ?"
                );
        ) {
            statement.setLong(1, id);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return Flight.fromResultSet(resultSet);
            } else {
                throw new ItemDoesntExistException();
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Flight[] getAll() {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement("SELECT id, ffrom, fto, departureTime, landingTime, seats FROM \"Flight\"");
                ResultSet resultSet = statement.executeQuery();
        ) {
            ArrayList<Flight> flights = new ArrayList<>();
            while (resultSet.next()) {
                Flight flight = Flight.fromResultSet(resultSet);
                flights.add(flight);
            }
            return flights.toArray(new Flight[0]);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
