package gui;

import domain.Client;
import domain.Flight;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.scene.control.*;
import repo.ItemAlreadyExistsException;
import srv.OnTicketsModified;
import srv.SrvManager;

import java.time.LocalDate;
import java.util.Arrays;

public class FlightsController {
    public TableView<Flight> tableViewFlight;
    public TableColumn<Flight, String> tableColumnFlightDepartureTime;
    public TableColumn<Flight, String> tableColumnFlightLandingTime;
    public TableColumn<Flight, String> tableColumnFlightSeats;
    public ComboBox<String> comboBoxFrom;
    public ComboBox<String> comboBoxTo;
    public DatePicker datePickerDepartureDate;
    public Label labelPage;

    private SrvManager srvManager;
    private Client client;
    public Label labelUsername;

    int page = 1;

    private OnTicketsModified onTicketsModified;

    public FlightsController() {
        onTicketsModified = () -> {
            updateFlights();
        };
    }

    public void initialize() {
        tableColumnFlightDepartureTime.setCellValueFactory(param -> new ReadOnlyStringWrapper(
                param.getValue().getDepartureTime().toString()
        ));
        tableColumnFlightLandingTime.setCellValueFactory(param -> new ReadOnlyStringWrapper(
                param.getValue().getLandingTime().toString()
        ));
        tableColumnFlightSeats.setCellValueFactory(param -> new ReadOnlyStringWrapper(
                Integer.toString(param.getValue().getSeats() - srvManager.getSrvTicket().getRemainingSeats(param.getValue().getId()))
        ));
    }

    public void setSrvManager(SrvManager srvManager) {
        this.srvManager = srvManager;
        tryUpdate();
    }

    public void setClient(Client client) {
        this.client = client;
        tryUpdate();
    }

    void tryUpdate() {
        if (srvManager != null && client != null) {
            labelUsername.setText(client.getName());
            comboBoxFrom.setItems(FXCollections.observableList(srvManager.getSrvFlight().getFromSet().stream().toList()));
            comboBoxTo.setItems(FXCollections.observableList(srvManager.getSrvFlight().getToSet().stream().toList()));
            srvManager.getSrvTicket().registerOnTicketsModified(onTicketsModified);
        }
        updateFlights();
    }

    void updateFlights() {
        Flight[] flights = {};
        if (srvManager != null) {
            String from = comboBoxFrom.getValue();
            String to = comboBoxTo.getValue();
            LocalDate departureDate = datePickerDepartureDate.getValue();
            if (from != null && to != null && departureDate != null) {
                flights = srvManager.getSrvFlight().getFlightsFromToWithDepartureDate(from, to, departureDate);
            }
        }

        int pages = (flights.length + 4) / 5;
        page = Integer.min(page, pages);
        page = Integer.max(page, 1);

        flights = Arrays.stream(flights)
                .skip((page-1)*5)
                .limit(5)
                .toArray(Flight[]::new);

        tableViewFlight.setItems(FXCollections.observableList(Arrays.stream(flights).toList()));
        labelPage.setText(Integer.toString(page) + "/" + Integer.toString(pages));
    }

    public void onComboBoxFromAction(ActionEvent actionEvent) {
        updateFlights();
    }

    public void onComboBoxToAction(ActionEvent actionEvent) {
        updateFlights();
    }

    public void onDatePickerDepartureDateAction(ActionEvent actionEvent) {
        updateFlights();
    }

    public void onButtonBuyAction(ActionEvent actionEvent) {
        Flight selectedItem = tableViewFlight.getSelectionModel().getSelectedItem();
        if (selectedItem != null) {
            try {
                srvManager.getSrvTicket().purchaseTicket(client.getUsername(), selectedItem.getId());
            } catch (ItemAlreadyExistsException e) {
                // TODO: exception window
//                throw new RuntimeException(e);
            }
        }
    }

    public void onButtonNextAction(ActionEvent actionEvent) {
        page += 1;
        updateFlights();
    }

    public void onButtonPreviousAction(ActionEvent actionEvent) {
        page -= 1;
        updateFlights();
    }
}

