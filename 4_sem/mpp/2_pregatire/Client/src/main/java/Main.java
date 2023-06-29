import domain.Configuratie;
import gui.GuiConstants;
import gui.GuiLogIn;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.hibernate.SessionFactory;
import org.hibernate.boot.MetadataSources;
import org.hibernate.boot.registry.StandardServiceRegistry;
import org.hibernate.boot.registry.StandardServiceRegistryBuilder;
import repo.*;
import srv.SrvApplication;
import srv.SrvApplicationImpl;

import java.io.Console;
import java.io.FileReader;
import java.io.IOException;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

public class Main extends Application {
    public static void main(String[] args) {
        launch();
    }

    public void start(Stage primaryStage) {
        RepoManager repoManager = new RepoManager();

        RepoConfiguratie repoConfiguratie = repoManager.getRepoConfiguratie();

        try {
            repoConfiguratie.store(new Configuratie(1, 1, "dingus"));
        } catch (IdAlreadyExistsException e) {
            throw new RuntimeException(e);
        }
        try {
            System.out.println(repoConfiguratie.find(1));
        } catch (IdNotFoundException e) {
            throw new RuntimeException(e);
        }
        for (Configuratie configuratie : repoConfiguratie.getAll()) {
            System.out.println(configuratie);
        }
        try {
            repoConfiguratie.update(1, new Configuratie(0, 0, "asdf"));
        } catch (IdNotFoundException e) {
            throw new RuntimeException(e);
        }
        try {
            repoConfiguratie.remove(4);
        } catch (IdNotFoundException e) {
            throw new RuntimeException(e);
        }


//        SrvApplication srvApplication = new SrvApplicationImpl(repoManager.getRepoJucator(),
//                repoManager.getRepoJoc(),
//                repoManager.getRepoConfiguratie());


//        SrvApplicationObjectProxy srvApplication = new SrvApplicationObjectProxy("localhost", 4100);

//        FXMLLoader fxmlLoader = new FXMLLoader();
//        fxmlLoader.setLocation(getClass().getResource("/gui/logIn.fxml"));
//        try {
//            Parent root = fxmlLoader.load();
//
//            GuiLogIn guiLogIn = fxmlLoader.getController();
//            guiLogIn.setSrvApplication(srvApplication);
//
//            Scene scene = new Scene(root, GuiConstants.SCENE_WIDTH, GuiConstants.SCENE_HEIGHT);
//            primaryStage.setScene(scene);
//            primaryStage.show();
//        } catch (IOException e) {
//            throw new RuntimeException(e);
//        }
    }
}
