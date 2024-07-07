package repo;

import domain.Table;

import java.sql.*;
import java.util.ArrayList;

public class RepoTable {
    private String url;
    private String userName;
    private String password;

    public RepoTable(String url, String userName, String password) {
        this.url = url;
        this.userName = userName;
        this.password = password;
    }

    public void store(Table table) throws ItemAlreadyExistsException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "INSERT INTO \"Table\" DEFAULT VALUES"
                );
        ) {
//            statement.setInt(1, table.getId());

            statement.execute();
        } catch (SQLException e) {
            if (e.getSQLState().startsWith("23")) {
                throw new ItemAlreadyExistsException();
            }
            throw new RuntimeException(e);
        }
    }

    public void update(Table table) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "UPDATE \"Table\" WHERE id = ?"
                );
        ) {
            statement.setInt(1, table.getId());

            int rowCount = statement.executeUpdate();
            if (rowCount == 0) {
                throw new ItemDoesntExistException();
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public void erase(int id) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "DELETE FROM \"Table\" WHERE id = ?"
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

    public Table find(int id) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT id FROM \"Table\" WHERE id = ?"
                );
        ) {
            statement.setInt(1, id);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return Table.fromResultSet(resultSet);
            } else {
                throw new ItemDoesntExistException();
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Table[] getAll() {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement("SELECT id FROM \"Table\"");
                ResultSet resultSet = statement.executeQuery();
        ) {
            ArrayList<Table> tables = new ArrayList<>();
            while (resultSet.next()) {
                Table table = Table.fromResultSet(resultSet);
                tables.add(table);
            }
            return tables.toArray(new Table[0]);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}