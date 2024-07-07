package gui;

import domain.Client;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.stage.Window;
import javafx.util.StringConverter;
import repo.ItemDoesntExistException;
import srv.SrvManager;

import java.io.IOException;
import java.util.*;

public class LoginController {
    private SrvManager srvManager;
    public VBox vboxMain;
    public TextField textFieldUsername;

    public void setSrvManager(SrvManager srvManager) {
        this.srvManager = srvManager;
        tryUpdate();
    }

    public void initialize() {

    }

    private void tryUpdate() {
        if (srvManager != null) {

        }
    }

    public void onLogInButtonClicked(ActionEvent actionEvent) {
        String username = textFieldUsername.getText();
        try {
            Client client = srvManager.getSrvClient().findClient(username);

            FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("flights-view.fxml"));
            Scene scene = null;
            try {
                scene = new Scene(fxmlLoader.load(), 320, 240);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

            FlightsController flightsController = fxmlLoader.getController();
            flightsController.setSrvManager(srvManager);
            flightsController.setClient(client);

            Stage stage = new Stage();
            stage.setTitle("Flights");
            stage.setScene(scene);
            stage.show();
        } catch (ItemDoesntExistException e) {
            // TODO: show error
            throw new RuntimeException(e);
        }
    }
}