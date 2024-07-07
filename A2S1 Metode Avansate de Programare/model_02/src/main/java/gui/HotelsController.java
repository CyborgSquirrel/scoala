package gui;

import domain.Hotel;
import domain.Location;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableRow;
import javafx.scene.control.TableView;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;
import javafx.util.StringConverter;
import repo.ItemDoesntExistException;
import srv.SrvManager;

import java.io.IOException;
import java.util.*;

public class HotelsController {
    public TableView<Hotel> tableViewHotels;
    public TableColumn<Hotel, String> tableColumnHotelsId;
    public TableColumn<Hotel, String> tableColumnHotelsName;
    public TableColumn<Hotel, String> tableColumnHotelsLocation;
    public TableColumn<Hotel, String> tableColumnHotelsNoRooms;
    public TableColumn<Hotel, String> tableColumnHotelsPricePerNight;
    public TableColumn<Hotel, String> tableColumnHotelsType;
    public ComboBox<Location> comboBoxLocation;
    private SrvManager srvManager;
    private Location hotelsLocation;

    public void setSrvManager(SrvManager srvManager) {
        this.srvManager = srvManager;
        tryUpdate();
    }

    public void initialize() {
        tableViewHotels.setRowFactory(param -> {
            TableRow<Hotel> row = new TableRow<>();
            row.setOnMouseClicked(event -> {
                Hotel item = row.getItem();
                if (item != null) {
                    if (item == tableViewHotels.getSelectionModel().getSelectedItem()) {
                        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("special-offer-view.fxml"));
                        Scene scene = null;
                        try {
                            scene = new Scene(fxmlLoader.load(), 320, 240);
                        } catch (IOException e) {
                            throw new RuntimeException(e);
                        }

                        SpecialOfferController specialOfferController = fxmlLoader.getController();
                        specialOfferController.setSrvManager(srvManager);
                        specialOfferController.setHotel(item);

                        Stage stage = new Stage();
                        stage.setTitle("Special Offers");
                        stage.setScene(scene);
                        stage.show();
                    }
                }
            });
            return row;
        });

        tableColumnHotelsId.setCellValueFactory(param -> new ReadOnlyStringWrapper(
                Integer.toString(param.getValue().getId())
        ));
        tableColumnHotelsName.setCellValueFactory(param -> new ReadOnlyStringWrapper(
                param.getValue().getName()
        ));
        tableColumnHotelsLocation.setCellValueFactory(param -> {
            try {
                return new ReadOnlyStringWrapper(
                        srvManager.getSrvLocation().findLocation(param.getValue().getLocationId()).getName()
                );
            } catch (ItemDoesntExistException e) {
                throw new RuntimeException(e);
            }
        });
        tableColumnHotelsNoRooms.setCellValueFactory(param -> new ReadOnlyStringWrapper(
                Integer.toString(param.getValue().getNoRooms())
        ));
        tableColumnHotelsPricePerNight.setCellValueFactory(param -> new ReadOnlyStringWrapper(
                Double.toString(param.getValue().getPricePerNight())
        ));
        tableColumnHotelsType.setCellValueFactory(param -> new ReadOnlyStringWrapper(
                param.getValue().getType().toString()
        ));

        comboBoxLocation.setConverter(new StringConverter<Location>() {
            @Override
            public String toString(Location object) {
                if (object == null) {
                    return null;
                } else {
                    return object.getName();
                }
            }

            @Override
            public Location fromString(String string) {
                return null;
            }
        });
    }

    private void tryUpdate() {
        if (srvManager != null) {
            updateHotels();
            comboBoxLocation.setItems(FXCollections.observableList(Arrays.stream(srvManager.getSrvLocation().getLocations()).toList()));
        }
    }

    private void updateHotels() {
        Hotel[] hotels = {};
        if (hotelsLocation != null) {
            hotels = Arrays.stream(srvManager.getSrvHotel().getHotels()).filter(hotel -> hotel.getLocationId() == hotelsLocation.getId()).toArray(Hotel[]::new);
        }
        tableViewHotels.setItems(FXCollections.observableList(Arrays.stream(hotels).toList()));
    }

    public void onLocationChanged(ActionEvent actionEvent) {
        hotelsLocation = comboBoxLocation.getValue();
        updateHotels();
    }
}