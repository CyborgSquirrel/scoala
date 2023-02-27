package domain;

import java.time.LocalDateTime;
import java.util.ArrayList;

public class Order {
    int id;
    Table table;
    ArrayList<MenuItem> menuItems;
    LocalDateTime date;
    OrderStatus status;

    public Order(int id, Table table, ArrayList<MenuItem> menuItems, LocalDateTime date, OrderStatus status) {
        this.id = id;
        this.table = table;
        this.menuItems = menuItems;
        this.date = date;
        this.status = status;
    }

    public int getId() {
        return id;
    }

    public Table getTable() {
        return table;
    }

    public ArrayList<MenuItem> getMenuItems() {
        return menuItems;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public OrderStatus getStatus() {
        return status;
    }
}
