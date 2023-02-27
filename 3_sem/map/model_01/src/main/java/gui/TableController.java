package gui;

import domain.MenuItem;
import domain.Table;
import javafx.beans.property.BooleanProperty;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.CheckBoxTableCell;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.VBox;
import srv.SrvManager;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class TableController {
    public VBox vBoxMenuItems;

    private SrvManager srvManager;
    private Table table;

    private ArrayList<TableView> tableViews = new ArrayList<>();

    public void setSrvManager(SrvManager srvManager) {
        this.srvManager = srvManager;
        tryUpdate();
    }
    public void setTable(Table table) {
        this.table = table;
        tryUpdate();
    }

    public void tryUpdate() {
        if (srvManager != null && table != null) {
            vBoxMenuItems.getChildren().clear();
            tableViews.clear();

            Map<String, List<MenuItem>> menuItemsGroupedByCategory = srvManager.getSrvMenuItem().getMenuItemsGroupedByCategory();
            for (Map.Entry<String, List<MenuItem>> categoryMenuItems : menuItemsGroupedByCategory.entrySet()) {
                String category = categoryMenuItems.getKey();
                Label labelCategory = new Label();
                labelCategory.setText(category);
                vBoxMenuItems.getChildren()
                        .add(labelCategory);

                List<MenuItem> menuItems = categoryMenuItems.getValue();

                var tableView = new TableView<OrderItem>();
                    var columnItem = new TableColumn<OrderItem, String>();
                    columnItem.setCellValueFactory(param -> new ReadOnlyStringWrapper(param.getValue().getMenuItem().getItem()));
                    tableView.getColumns().add(columnItem);

                    var columnPrice = new TableColumn<OrderItem, String>();
                    columnPrice.setCellValueFactory(param -> new ReadOnlyStringWrapper(Float.toString(param.getValue().getMenuItem().getPrice()) + " " + param.getValue().getMenuItem().getCurrency()));
                    tableView.getColumns().add(columnPrice);

                    var columnTick = new TableColumn<OrderItem, Boolean>();
                    columnTick.setCellValueFactory(new PropertyValueFactory<>("include"));
                    columnTick.setCellFactory(param -> new CheckBoxTableCell<>());
                    columnTick.setEditable(true);
                    tableView.getColumns().add(columnTick);
                tableView.setItems(FXCollections.observableList(menuItems.stream().map(menuItem -> new OrderItem(menuItem)).collect(Collectors.toList())));
                tableView.setEditable(true);
                vBoxMenuItems.getChildren()
                        .add(tableView);
                tableViews.add(tableView);
            }
        }
    }

    public void onPlaceOrderClicked(ActionEvent actionEvent) {
        List<MenuItem> orderItems = tableViews.stream()
                .map(TableView::getItems)
                .map(observableList -> observableList.stream().toList())
                .flatMap(List<OrderItem>::stream)
                .filter(orderItem -> orderItem.includeProperty().get())
                .map(OrderItem::getMenuItem)
                .toList();

        srvManager.getSrvOrder().makeOrder(table, new ArrayList<>(orderItems));
    }
}
