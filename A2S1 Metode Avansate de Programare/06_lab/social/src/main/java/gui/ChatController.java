package gui;

import domain.Message;
import domain.User;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.scene.control.*;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.Region;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import repo.exception.ItemDoesntExistException;
import service.ServiceMessage;
import service.ServiceUser;

import java.util.*;

class MessageListCell extends ListCell<Message> {
    private ServiceUser serviceUser;

    private Label labelUser;
    private Text textText;
    private Label labelTimestamp;

    private HBox containerInfo;
    private VBox containerContent;

    public MessageListCell(ListView<Message> listView, ServiceUser serviceUser) {
        super();

        this.serviceUser = serviceUser;

        labelUser = new Label();
        textText = new Text();
        textText.wrappingWidthProperty().bind(listView.widthProperty().subtract(35));
        labelTimestamp = new Label();
        Region spacer = new Region();
        HBox.setHgrow(spacer, Priority.ALWAYS);

        containerInfo = new HBox();
        containerContent = new VBox();

        containerInfo.getChildren().add(labelUser);
        containerInfo.getChildren().add(spacer);
        containerInfo.getChildren().add(labelTimestamp);

        containerContent.getChildren().add(containerInfo);
        containerContent.getChildren().add(textText);
    }

    @Override
    protected void updateItem(Message item, boolean empty) {
        super.updateItem(item, empty);
        if (item != null && !empty) {
            User user = null;
            try {
                user = serviceUser.findById(item.getSourceUserId());
            } catch (ItemDoesntExistException e) {
                // NOTE: This should never happen.
                throw new RuntimeException(e);
            }
            labelUser.setText(user.getName());
            labelTimestamp.setText(item.getTimestamp().format(Message.DATE_TIME_FORMATTER));
            textText.setText(item.getText());
            setGraphic(containerContent);
        } else {
            setGraphic(null);
        }
    }
}

public class ChatController {
    public ListView<Message> listView;
    public TextField textFieldMessageText;

    UUID sourceUserId;
    UUID destinationUserId;
    ServiceMessage serviceMessage;
    ServiceUser serviceUser;

    void initialize() {

    }

    public void setSourceUserId(UUID sourceUserId) {
        this.sourceUserId = sourceUserId;
        tryUpdate();
    }

    public void setDestinationUserId(UUID destinationUserId) {
        this.destinationUserId = destinationUserId;
        tryUpdate();
    }

    public void setServiceMessage(ServiceMessage serviceMessage) {
        this.serviceMessage = serviceMessage;
        tryUpdate();
    }

    public void setServiceUser(ServiceUser serviceUser) {
        this.serviceUser = serviceUser;
        listView.setCellFactory(list -> new MessageListCell(listView, serviceUser));
        tryUpdate();
    }

    public void tryUpdate() {
        if (sourceUserId != null && destinationUserId != null && serviceMessage != null && serviceUser != null) {
            updateListView();
        }
    }

    private void updateListView() {
        List<Message> messages = Arrays.stream(serviceMessage.getAll())
                .filter(message ->
                        (Objects.equals(message.getSourceUserId(), sourceUserId) && Objects.equals(message.getDestinationUserId(), destinationUserId))
                                || (Objects.equals(message.getSourceUserId(), destinationUserId) && Objects.equals(message.getDestinationUserId(), sourceUserId)))
                .sorted(Comparator.comparing(Message::getTimestamp))
                .toList();

        listView.setItems(FXCollections.observableList(messages));
    }

    public void onButtonSendClicked(ActionEvent actionEvent) {
        serviceMessage.send(sourceUserId, destinationUserId, textFieldMessageText.getText());
        textFieldMessageText.clear();
        tryUpdate();
    }
}
