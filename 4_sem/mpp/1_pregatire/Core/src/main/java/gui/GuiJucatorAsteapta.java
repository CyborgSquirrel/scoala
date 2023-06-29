package gui;

import domain.Jucator;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import srv.SrvApplication;
import srv.protocol.message.UpdateStartJoc;

import java.io.IOException;

public class GuiJucatorAsteapta {
    SrvApplication srvApplication;
    Jucator jucator;
    Integer jocId;

    public VBox root;

    public void setSrvApplication(SrvApplication srvApplication) {
        this.srvApplication = srvApplication;
        tryRegisterOnJocStarted();
    }

    public void setJucator(Jucator jucator) {
        this.jucator = jucator;
    }

    public void setJocId(int jocId) {
        this.jocId = jocId;
        tryRegisterOnJocStarted();
    }

    private void tryRegisterOnJocStarted() {
        if (srvApplication == null) return;
        if (jocId == null) return;

        srvApplication.registerOnJocStarted(
            jocId,
            updateStartJoc -> {
                startJoc(updateStartJoc);
            }
        );
    }

    public void startJoc(UpdateStartJoc updateStartJoc) {
        FXMLLoader fxmlLoader = new FXMLLoader();
        fxmlLoader.setLocation(getClass().getResource("/gui/jucatorJoaca.fxml"));
        try {
            Stage stage = GuiUtils.getStage(root);
            Parent root = fxmlLoader.load();

            GuiJucatorJoaca guiJucatorJoaca = fxmlLoader.getController();
            guiJucatorJoaca.setSrvApplication(srvApplication);
            guiJucatorJoaca.setJucator(jucator);
            guiJucatorJoaca.setJocId(jocId);
            guiJucatorJoaca.processUpdateStartJoc(updateStartJoc);

            Scene scene = new Scene(root, GuiConstants.SCENE_WIDTH, GuiConstants.SCENE_HEIGHT);
            stage.setScene(scene);
            stage.show();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public void onButtonLogOutAction(ActionEvent actionEvent) {
        srvApplication.logOut(jucator.getId());
        GuiUtils.getStage(root).close();
    }
}
