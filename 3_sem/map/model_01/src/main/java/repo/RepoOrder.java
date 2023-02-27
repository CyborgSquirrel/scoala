package repo;

import domain.MenuItem;
import domain.Order;
import domain.OrderStatus;
import domain.Table;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;

public class RepoOrder {
    private String url;
    private String userName;
    private String password;

    private Order readItem(ResultSet resultSet) {
        int id;
        try {
            id = resultSet.getInt("id");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        int table_id;
        try {
            table_id = resultSet.getInt("table_id");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        LocalDateTime date;
        try {
            date = resultSet.getTimestamp("date").toLocalDateTime();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        OrderStatus orderStatus;
        try {
            orderStatus = OrderStatus.fromValue(resultSet.getInt("status"));
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        Table table = null;
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT id FROM \"Table\" WHERE \"Table\".id = ?"
                );
        ) {
            statement.setInt(1, table_id);

            ResultSet resultSet1 = statement.executeQuery();
            if (resultSet1.next()) {
                table = Table.fromResultSet(resultSet1);
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        ArrayList<MenuItem> menuItems = new ArrayList<>();
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT id, category, item, price, currency FROM \"OrderItem\" INNER JOIN \"MenuItem\" ON \"MenuItem\".id = \"OrderItem\".menu_item_id WHERE \"OrderItem\".order_id = ?"
                );
        ) {
            statement.setInt(1, id);

            ResultSet resultSet1 = statement.executeQuery();
            while (resultSet1.next()) {
                menuItems.add(MenuItem.fromResultSet(resultSet1));
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

        Order order = new Order(id, table, menuItems, date, orderStatus);
        return order;
    }

    public RepoOrder(String url, String userName, String password) {
        this.url = url;
        this.userName = userName;
        this.password = password;
    }

    public void store(Order order) throws ItemAlreadyExistsException {
        String[] returnId = { "id" };

        int order_id;
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "INSERT INTO \"Order\" (table_id, date, status) VALUES (?, ?, ?)",
                        returnId
                );
        ) {
            statement.setInt(1, order.getTable().getId());
            statement.setTimestamp(2, Timestamp.valueOf(order.getDate()));
            statement.setInt(3, order.getStatus().getValue());

            statement.execute();

            ResultSet generatedKeys = statement.getGeneratedKeys();
            generatedKeys.next();
            order_id = generatedKeys.getInt("id");
        } catch (SQLException e) {
            if (e.getSQLState().startsWith("23")) {
                throw new ItemAlreadyExistsException();
            }
            throw new RuntimeException(e);
        }

        for (MenuItem menuItem : order.getMenuItems()) {
            try (
                    Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                    PreparedStatement statement = connection.prepareStatement(
                            "INSERT INTO \"OrderItem\" (order_id, menu_item_id) VALUES (?, ?)"
                    );
            ) {
                statement.setInt(1, order_id);
                statement.setInt(2, menuItem.getId());

                statement.execute();
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
        }
    }

    public void erase(int id) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "DELETE FROM \"Order\" WHERE id = ?"
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

    public Order find(int id) throws ItemDoesntExistException {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement(
                        "SELECT id, table_id, date, status FROM \"Order\" WHERE id = ?"
                );
        ) {
            statement.setInt(1, id);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return readItem(resultSet);
            } else {
                throw new ItemDoesntExistException();
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Order[] getAll() {
        try (
                Connection connection = DriverManager.getConnection(this.url, this.userName, this.password);
                PreparedStatement statement = connection.prepareStatement("SELECT id, table_id, date, status FROM \"Order\"");
                ResultSet resultSet = statement.executeQuery();
        ) {
            ArrayList<Order> orders = new ArrayList<>();
            while (resultSet.next()) {
                Order order = readItem(resultSet);
                orders.add(order);
            }
            return orders.toArray(new Order[0]);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}