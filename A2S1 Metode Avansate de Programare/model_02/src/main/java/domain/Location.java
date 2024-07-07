package domain;

import java.sql.ResultSet;
import java.sql.SQLException;

public class Location {
    int id;
    String name;

    public static Location fromResultSet(ResultSet resultSet) {
        int id;
        try {
            id = resultSet.getInt("id");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        String name;
        try {
            name = resultSet.getString("name");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return new Location(id, name);
    }

    public Location(int id, String name) {
        this.id = id;
        this.name = name;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }
}
