package gui;

import domain.Client;
import domain.Hotel;
import domain.Location;
import domain.SpecialOffer;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableRow;
import javafx.scene.control.TableView;
import javafx.stage.Stage;
import javafx.util.StringConverter;
import repo.ItemDoesntExistException;
import srv.SrvManager;

import java.io.IOException;
import java.util.Arrays;

public class ClientController {
    public TableView<SpecialOffer> tableViewSpecialOffers;
    public TableColumn<SpecialOffer, String> tableColumnSpecialOffersHotel;
    public TableColumn<SpecialOffer, String> tableColumnSpecialOffersLocation;
    public TableColumn<SpecialOffer, String> tableColumnSpecialOffersStartDate;
    public TableColumn<SpecialOffer, String> tableColumnSpecialOffersEndDate;
    private SrvManager srvManager;
    private Client client;

    public void setSrvManager(SrvManager srvManager) {
        this.srvManager = srvManager;
        tryUpdate();
    }

    public void setClient(Client client) {
        this.client = client;
        tryUpdate();
    }

    public void initialize() {
        tableColumnSpecialOffersHotel.setCellValueFactory(param -> {
            try {
                return new ReadOnlyStringWrapper(
                        srvManager.getSrvHotel().findHotel(param.getValue().getHotelId()).getName()
                );
            } catch (ItemDoesntExistException e) {
                throw new RuntimeException(e);
            }
        });
        tableColumnSpecialOffersLocation.setCellValueFactory(param -> {
            try {
                return new ReadOnlyStringWrapper(
                        srvManager.getSrvLocation().findLocation(srvManager.getSrvHotel().findHotel(param.getValue().getHotelId()).getLocationId()).getName()
                );
            } catch (ItemDoesntExistException e) {
                throw new RuntimeException(e);
            }
        });
        tableColumnSpecialOffersStartDate.setCellValueFactory(param -> new ReadOnlyStringWrapper(
                param.getValue().getStartDate().toString()
        ));
        tableColumnSpecialOffersEndDate.setCellValueFactory(param -> new ReadOnlyStringWrapper(
                param.getValue().getEndDate().toString()
        ));
    }

    private void tryUpdate() {
        if (srvManager != null && client != null) {
            SpecialOffer[] clientEligibleSpecialOffers = srvManager.getSrvSpecialOffer().getClientEligibleSpecialOffers(client);
            tableViewSpecialOffers.setItems(FXCollections.observableList(Arrays.stream(clientEligibleSpecialOffers).toList()));
        }
    }
}