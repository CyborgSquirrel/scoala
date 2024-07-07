package gui;

import domain.*;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import repo.*;
import srv.*;

import java.io.IOException;
import java.util.Arrays;
import java.util.Date;
import java.util.stream.Collectors;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        String url = "jdbc:postgresql://localhost:5432/02_model";
        String userName = "postgres";
        String password = "";

        // repo
        RepoClient repoClient = new RepoClient(url, userName, password);
        RepoHotel repoHotel = new RepoHotel(url, userName, password);
        RepoLocation repoLocation = new RepoLocation(url, userName, password);
        RepoReservation repoReservation = new RepoReservation(url, userName, password);
        RepoSpecialOffer repoSpecialOffer = new RepoSpecialOffer(url, userName, password);

        // srv
        SrvHotel srvHotel = new SrvHotel(repoHotel);
        SrvLocation srvLocation = new SrvLocation(repoLocation);
        SrvSpecialOffer srvSpecialOffer = new SrvSpecialOffer(repoSpecialOffer);
        SrvClient srvClient = new SrvClient(repoClient);

        // srv manager
        SrvManager srvManager = new SrvManager(srvLocation, srvHotel, srvSpecialOffer, srvClient);

        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("hotels-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 320, 240);

        stage.setTitle("Hotels");
        stage.setScene(scene);
        stage.show();

        HotelsController hotelsController = fxmlLoader.getController();
        hotelsController.setSrvManager(srvManager);

        Parameters parameters = getParameters();
        Client[] clients = Arrays.stream(parameters.getUnnamed().stream()
                        .collect(Collectors.joining())
                        .split(","))
                .map(Integer::valueOf)
                .map(id -> {
                    try {
                        return srvManager.getSrvClient().findClient(id);
                    } catch (ItemDoesntExistException e) {
                        throw new RuntimeException(e);
                    }
                }).toArray(Client[]::new);
        for (Client client : clients) {
            FXMLLoader fxmlLoader1 = new FXMLLoader(HelloApplication.class.getResource("client-view.fxml"));
            Scene scene1 = new Scene(fxmlLoader1.load(), 320, 240);

            Stage stage1 = new Stage();
            stage1.setTitle(client.getName());
            stage1.setScene(scene1);
            stage1.show();

            ClientController clientController = fxmlLoader1.getController();
            clientController.setSrvManager(srvManager);
            clientController.setClient(client);
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}