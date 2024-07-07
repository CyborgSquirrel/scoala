package domain;

import java.sql.ResultSet;
import java.sql.SQLException;

public class MenuItem {
    int id;
    String category;
    String item;
    float price;
    String currency;

    public MenuItem(int id, String category, String item, float price, String currency) {
        this.id = id;
        this.category = category;
        this.item = item;
        this.price = price;
        this.currency = currency;
    }

    public static MenuItem fromResultSet(ResultSet resultSet) {
        int id;
        try {
            id = resultSet.getInt("id");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        String category;
        try {
            category = resultSet.getString("category");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        String item;
        try {
            item = resultSet.getString("item");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        float price;
        try {
            price = resultSet.getFloat("price");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        String currency;
        try {
            currency = resultSet.getString("currency");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        MenuItem menuItem = new MenuItem(id, category, item, price, currency);
        return menuItem;
    }

    public int getId() {
        return id;
    }

    public String getCategory() {
        return category;
    }

    public String getItem() {
        return item;
    }

    public float getPrice() {
        return price;
    }

    public String getCurrency() {
        return currency;
    }
}
