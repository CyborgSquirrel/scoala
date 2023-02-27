package repo;

import domain.Client;
import domain.SpecialOffer;

import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;

public class RepoSpecialOffer {
    private String url;
    private String userName;
    private String password;

    public RepoSpecialOffer(String url, String userName, String password) {
        this.url = url;
        this.userName = userName;
        this.password = password;
    }

    public void store(SpecialOffer specialOffer) throws ItemAlreadyExistsException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "INSERT INTO \"SpecialOffer\"(hotelId, startDate, endDate, percents) VALUES (?, ?, ?, ?)"
                );
        ) {
            statement.setInt(1, specialOffer.getHotelId());
            statement.setDate(2, new Date(specialOffer.getStartDate().getTime()));
            statement.setDate(3, new Date(specialOffer.getEndDate().getTime()));
            statement.setInt(4, specialOffer.getPercents());

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
                        "DELETE FROM \"SpecialOffer\" WHERE id = ?"
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

    public SpecialOffer find(int id) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT id, hotelId, startDate, endDate, percents FROM \"SpecialOffer\" WHERE id = ?"
                );
        ) {
            statement.setInt(1, id);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return SpecialOffer.fromResultSet(resultSet);
            } else {
                throw new ItemDoesntExistException();
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public SpecialOffer[] getAll() {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement("SELECT id, hotelId, startDate, endDate, percents FROM \"SpecialOffer\"");
                ResultSet resultSet = statement.executeQuery();
        ) {
            ArrayList<SpecialOffer> specialOffers = new ArrayList<>();
            while (resultSet.next()) {
                SpecialOffer specialOffer = SpecialOffer.fromResultSet(resultSet);
                specialOffers.add(specialOffer);
            }
            return specialOffers.toArray(new SpecialOffer[0]);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
