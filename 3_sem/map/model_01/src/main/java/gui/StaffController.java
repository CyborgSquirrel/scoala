package gui;

import domain.Order;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import srv.SrvManager;

import java.time.format.DateTimeFormatter;
import java.util.*;
import java.util.stream.Collectors;

public class StaffController {
    public TableView placedOrders;
    private SrvManager srvManager;

    public void setSrvManager(SrvManager srvManager) {
        this.srvManager = srvManager;
        tryUpdate();
    }

    public TableColumn<Order, String> placedOrdersId;
    public TableColumn<Order, String> placedOrdersDate;
    public TableColumn<Order, String> placedOrdersItems;

    public void initialize() {
        placedOrdersId.setCellValueFactory(param -> new ReadOnlyStringWrapper(
            Integer.toString(param.getValue().getTable().getId())
        ));
        placedOrdersDate.setCellValueFactory(param -> new ReadOnlyStringWrapper(
                param.getValue().getDate().format(DateTimeFormatter.ISO_DATE_TIME)
        ));
        placedOrdersItems.setCellValueFactory(param -> new ReadOnlyStringWrapper(
                param.getValue().getMenuItems().stream()
                        .map(menuItem -> menuItem.getItem())
                        .collect(Collectors.joining(", "))
        ));
    }

    private void tryUpdate() {
        if (srvManager != null) {
            srvManager.getSrvOrder().addOnOrdersChangedCallback(orders -> this.updateOrders(orders));
            updateOrders(srvManager.getSrvOrder().getOrders());
        }
    }

    public void updateOrders(Order[] orders) {
        ArrayList<Order> orders1 = new ArrayList<>(Arrays.asList(orders));
        orders1.sort(Comparator.comparing(order -> order.getDate()));
        placedOrders.setItems(FXCollections.observableList(orders1));
    }
}