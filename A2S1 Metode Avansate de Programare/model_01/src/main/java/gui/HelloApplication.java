package gui;

import domain.MenuItem;
import domain.Table;
import javafx.application.Application;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import repo.ItemAlreadyExistsException;
import repo.RepoMenuItem;
import repo.RepoOrder;
import repo.RepoTable;
import srv.SrvManager;
import srv.SrvMenuItem;
import srv.SrvOrder;
import srv.SrvTable;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        String url = "jdbc:postgresql://localhost:5432/01_model";
        String userName = "postgres";
        String password = "";

        // repo
        RepoMenuItem repoMenuItem = new RepoMenuItem(url, userName, password);
        RepoOrder repoOrder = new RepoOrder(url, userName, password);
        RepoTable repoTable = new RepoTable(url, userName, password);

        if (false) {
            try {
                repoMenuItem.store(new MenuItem(0, "Antreuri", "Bruschete cu rosii", 15, "RON"));
                repoMenuItem.store(new MenuItem(0, "Antreuri", "Salata Caprese", 20, "RON"));
                repoMenuItem.store(new MenuItem(0, "Fel Principal", "Paste cu sos pestu", 25, "RON"));
                repoMenuItem.store(new MenuItem(0, "Fel Principal", "Vinete parmigiana", 25, "RON"));
            } catch (ItemAlreadyExistsException e) {
                throw new RuntimeException(e);
            }
        }

        // srv
        SrvMenuItem srvMenuItem = new SrvMenuItem(repoMenuItem);
        SrvTable srvTable = new SrvTable(repoTable);
        SrvOrder srvOrder = new SrvOrder(repoOrder);

        // srv manager
        SrvManager srvManager = new SrvManager(srvMenuItem, srvTable, srvOrder);

        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("staff-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 320, 240);

        stage.setTitle("Staff");
        stage.setScene(scene);
        stage.show();

        StaffController staffController = fxmlLoader.getController();
        staffController.setSrvManager(srvManager);

        for (Table table : srvManager.getSrvTable().getAll()) {
            FXMLLoader fxmlLoader1 = new FXMLLoader();
            fxmlLoader1.setLocation(getClass().getResource("/gui/table-view.fxml"));

            Stage stage1 = new Stage();
            stage1.setTitle("Table " + Integer.toString(table.getId()));
            stage1.setScene(new Scene(fxmlLoader1.load(), 320, 240));
            stage1.show();

            TableController tableController = fxmlLoader1.getController();
            tableController.setSrvManager(srvManager);
            tableController.setTable(table);
        }
    }

    public static void main(String[] args) {
        launch();
    }
}