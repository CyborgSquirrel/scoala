package domain;

import java.sql.ResultSet;
import java.sql.SQLException;

public class Client {
    String username;
    String name;

    public static Client fromResultSet(ResultSet resultSet) {
        String username;
        try {
            username = resultSet.getString("username");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        String name;
        try {
            name = resultSet.getString("name");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return new Client(username, name);
    }

    public Client(String username, String name) {
        this.username = username;
        this.name = name;
    }

    public String getUsername() {
        return username;
    }

    public String getName() {
        return name;
    }
}
