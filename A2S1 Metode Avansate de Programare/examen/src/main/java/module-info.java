module com.example.model {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;

    exports domain;
    exports gui;
    opens gui to javafx.fxml;
}