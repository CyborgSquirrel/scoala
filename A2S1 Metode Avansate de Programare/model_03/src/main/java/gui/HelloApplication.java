package gui;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import repo.*;
import srv.*;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        String url = "jdbc:postgresql://localhost:5432/03_model";
        String userName = "postgres";
        String password = "";

        // repo
        RepoClient repoClient = new RepoClient(url, userName, password);
        RepoFlight repoFlight = new RepoFlight(url, userName, password);
        RepoTicket repoTicket = new RepoTicket(url, userName, password);

        // srv
        SrvClient srvClient = new SrvClient(repoClient);
        SrvFlight srvFlight = new SrvFlight(repoFlight);
        SrvTicket srvTicket = new SrvTicket(repoTicket);

        // srv manager
        SrvManager srvManager = new SrvManager(srvClient, srvFlight, srvTicket);

        // fxml
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("login-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 320, 240);

        stage.setTitle("Log in");
        stage.setScene(scene);
        stage.show();

        LoginController loginController = fxmlLoader.getController();
        loginController.setSrvManager(srvManager);
    }

    public static void main(String[] args) {
        launch(args);
    }
}