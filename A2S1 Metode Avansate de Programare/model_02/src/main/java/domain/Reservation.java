package domain;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDateTime;

public class Reservation {
    int id;
    int clientId;
    int hotelId;
    LocalDateTime startDate;
    int noNights;

    public static Reservation fromResultSet(ResultSet resultSet) {
        int id;
        try {
            id = resultSet.getInt("id");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        int clientId;
        try {
            clientId = resultSet.getInt("clientId");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        int hotelId;
        try {
            hotelId = resultSet.getInt("hotelId");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        LocalDateTime startDate;
        try {
            startDate = resultSet.getDate("startDate").toLocalDate().atStartOfDay();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        int noNights;
        try {
            noNights = resultSet.getInt("noNights");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return new Reservation(id, clientId, hotelId, startDate, noNights);
    }

    public Reservation(int id, int clientId, int hotelId, LocalDateTime startDate, int noNights) {
        this.id = id;
        this.clientId = clientId;
        this.hotelId = hotelId;
        this.startDate = startDate;
        this.noNights = noNights;
    }

    public int getId() {
        return id;
    }

    public int getClientId() {
        return clientId;
    }

    public int getHotelId() {
        return hotelId;
    }

    public LocalDateTime getStartDate() {
        return startDate;
    }

    public int getNoNights() {
        return noNights;
    }
}
