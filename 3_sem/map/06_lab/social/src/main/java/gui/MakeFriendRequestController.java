package gui;

import domain.User;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyEvent;
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;
import service.ServiceFriendship;
import service.ServiceUser;

import java.util.Arrays;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

public class MakeFriendRequestController {
    private ServiceUser serviceUser;
    private ServiceFriendship serviceFriendship;
    private User user;

    private String listViewName = "";
    public ListView<User> listView;
    public TextField textFieldName;

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

    private void updateListView() {
        List<User> users = Arrays.stream(serviceUser.getUsers())
                .filter(user -> !Objects.equals(user.getId(), this.user.getId()))
                .filter(user -> !this.serviceFriendship.areFriends(this.user.getId(), user.getId()))
                .filter(user -> {
                    try {
                        this.serviceFriendship.getFriendshipRequest(this.user.getId(), user.getId());
                        return false;
                    } catch (ItemDoesntExistException e) {
                        return true;
                    }
                })
                .filter(user -> user.getName().contains(listViewName))
                .collect(Collectors.toList());

        listView.setItems(FXCollections.observableList(users));
    }

    public void onFriendNameTyped(KeyEvent keyEvent) {
        listViewName = textFieldName.getText();
        updateListView();
    }

    public void setServiceUser(ServiceUser serviceUser) {
        this.serviceUser = serviceUser;
        tryUpdate();
    }

    public void setServiceFriendship(ServiceFriendship serviceFriendship) {
        this.serviceFriendship = serviceFriendship;
        tryUpdate();
    }

    public void setUser(User user) {
        this.user = user;
        tryUpdate();
    }

    public void onAddFriendButtonClicked(ActionEvent actionEvent) {
        User selectedItem = listView.getSelectionModel().getSelectedItem();
        if (selectedItem == null) return;
        try {
            serviceFriendship.makeFriendshipRequest(user.getId(), selectedItem.getId());
            updateListView();
        } catch (ItemAlreadyExistsException e) {
            // NOTE: This exception should not happen here.
        }
    }
}
