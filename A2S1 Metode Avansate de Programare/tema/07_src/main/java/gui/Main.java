package gui;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import repo.friendship.RepoFriendship;
import repo.friendship.RepoFriendshipDB;
import repo.friendship.RepoFriendshipRequestDb;
import repo.friendship_request.RepoFriendshipRequest;
import repo.friendship_request.RepoFriendshipRequestInmem;
import repo.message.RepoMessage;
import repo.message.RepoMessageDb;
import repo.message.RepoMessageInmem;
import repo.user.RepoUser;
import repo.user.RepoUserDB;
import service.ServiceFriendship;
import service.ServiceMessage;
import service.ServiceUser;

import java.io.IOException;

public class Main extends Application {
    public static void main(String[] args) {
        launch();
    }

    @Override
    public void start(Stage stage) throws IOException {
        String url = "jdbc:postgresql://localhost:5432/social";
        String userName = "postgres";
        String password = "";

        // REPO
        RepoUser repoUser = new RepoUserDB(url, userName, password);
        RepoFriendship repoFriendship = new RepoFriendshipDB(url, userName, password);
        RepoFriendshipRequest repoFriendshipRequest = new RepoFriendshipRequestDb(url, userName, password);
        RepoMessage repoMessage = new RepoMessageDb(url, userName, password);

        // SERVICE
        ServiceUser serviceUser = new ServiceUser(repoUser, repoFriendship);
        ServiceFriendship serviceFriendship = new ServiceFriendship(repoUser, repoFriendship, repoFriendshipRequest);
        ServiceMessage serviceMessage = new ServiceMessage(repoUser, repoMessage);

        // UI
        FXMLLoader fxmlLoader = new FXMLLoader();
        fxmlLoader.setLocation(getClass().getResource("/gui/log_in.fxml"));
        Parent root = fxmlLoader.load();

        LogInController logInController = fxmlLoader.getController();
        logInController.setServiceUser(serviceUser);
        logInController.setServiceFriendship(serviceFriendship);
        logInController.setServiceMessage(serviceMessage);

        Scene scene = new Scene(root, Constants.sceneWidth, Constants.sceneHeight);
        stage.setTitle("Log in");
        stage.setScene(scene);
        stage.show();
    }
}