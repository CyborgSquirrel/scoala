package domain;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.time.LocalDateTime;
import java.util.Date;

public class SpecialOffer {
    int id;
    int hotelId;
    Date startDate;
    Date endDate;
    int percents;

    public static SpecialOffer fromResultSet(ResultSet resultSet) {
        int id;
        try {
            id = resultSet.getInt("id");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        int hotelId;
        try {
            hotelId = resultSet.getInt("hotelId");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        Date startDate;
        try {
            startDate = resultSet.getDate("startDate");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        Date endDate;
        try {
            endDate = resultSet.getDate("endDate");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        int percents;
        try {
            percents = resultSet.getInt("percents");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return new SpecialOffer(id, hotelId, startDate, endDate, percents);
    }

    public SpecialOffer(int id, int hotelId, Date startDate, Date endDate, int percents) {
        this.id = id;
        this.hotelId = hotelId;
        this.startDate = startDate;
        this.endDate = endDate;
        this.percents = percents;
    }

    public int getId() {
        return id;
    }

    public int getHotelId() {
        return hotelId;
    }

    public Date getStartDate() {
        return startDate;
    }

    public Date getEndDate() {
        return endDate;
    }

    public int getPercents() {
        return percents;
    }
}
