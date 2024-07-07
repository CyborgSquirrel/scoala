package gui;

import domain.Oras;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.util.StringConverter;
import srv.SrvManager;

import java.io.IOException;
import java.util.Arrays;

public class RegisterController {
    public TextField textFieldNume;
    public TextField textFieldPrenume;
    public TextField textFieldUsername;
    public TextField textFieldParola;
    public ComboBox<Oras> comboBoxOras;
    public TextField textFieldStrada;
    public TextField textFieldNumarStrada;
    public TextField textFieldTelefon;
    private SrvManager srvManager;
    public VBox vboxMain;

    public void setSrvManager(SrvManager srvManager) {
        this.srvManager = srvManager;
        tryUpdate();
    }

    public void initialize() {
        comboBoxOras.setConverter(
            new StringConverter<Oras>() {
                @Override
                public String toString(Oras oras) {
                    if (oras == null) {
                        return "";
                    } else {
                        return oras.toValue();
                    }
                }

                @Override
                public Oras fromString(String string) {
                    return null;
                }
            });

        comboBoxOras.setItems(FXCollections.observableList(Arrays.stream(Oras.values()).toList()));
    }

    private void tryUpdate() {
        if (srvManager != null) {

        }
    }

    public void onButtonRegisterAction(ActionEvent actionEvent) {
        String nume = textFieldNume.getText();
        String prenume = textFieldPrenume.getText();
        String username = textFieldUsername.getText();
        String parola = textFieldParola.getText();
        Oras oras = comboBoxOras.getValue();
        String strada = textFieldStrada.getText();
        String numarStrada = textFieldNumarStrada.getText();
        String telefon = textFieldTelefon.getText();

        boolean valid =
                nume != null && !nume.isEmpty()
                && prenume != null && !prenume.isEmpty()
                && username != null && !username.isEmpty()
                && parola != null && !parola.isEmpty()
                && oras != null
                && strada != null && !strada.isEmpty()
                && numarStrada != null && !numarStrada.isEmpty()
                && telefon != null && !telefon.isEmpty();

        if (valid) {
            srvManager.getSrvPersoana().register(
                nume, prenume, username, parola,
                oras, strada, numarStrada,
                telefon
            );
        } else {
            Alert alert = new Alert(Alert.AlertType.ERROR, "Date invalide!", ButtonType.CLOSE);
            alert.showAndWait();
        }
    }

    public void onHyperlinkLogInAction(ActionEvent actionEvent) {
        Stage stage = (Stage) vboxMain.getScene().getWindow();

        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("login-view.fxml"));
        Scene scene = null;
        try {
            scene = new Scene(fxmlLoader.load(), Util.WIDTH, Util.HEIGHT);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        stage.setScene(scene);
        stage.show();

        LogInController logInController = fxmlLoader.getController();
        logInController.setSrvManager(srvManager);
    }
}