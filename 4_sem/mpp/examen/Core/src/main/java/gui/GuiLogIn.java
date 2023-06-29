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
import srv.protocol.message.ResponseStartJoc;

import java.io.IOException;

public class GuiLogIn {
    SrvApplication srvApplication;

    public TextField textField_alias;
    public PasswordField passwordField_parola;

    public void onButtonLogInAction(ActionEvent actionEvent) {
        String alias = textField_alias.getText();
        try {
            ResponseStartJoc responseStartJoc = srvApplication.startJoc(alias);

            FXMLLoader fxmlLoader = new FXMLLoader();
            fxmlLoader.setLocation(getClass().getResource("/gui/jucatorJoaca.fxml"));
            try {
                Stage stage = new Stage();
                Parent root = fxmlLoader.load();

                GuiJucatorJoaca guiJucatorJoaca = fxmlLoader.getController();
                guiJucatorJoaca.setSrvApplication(srvApplication);
                guiJucatorJoaca.setJocId(responseStartJoc.getJocId());

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
