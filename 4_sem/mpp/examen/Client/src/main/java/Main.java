import gui.GuiConstants;
import gui.GuiLogIn;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import repo.*;
import srv.SrvApplication;
import srv.SrvApplicationImpl;
import srv.SrvApplicationObjectProxy;

import java.io.IOException;

public class Main extends Application {
    public static void main(String[] args) {
        launch();
    }

    public void start(Stage primaryStage) {
//        RepoManager repoManager = new RepoManager();
//
//        SrvApplication srvApplication = new SrvApplicationImpl(repoManager.getRepoJucator(),
//                repoManager.getRepoJoc(),
//                repoManager.getRepoPozitie());

        SrvApplicationObjectProxy srvApplication = new SrvApplicationObjectProxy("localhost", 4100);

        FXMLLoader fxmlLoader = new FXMLLoader();
        fxmlLoader.setLocation(getClass().getResource("/gui/logIn.fxml"));
        try {
            Parent root = fxmlLoader.load();

            GuiLogIn guiLogIn = fxmlLoader.getController();
            guiLogIn.setSrvApplication(srvApplication);

            Scene scene = new Scene(root, GuiConstants.SCENE_WIDTH, GuiConstants.SCENE_HEIGHT);
            primaryStage.setScene(scene);
            primaryStage.show();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
