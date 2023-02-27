package gui;

import domain.FriendshipRequest;
import domain.User;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.scene.control.*;
import javafx.scene.input.KeyEvent;
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;
import service.ServiceFriendship;
import service.ServiceUser;

import java.util.Arrays;
import java.util.List;

class TableViewRow {
    User user;

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public FriendshipRequest getFriendshipRequest() {
        return friendshipRequest;
    }

    public void setFriendshipRequest(FriendshipRequest friendshipRequest) {
        this.friendshipRequest = friendshipRequest;
    }

    FriendshipRequest friendshipRequest;

    public TableViewRow(User user, FriendshipRequest friendshipRequest) {
        this.user = user;
        this.friendshipRequest = friendshipRequest;
    }
}

public class AcceptFriendRequestController {
    public TableView<TableViewRow> tableView;
    public TableColumn<TableViewRow, String> tableView_name;
    public TableColumn<TableViewRow, String> tableView_createdTime;
    private ServiceUser serviceUser;
    private User user;

    private ServiceFriendship serviceFriendship;

    public TextField textFieldName;
    private String listViewName = "";

    public void initialize() {
        tableView_name.setCellValueFactory(cell -> {
            String name = cell.getValue().getUser().getName();
            return new SimpleStringProperty(name);
        });

        tableView_createdTime.setCellValueFactory(cell -> {
            String name = cell.getValue().getFriendshipRequest().getCreatedTime().format(FriendshipRequest.DATE_TIME_FORMATTER);
            return new SimpleStringProperty(name);
        });
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

    public void tryUpdate() {
        if (serviceUser != null && serviceFriendship != null && user != null) {
            updateListView();
        }
    }

    private void updateListView() {
        List<TableViewRow> tableViewRows = Arrays.stream(serviceUser.getUsers())
                .map(user -> {
                    try {
                        return new TableViewRow(user, serviceFriendship.getFriendshipRequest(user.getId(), this.user.getId()));
                    } catch (ItemDoesntExistException e) {
                        return null;
                    }
                })
                .filter(tableViewRow -> tableViewRow != null)
                .filter(tableViewRow -> tableViewRow.getUser().getName().contains(listViewName))
                .toList();

        tableView.setItems(FXCollections.observableList(tableViewRows));
    }

    public void onFriendNameTyped(KeyEvent keyEvent) {
        listViewName = textFieldName.getText();
        updateListView();
    }

    public void onAcceptFriendButtonClicked(ActionEvent actionEvent) {
        User selectedItem = tableView.getSelectionModel().getSelectedItem().getUser();
        if (selectedItem == null) return;

        try {
            serviceFriendship.acceptFriendshipRequest(selectedItem.getId(), user.getId());
        } catch (ItemDoesntExistException | ItemAlreadyExistsException e) {
            throw new RuntimeException(e);
        }
        updateListView();
    }
}
