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
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;
import service.ServiceFriendship;
import service.ServiceMessage;
import service.ServiceUser;
import util.valid.NameValidator;

import java.io.IOException;

public class RegisterController {
    public TextField textFieldName;
    private ServiceUser serviceUser;
    private ServiceFriendship serviceFriendship;
    private ServiceMessage serviceMessage;

    public void onButtonRegisterClicked(ActionEvent actionEvent) {
        NameValidator nameValidator = new NameValidator();
        String name = textFieldName.getText();
        nameValidator.validate(name);

        try {
            serviceUser.addUser(name);
        } catch (ItemAlreadyExistsException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR, "User already exists.", ButtonType.CLOSE);
            alert.showAndWait();
            return;
        }

        User user = null;
        try {
            user = serviceUser.findByName(name);
        } catch (ItemDoesntExistException e) {
            // NOTE: This should not be possible.
            throw new RuntimeException(e);
        }

        Stage stage = (Stage)((Node) actionEvent.getSource()).getScene().getWindow();

        FXMLLoader fxmlLoader = new FXMLLoader();
        fxmlLoader.setLocation(getClass().getResource("/gui/logged_in.fxml"));
        try {
            Parent root = fxmlLoader.load();

            LoggedInController loggedInController = fxmlLoader.getController();
            loggedInController.setServiceUser(serviceUser);
            loggedInController.setServiceFriendship(serviceFriendship);
            loggedInController.setUser(user);

            Scene scene = new Scene(root, Constants.sceneWidth, Constants.sceneHeight);
            stage.setScene(scene);
            stage.show();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public void onLinkLogInClicked(ActionEvent actionEvent) {
        Stage stage = (Stage)((Node) actionEvent.getSource()).getScene().getWindow();

        FXMLLoader fxmlLoader = new FXMLLoader();
        fxmlLoader.setLocation(getClass().getResource("/gui/log_in.fxml"));
        try {
            Parent root = fxmlLoader.load();

            LogInController logInController = fxmlLoader.getController();
            logInController.setServiceUser(serviceUser);
            logInController.setServiceFriendship(serviceFriendship);
            logInController.setServiceMessage(serviceMessage);

            Scene scene = new Scene(root, Constants.sceneWidth, Constants.sceneHeight);
            stage.setScene(scene);
            stage.show();
        } catch (IOException e) {
            throw new RuntimeException(e);
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
}
