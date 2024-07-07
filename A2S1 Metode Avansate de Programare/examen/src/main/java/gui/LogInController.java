package gui;

import domain.Oras;
import domain.Persoana;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextField;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.util.StringConverter;
import srv.SrvManager;

import java.io.IOException;
import java.util.Arrays;
import java.util.Set;

public class LogInController {
    public ComboBox<Persoana> comboBoxUsername;
    private SrvManager srvManager;
    public VBox vboxMain;

    public void setSrvManager(SrvManager srvManager) {
        this.srvManager = srvManager;
        tryUpdate();
    }

    public void initialize() {
        comboBoxUsername.setConverter(
                new StringConverter<Persoana>() {
                    @Override
                    public String toString(Persoana persoana) {
                        if (persoana == null) {
                            return "";
                        } else {
                            return persoana.getUsername();
                        }
                    }

                    @Override
                    public Persoana fromString(String string) {
                        return null;
                    }
                });;
    }

    private void tryUpdate() {
        if (srvManager != null) {
            Persoana[] persoane = srvManager.getSrvPersoana().getPersoane();
            comboBoxUsername.setItems(FXCollections.observableList(Arrays.stream(persoane).toList()));
        }
    }

    public void onHyperlinkRegisterAction(ActionEvent actionEvent) {
        Stage stage = (Stage) vboxMain.getScene().getWindow();

        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("register-view.fxml"));
        Scene scene = null;
        try {
            scene = new Scene(fxmlLoader.load(), Util.WIDTH, Util.HEIGHT);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        stage.setScene(scene);
        stage.show();

        RegisterController registerController = fxmlLoader.getController();
        registerController.setSrvManager(srvManager);
    }

    public void onComboBoxUsernameAction(ActionEvent actionEvent) {
        Persoana persoana = comboBoxUsername.getValue();
        if (persoana != null) {
            Stage stage = new Stage();

            FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("logged-in-view.fxml"));
            Scene scene = null;
            try {
                scene = new Scene(fxmlLoader.load(), Util.WIDTH, Util.HEIGHT);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

            stage.setScene(scene);
            stage.show();

            LoggedInController loggedInController = fxmlLoader.getController();
            loggedInController.setSrvManager(srvManager);
            loggedInController.setPersoana(persoana);
        }
    }
}