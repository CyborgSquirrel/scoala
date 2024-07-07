module com.example.javava1919 {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.javava1919 to javafx.fxml;
    exports com.example.javava1919;
}