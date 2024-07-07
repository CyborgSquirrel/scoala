package gui;

import domain.User;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import repo.exception.ItemDoesntExistException;
import service.ServiceFriendship;
import service.ServiceMessage;
import service.ServiceUser;

import java.io.IOException;

public class LogInController {
    private ServiceUser serviceUser;
    private ServiceFriendship serviceFriendship;
    private ServiceMessage serviceMessage;

    public TextField textFieldName;

    public void onButtonLogInClicked(ActionEvent actionEvent) {
        String name = textFieldName.getText();

        try {
            User user = serviceUser.findByName(name);
            Stage stage = (Stage)((Node) actionEvent.getSource()).getScene().getWindow();

            FXMLLoader fxmlLoader = new FXMLLoader();
            fxmlLoader.setLocation(getClass().getResource("/gui/logged_in.fxml"));
            try {
                Parent root = fxmlLoader.load();

                LoggedInController loggedInController = fxmlLoader.getController();
                loggedInController.setUser(user);
                loggedInController.setServiceUser(serviceUser);
                loggedInController.setServiceFriendship(serviceFriendship);
                loggedInController.setServiceMessage(serviceMessage);

                Scene scene = new Scene(root, Constants.sceneWidth, Constants.sceneHeight);
                stage.setScene(scene);
                stage.show();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        } catch (ItemDoesntExistException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR, "User not found.", ButtonType.CLOSE);
            alert.showAndWait();
            return;
        }
    }

    public void setServiceUser(ServiceUser serviceUser) {
        this.serviceUser = serviceUser;
    }

    public void setServiceFriendship(ServiceFriendship serviceFriendship) {
        this.serviceFriendship = serviceFriendship;
    }

    public void setServiceMessage(ServiceMessage serviceMessage) {
        this.serviceMessage = serviceMessage;
    }

    public void onLinkRegisterClicked(ActionEvent actionEvent) {
        Stage stage = (Stage)((Node) actionEvent.getSource()).getScene().getWindow();

        FXMLLoader fxmlLoader = new FXMLLoader();
        fxmlLoader.setLocation(getClass().getResource("/gui/register.fxml"));
        try {
            Parent root = fxmlLoader.load();

            RegisterController registerController = fxmlLoader.getController();
            registerController.setServiceUser(serviceUser);
            registerController.setServiceFriendship(serviceFriendship);
            registerController.setServiceMessage(serviceMessage);

            Scene scene = new Scene(root, Constants.sceneWidth, Constants.sceneHeight);
            stage.setScene(scene);
            stage.show();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}