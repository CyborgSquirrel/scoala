package repo;

import domain.Client;
import domain.Hotel;

import java.sql.*;
import java.util.ArrayList;

public class RepoHotel {
    private String url;
    private String userName;
    private String password;

    public RepoHotel(String url, String userName, String password) {
        this.url = url;
        this.userName = userName;
        this.password = password;
    }

    public void store(Hotel hotel) throws ItemAlreadyExistsException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "INSERT INTO \"Hotel\"(locationId, name, noRooms, pricePerNight, type) VALUES (?, ?, ?, ?, ?)"
                );
        ) {
            statement.setInt(1, hotel.getLocationId());
            statement.setString(2, hotel.getName());
            statement.setInt(3, hotel.getNoRooms());
            statement.setDouble(4, hotel.getPricePerNight());
            statement.setInt(5, hotel.getType().getValue());

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
                        "DELETE FROM \"Hotel\" WHERE id = ?"
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

    public Hotel find(int id) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT id, locationId, name, noRooms, pricePerNight, type FROM \"Hotel\" WHERE id = ?"
                );
        ) {
            statement.setInt(1, id);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return Hotel.fromResultSet(resultSet);
            } else {
                throw new ItemDoesntExistException();
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Hotel[] getAll() {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement("SELECT id, locationId, name, noRooms, pricePerNight, type FROM \"Hotel\"");
                ResultSet resultSet = statement.executeQuery();
        ) {
            ArrayList<Hotel> hotels = new ArrayList<>();
            while (resultSet.next()) {
                Hotel hotel = Hotel.fromResultSet(resultSet);
                hotels.add(hotel);
            }
            return hotels.toArray(new Hotel[0]);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
