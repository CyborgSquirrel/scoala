package domain;

import java.sql.ResultSet;
import java.sql.SQLException;

public class Table {
    private int id;

    public Table(int id) {
        this.id = id;
    }

    public static Table fromResultSet(ResultSet resultSet) {
        int id;
        try {
            id = resultSet.getInt("id");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return new Table(id);
    }

    public int getId() {
        return id;
    }
}
