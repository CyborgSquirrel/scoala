package gui;

import javafx.scene.Node;
import javafx.stage.Stage;

public class GuiUtils {
    public static Stage getStage(Node node) {
        return (Stage) node.getScene().getWindow();
    }
}
