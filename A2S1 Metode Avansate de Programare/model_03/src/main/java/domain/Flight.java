package domain;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDateTime;

public class Flight {
    long id;
    String from;
    String to;
    LocalDateTime departureTime;
    LocalDateTime landingTime;
    int seats;

    public static Flight fromResultSet(ResultSet resultSet) {
        long id;
        try {
            id = resultSet.getLong("id");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        String from;
        try {
            from = resultSet.getString("ffrom");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        String to;
        try {
            to = resultSet.getString("fto");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        LocalDateTime departureTime;
        try {
            departureTime = resultSet.getTimestamp("departureTime").toLocalDateTime();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        LocalDateTime landingTime;
        try {
            landingTime = resultSet.getTimestamp("landingTime").toLocalDateTime();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        int seats;
        try {
            seats = resultSet.getInt("seats");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return new Flight(id, from, to, departureTime, landingTime, seats);
    }

    public Flight(long id, String from, String to, LocalDateTime departureTime, LocalDateTime landingTime, int seats) {
        this.id = id;
        this.from = from;
        this.to = to;
        this.departureTime = departureTime;
        this.landingTime = landingTime;
        this.seats = seats;
    }

    public long getId() {
        return id;
    }

    public String getFrom() {
        return from;
    }

    public String getTo() {
        return to;
    }

    public LocalDateTime getDepartureTime() {
        return departureTime;
    }

    public LocalDateTime getLandingTime() {
        return landingTime;
    }

    public int getSeats() {
        return seats;
    }
}
