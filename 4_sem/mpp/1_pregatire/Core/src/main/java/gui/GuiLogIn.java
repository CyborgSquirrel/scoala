package gui;

import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import domain.Jucator;
import srv.CredentialeNevalideException;
import srv.SrvApplication;

import java.io.IOException;

public class GuiLogIn {
    SrvApplication srvApplication;

    public TextField textField_nume;
    public PasswordField passwordField_parola;

    public void onButtonLogInAction(ActionEvent actionEvent) {
        String nume = textField_nume.getText();
        String parola = passwordField_parola.getText();
        try {
            Jucator jucator = srvApplication.logIn(nume, parola);

            FXMLLoader fxmlLoader = new FXMLLoader();
            fxmlLoader.setLocation(getClass().getResource("/gui/jucatorStart.fxml"));
            try {
                Stage stage = new Stage();
                Parent root = fxmlLoader.load();

                GuiJucatorStart guiJucatorStart = fxmlLoader.getController();
                guiJucatorStart.setSrvApplication(srvApplication);
                guiJucatorStart.setJucator(jucator);

                Scene scene = new Scene(root, GuiConstants.SCENE_WIDTH, GuiConstants.SCENE_HEIGHT);
                stage.setScene(scene);
                stage.show();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        } catch (CredentialeNevalideException e) {
            throw new RuntimeException(e);
        }
    }

    public void setSrvApplication(SrvApplication srvApplication) {
        this.srvApplication = srvApplication;
    }
}
