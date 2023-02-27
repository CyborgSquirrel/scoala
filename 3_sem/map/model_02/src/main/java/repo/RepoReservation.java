package repo;

import domain.Client;
import domain.Reservation;

import java.sql.*;
import java.util.ArrayList;

public class RepoReservation {
    private String url;
    private String userName;
    private String password;

    public RepoReservation(String url, String userName, String password) {
        this.url = url;
        this.userName = userName;
        this.password = password;
    }

    public void store(Reservation reservation) throws ItemAlreadyExistsException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "INSERT INTO \"Reservation\"(clientId, hotelId, startDate, noNights) VALUES (?, ?, ?, ?)"
                );
        ) {
            statement.setInt(1, reservation.getClientId());
            statement.setInt(2, reservation.getHotelId());
            statement.setDate(3, Date.valueOf(reservation.getStartDate().toLocalDate()));
            statement.setInt(4, reservation.getNoNights());

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
                        "DELETE FROM \"Reservation\" WHERE id = ?"
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

    public Reservation find(int id) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT id, clientId, hotelId, startDate, noNights FROM \"Reservation\" WHERE id = ?"
                );
        ) {
            statement.setInt(1, id);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return Reservation.fromResultSet(resultSet);
            } else {
                throw new ItemDoesntExistException();
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Reservation[] getAll() {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement("SELECT id, clientId, hotelId, startDate, noNights FROM \"Reservation\"");
                ResultSet resultSet = statement.executeQuery();
        ) {
            ArrayList<Reservation> reservations = new ArrayList<>();
            while (resultSet.next()) {
                Reservation reservation = Reservation.fromResultSet(resultSet);
                reservations.add(reservation);
            }
            return reservations.toArray(new Reservation[0]);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
