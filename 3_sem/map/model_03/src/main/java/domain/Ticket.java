package domain;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDateTime;

public class Ticket {
    String username;
    long flightId;
    LocalDateTime purchaseTime;

    public static Ticket fromResultSet(ResultSet resultSet) {
        String username;
        try {
            username = resultSet.getString("username");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        long flightId;
        try {
            flightId = resultSet.getLong("flightId");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        LocalDateTime purchaseTime;
        try {
            purchaseTime = resultSet.getTimestamp("purchaseTime").toLocalDateTime();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return new Ticket(username, flightId, purchaseTime);
    }

    public Ticket(String username, long flightId, LocalDateTime purchaseTime) {
        this.username = username;
        this.flightId = flightId;
        this.purchaseTime = purchaseTime;
    }

    public String getUsername() {
        return username;
    }

    public long getFlightId() {
        return flightId;
    }

    public LocalDateTime getPurchaseTime() {
        return purchaseTime;
    }
}
