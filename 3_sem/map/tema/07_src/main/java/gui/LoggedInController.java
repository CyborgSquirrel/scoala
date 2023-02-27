package gui;

import domain.User;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;
import repo.exception.ItemDoesntExistException;
import service.ServiceFriendship;
import service.ServiceMessage;
import service.ServiceUser;

import java.io.IOException;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

public class LoggedInController {
    private ServiceUser serviceUser;
    private ServiceFriendship serviceFriendship;
    private ServiceMessage serviceMessage;
    private User user;

    @FXML private Label labelUserName;
    @FXML private ListView<User> listView;

    @FXML private Tab tabLoggedIn;

    @FXML private Tab tabChatList;
    @FXML private HBox chatList;
    @FXML private ChatListController chatListController;

    @FXML private Tab tabEraseRequest;
    @FXML private HBox eraseFriendRequest;
    @FXML private EraseFriendRequestController eraseFriendRequestController;


    @FXML private Tab tabMakeRequest;
    @FXML private HBox makeFriendRequest;
    @FXML private MakeFriendRequestController makeFriendRequestController;

    @FXML private Tab tabAcceptRequest;
    @FXML private HBox acceptFriendRequest;
    @FXML private AcceptFriendRequestController acceptFriendRequestController;

    public void initialize() {
        listView.setCellFactory(list -> new ListCell<User>(){
            @Override
            protected void updateItem(User item, boolean empty) {
                super.updateItem(item, empty);
                if (item == null) {
                    setText(null);
                } else {
                    setText(item.getName());
                }
            }
        });
    }

    public void tryUpdate() {
        if (serviceUser != null && serviceFriendship != null && user != null) {
            updateListView();
        }
    }

    public void setUser(User user) {
        this.user = user;
        labelUserName.setText(user.getName());
        makeFriendRequestController.setUser(user);
        acceptFriendRequestController.setUser(user);
        eraseFriendRequestController.setUser(user);
        chatListController.setUser(user);
        tryUpdate();
    }

    public void setServiceUser(ServiceUser serviceUser) {
        this.serviceUser = serviceUser;
        makeFriendRequestController.setServiceUser(serviceUser);
        acceptFriendRequestController.setServiceUser(serviceUser);
        eraseFriendRequestController.setServiceUser(serviceUser);
        chatListController.setServiceUser(serviceUser);
        tryUpdate();
    }

    public void setServiceFriendship(ServiceFriendship serviceFriendship) {
        this.serviceFriendship = serviceFriendship;
        makeFriendRequestController.setServiceFriendship(serviceFriendship);
        acceptFriendRequestController.setServiceFriendship(serviceFriendship);
        eraseFriendRequestController.setServiceFriendship(serviceFriendship);
        chatListController.setServiceFriendship(serviceFriendship);
        tryUpdate();
    }

    public void setServiceMessage(ServiceMessage serviceMessage) {
        this.serviceMessage = serviceMessage;
        chatListController.setServiceMessage(serviceMessage);
    }

    public void onLogOutButtonClicked(ActionEvent actionEvent) {
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

    private void updateListView() {
        List<User> users = Arrays.stream(serviceUser.getUsers())
                .filter(user -> !Objects.equals(user.getId(), this.user.getId()))
                .filter(user -> serviceFriendship.areFriends(user.getId(), this.user.getId()))
                .toList();

        listView.setItems(FXCollections.observableList(users));
    }

    public void onEraseFriendButtonClicked(ActionEvent actionEvent) {
        User selectedItem = listView.getSelectionModel().getSelectedItem();
        if (selectedItem == null) return;

        try {
            serviceFriendship.removeFriendship(user.getId(), selectedItem.getId());
        } catch (ItemDoesntExistException e) {
            throw new RuntimeException(e);
        }
        updateListView();
    }

    public void onLoggedInSelectionChanged(Event event) {
        if (tabLoggedIn.isSelected()) {
            tryUpdate();
        }
    }

    public void onMakeRequestSelectionChanged(Event event) {
        if (tabMakeRequest.isSelected()) {
            makeFriendRequestController.tryUpdate();
        }
    }

    public void onAcceptRequestSelectionChanged(Event event) {
        if (tabAcceptRequest.isSelected()) {
            acceptFriendRequestController.tryUpdate();
        }
    }

    public void onEraseRequestSelectionChanged(Event event) {
        if (tabEraseRequest.isSelected()) {
            eraseFriendRequestController.tryUpdate();
        }
    }

    public void onChatListSelectionChangead(Event event) {
        if (tabChatList.isSelected()) {
            chatListController.tryUpdate();
        }
    }
}
