module com.example.social {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;

    opens com.example.social to javafx.fxml;
    exports com.example.social;
}