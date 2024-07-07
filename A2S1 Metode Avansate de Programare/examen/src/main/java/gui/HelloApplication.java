package gui;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import repo.RepoNevoie;
import repo.RepoPersoana;
import srv.*;

import java.io.IOException;
import java.io.UTFDataFormatException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        String url = "jdbc:postgresql://localhost:5432/examen";
        String userName = "postgres";
        String password = "";

        // repo
        RepoPersoana repoPersoana = new RepoPersoana(url, userName, password);
        RepoNevoie repoNevoie = new RepoNevoie(url, userName, password);

        // srv
        SrvPersoana srvPersoana = new SrvPersoana(repoPersoana);
        SrvNevoie srvNevoie = new SrvNevoie(repoNevoie, repoPersoana);

        // srv manager
        SrvManager srvManager = new SrvManager(srvPersoana, srvNevoie);

        // fxml
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("register-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), Util.WIDTH, Util.HEIGHT);

        stage.setTitle("App");
        stage.setScene(scene);
        stage.show();

        RegisterController registerController = fxmlLoader.getController();
        registerController.setSrvManager(srvManager);
    }

    public static void main(String[] args) {
        launch(args);
    }
}