package gui;

import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.TextField;
import domain.Jucator;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import srv.SrvApplication;

import java.io.IOException;

public class GuiJucatorStart {
    SrvApplication srvApplication;
    Jucator jucator;

    public VBox root;
    public TextField textField_cuvant;

    public void setSrvApplication(SrvApplication srvApplication) {
        this.srvApplication = srvApplication;
    }

    public void setJucator(Jucator jucator) {
        this.jucator = jucator;
    }

    public void onButtonStartJocAction(ActionEvent actionEvent) {
        FXMLLoader fxmlLoader = new FXMLLoader();
        fxmlLoader.setLocation(getClass().getResource("/gui/jucatorAsteapta.fxml"));
        try {
            Stage stage = (Stage) ((Node) actionEvent.getSource()).getScene().getWindow();
            Parent root = fxmlLoader.load();

            GuiJucatorAsteapta guiJucatorAsteapta = fxmlLoader.getController();
            guiJucatorAsteapta.setSrvApplication(srvApplication);
            guiJucatorAsteapta.setJucator(jucator);
            guiJucatorAsteapta.setJocId(srvApplication.getJocId());

            Scene scene = new Scene(root, GuiConstants.SCENE_WIDTH, GuiConstants.SCENE_HEIGHT);
            stage.setScene(scene);
            stage.show();

            String cuvant = textField_cuvant.getText();

            srvApplication.jucatorStart(jucator.getId(), cuvant);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public void onButtonLogOutAction(ActionEvent actionEvent) {
        srvApplication.logOut(jucator.getId());
        GuiUtils.getStage(root).close();
    }
}
