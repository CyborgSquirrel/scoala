package gui;

import domain.MenuItem;
import javafx.beans.property.BooleanProperty;
import javafx.beans.property.SimpleBooleanProperty;

public class OrderItem {
    public MenuItem getMenuItem() {
        return menuItem;
    }

    private MenuItem menuItem;
    private final BooleanProperty include = new SimpleBooleanProperty();

    OrderItem(MenuItem menuItem) {
        this.menuItem = menuItem;
    }

    public BooleanProperty includeProperty() { return include; }
}