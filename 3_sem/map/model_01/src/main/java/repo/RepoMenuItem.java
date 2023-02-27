package repo;

import domain.MenuItem;
import domain.Table;

import java.sql.*;
import java.util.ArrayList;

public class RepoMenuItem {
    private String url;
    private String userName;
    private String password;

    public RepoMenuItem(String url, String userName, String password) {
        this.url = url;
        this.userName = userName;
        this.password = password;
    }

    public void store(MenuItem menuItem) throws ItemAlreadyExistsException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "INSERT INTO \"MenuItem\" (category, item, price, currency) VALUES (?, ?, ?, ?)"
                );
        ) {
            statement.setString(1, menuItem.getCategory());
            statement.setString(2, menuItem.getItem());
            statement.setFloat(3, menuItem.getPrice());
            statement.setString(4, menuItem.getCurrency());

            statement.execute();
        } catch (SQLException e) {
            if (e.getSQLState().startsWith("23")) {
                throw new ItemAlreadyExistsException();
            }
            throw new RuntimeException(e);
        }
    }

    public void update(MenuItem menuItem) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "UPDATE \"MenuItem\" SET category = ?, item = ?, price = ?, currency = ? WHERE id = ?"
                );
        ) {
            statement.setString(1, menuItem.getCategory());
            statement.setString(2, menuItem.getItem());
            statement.setFloat(3, menuItem.getPrice());
            statement.setString(4, menuItem.getCurrency());

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
                        "DELETE FROM \"MenuItem\" WHERE id = ?"
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

    public MenuItem find(int id) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT id, category, item, price, currency FROM \"MenuItem\" WHERE id = ?"
                );
        ) {
            statement.setInt(1, id);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return MenuItem.fromResultSet(resultSet);
            } else {
                throw new ItemDoesntExistException();
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public MenuItem[] getAll() {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement("SELECT id, category, item, price, currency FROM \"MenuItem\"");
                ResultSet resultSet = statement.executeQuery();
        ) {
            ArrayList<MenuItem> menuItems = new ArrayList<>();
            while (resultSet.next()) {
                MenuItem menuItem = MenuItem.fromResultSet(resultSet);
                menuItems.add(menuItem);
            }
            return menuItems.toArray(new MenuItem[0]);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}