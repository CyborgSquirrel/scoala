package domain;

import java.sql.ResultSet;
import java.sql.SQLException;

public class Hotel {
    int id;
    int locationId;
    String name;
    int noRooms;
    double pricePerNight;
    HotelType type;

    public static Hotel fromResultSet(ResultSet resultSet) {
        int id;
        try {
            id = resultSet.getInt("id");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        int locationId;
        try {
            locationId = resultSet.getInt("locationId");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        String name;
        try {
            name = resultSet.getString("name");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        int noRooms;
        try {
            noRooms = resultSet.getInt("noRooms");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        double pricePerNight;
        try {
            pricePerNight = resultSet.getDouble("pricePerNight");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        HotelType type;
        try {
            type = HotelType.fromValue(resultSet.getInt("type"));
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return new Hotel(id, locationId, name, noRooms, pricePerNight, type);
    }

    public Hotel(int id, int locationId, String name, int noRooms, double pricePerNight, HotelType type) {
        this.id = id;
        this.locationId = locationId;
        this.name = name;
        this.noRooms = noRooms;
        this.pricePerNight = pricePerNight;
        this.type = type;
    }

    public int getId() {
        return id;
    }

    public int getLocationId() {
        return locationId;
    }

    public String getName() {
        return name;
    }

    public int getNoRooms() {
        return noRooms;
    }

    public double getPricePerNight() {
        return pricePerNight;
    }

    public HotelType getType() {
        return type;
    }
}
