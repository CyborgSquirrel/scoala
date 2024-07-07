package gui;

import domain.User;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.VBox;
import service.ServiceFriendship;
import service.ServiceMessage;
import service.ServiceUser;

import java.util.Arrays;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

public class ChatListController {
    @FXML private VBox chat;
    @FXML private ChatController chatController;

    private User user;
    private ServiceUser serviceUser;
    private ServiceFriendship serviceFriendship;
    private ServiceMessage serviceMessage;

    public ListView<User> listView;

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

    public void setServiceUser(ServiceUser serviceUser) {
        this.serviceUser = serviceUser;
        this.chatController.setServiceUser(serviceUser);
        tryUpdate();
    }

    public void setServiceFriendship(ServiceFriendship serviceFriendship) {
        this.serviceFriendship = serviceFriendship;
        tryUpdate();
    }

    public void setUser(User user) {
        this.user = user;
        this.chatController.setSourceUserId(user.getId());
        tryUpdate();
    }

    public void setServiceMessage(ServiceMessage serviceMessage) {
        this.serviceMessage = serviceMessage;
        this.chatController.setServiceMessage(serviceMessage);
        tryUpdate();
    }

    public void tryUpdate() {
        if (serviceUser != null && serviceFriendship != null && user != null) {
            updateListView();
        }
    }

    private void updateListView() {
        List<User> users = Arrays.stream(serviceUser.getUsers())
                .filter(user -> !Objects.equals(user.getId(), this.user.getId()))
                .filter(user -> serviceFriendship.areFriends(user.getId(), this.user.getId()))
                .collect(Collectors.toList());

        listView.setItems(FXCollections.observableList(users));
    }

    public void onListViewMouseClicked(MouseEvent mouseEvent) {
        User selectedItem = listView.getSelectionModel().getSelectedItem();
        if (selectedItem == null) return;

        chatController.setDestinationUserId(selectedItem.getId());
        chat.setVisible(true);
    }
}
