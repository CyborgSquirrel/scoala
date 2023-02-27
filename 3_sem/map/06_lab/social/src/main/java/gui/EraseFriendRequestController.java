package gui;

import domain.User;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.Region;
import repo.exception.ItemDoesntExistException;
import service.ServiceFriendship;
import service.ServiceUser;

import java.util.Arrays;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

class CustomListCell extends ListCell<User> {
    private User sourceUser;
    private EraseFriendRequestController eraseFriendRequestController;
    private User destinationUser;
    private ServiceFriendship serviceFriendship;

    private Label label;
    private Button button;
    private HBox content;

    public CustomListCell(EraseFriendRequestController eraseFriendRequestController, User sourceUser, ServiceFriendship serviceFriendship) {
        super();
        this.eraseFriendRequestController = eraseFriendRequestController;
        this.sourceUser = sourceUser;
        this.serviceFriendship = serviceFriendship;
        label = new Label();
        button = new Button();
        button.setText("erase");
        Region spacer = new Region();
        HBox.setHgrow(spacer, Priority.ALWAYS);
        content = new HBox();
        content.getChildren().add(label);
        content.getChildren().add(spacer);
        content.getChildren().add(button);
    }

    @Override
    protected void updateItem(User item, boolean empty) {
        super.updateItem(item, empty);
        if (item != null && !empty) {
            this.destinationUser = item;
            label.setText(item.getName());
            button.onActionProperty().set(event -> {
                try {
                    serviceFriendship.removeFriendshipRequest(sourceUser.getId(), destinationUser.getId());
                    eraseFriendRequestController.tryUpdate();
                } catch (ItemDoesntExistException e) {
                    throw new RuntimeException(e);
                }
            });
            setGraphic(content);
        } else {
            setGraphic(null);
        }
    }
}

public class EraseFriendRequestController {
    private ServiceUser serviceUser;
    private ServiceFriendship serviceFriendship;
    private User user;

    String listViewName = "";

    @FXML private TextField textFieldName;
    @FXML private ListView<User> listView;

    public void initialize() {

    }

    public void tryUpdate() {
        if (serviceUser != null && serviceFriendship != null && user != null) {
            updateListView();
            listView.setCellFactory(listView -> new CustomListCell(this, user, serviceFriendship));
        }
    }

    private void updateListView() {
        List<User> users = Arrays.stream(serviceUser.getUsers())
                .filter(user -> !Objects.equals(user.getId(), this.user.getId()))
                .filter(user -> !this.serviceFriendship.areFriends(this.user.getId(), user.getId()))
                .filter(user -> {
                    try {
                        this.serviceFriendship.getFriendshipRequest(this.user.getId(), user.getId());
                        return true;
                    } catch (ItemDoesntExistException e) {
                        return false;
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
}
