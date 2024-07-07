module inventory {
    requires javafx.graphics;
    requires javafx.fxml;
    requires javafx.controls;

    opens inventory.model to javafx.base;
    exports inventory.model;
    opens inventory to javafx.fxml;
    exports inventory;
    opens inventory.controller to javafx.fxml;
    exports inventory.controller;
}