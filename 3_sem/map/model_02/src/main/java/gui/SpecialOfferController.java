package gui;

import domain.Hotel;
import domain.SpecialOffer;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.scene.control.DatePicker;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import srv.SrvManager;

import java.time.LocalDate;
import java.time.ZoneId;
import java.util.Arrays;
import java.util.Date;

public class SpecialOfferController {
    public TextField textFieldClientId;
    public DatePicker datePickerStartDateDingus;
    public TextField textFieldNoNights;
    SrvManager srvManager;
    Hotel hotel;

    public TableView<SpecialOffer> tableViewSpecialOffer;
    public TableColumn<SpecialOffer, String> tableColumnSpecialOfferStartDate;
    public TableColumn<SpecialOffer, String> tableColumnSpecialOfferEndDate;
    public TableColumn<SpecialOffer, String> tableColumnSpecialOfferPercents;
    public DatePicker datePickerStartDate;
    public DatePicker datePickerEndDate;
    private LocalDate startDate;
    private LocalDate endDate;

    public void setSrvManager(SrvManager srvManager) {
        this.srvManager = srvManager;
    }

    public void setHotel(Hotel hotel) {
        this.hotel = hotel;
    }

    public void initialize() {
        tableColumnSpecialOfferStartDate.setCellValueFactory(param -> new ReadOnlyStringWrapper(
                param.getValue().getStartDate().toString()
        ));
        tableColumnSpecialOfferEndDate.setCellValueFactory(param -> new ReadOnlyStringWrapper(
                param.getValue().getEndDate().toString()
        ));
        tableColumnSpecialOfferPercents.setCellValueFactory(param -> new ReadOnlyStringWrapper(
                Integer.toString(param.getValue().getPercents())
        ));
    }

    private void updateSpecialOffers() {
        SpecialOffer[] specialOffers = {};
        if (startDate != null && endDate != null) {
            specialOffers = srvManager.getSrvSpecialOffer()
                    .getSpecialOffersInRangeForHotel(
                            hotel.getId(),
                            Date.from(startDate.atStartOfDay(ZoneId.systemDefault()).toInstant()),
                            Date.from(endDate.atStartOfDay(ZoneId.systemDefault()).toInstant()));
        }
        tableViewSpecialOffer.setItems(FXCollections.observableList(Arrays.stream(specialOffers).toList()));
    }

    public void onStartDateChanged(ActionEvent actionEvent) {
        startDate = datePickerStartDate.getValue();
        updateSpecialOffers();
    }

    public void onEndDateChanged(ActionEvent actionEvent) {
        endDate = datePickerEndDate.getValue();
        updateSpecialOffers();
    }
}
