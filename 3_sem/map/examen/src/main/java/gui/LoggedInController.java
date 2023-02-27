package gui;

import domain.Nevoie;
import domain.Persoana;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.util.Callback;
import srv.OnNevoieModified;
import srv.SrvManager;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.Arrays;

public class LoggedInController {
    public TableView<Nevoie> tableView1;
    public TableColumn<Nevoie, String> tableColumn1Titlu;
    public TableColumn<Nevoie, String> tableColumn1Descriere;
    public TableColumn<Nevoie, LocalDateTime> tableColumn1Deadline;
    public TableColumn<Nevoie, Long> tableColumn1OmInNevoie;
    public TableColumn<Nevoie, String> tableColumn1OmInNevoieUsername;
    public TableColumn<Nevoie, Long> tableColumn1OmSalvator;
    public TableColumn<Nevoie, String> tableColumn1OmSalvatorUsername;
    public TableColumn<Nevoie, String> tableColumn1Status;

    public TextField textFieldGetHelpTitlu;
    public TextField textFieldGetHelpDescriere;
    public DatePicker datePickerGetHelpDeadline;
    public TableView<Nevoie> tableView2;
    public TableColumn<Nevoie, String> tableColumn2Titlu;
    public TableColumn<Nevoie, LocalDateTime> tableColumn2Deadline;
    public TableColumn<Nevoie, String> tableColumn2Descriere;
    public TableColumn<Nevoie, Long> tableColumn2OmInNevoie;
    public TableColumn<Nevoie, String > tableColumn2OmInNevoieUsername;

    public Label labelPersoanaUsername;
    public Label labelPersoanaId;
    public Label labelPersoanaOras;

    private Persoana persoana;
    private SrvManager srvManager;

    OnNevoieModified onNevoieModified;

    public LoggedInController() {
        onNevoieModified = () -> {
            updateGoodDeeds();
            updateApplicableNevoi();
        };
    }

    public void setSrvManager(SrvManager srvManager) {
        this.srvManager = srvManager;
        tryUpdate();
    }

    public void setPersoana(Persoana persoana) {
        this.persoana = persoana;
        tryUpdate();
    }

    public void initialize() {
        tableColumn1Titlu.setCellValueFactory(new PropertyValueFactory<Nevoie, String>("titlu"));
        tableColumn1Descriere.setCellValueFactory(new PropertyValueFactory<Nevoie, String>("descriere"));
        tableColumn1Deadline.setCellValueFactory(new PropertyValueFactory<Nevoie, LocalDateTime>("deadline"));
        tableColumn1OmInNevoie.setCellValueFactory(new PropertyValueFactory<Nevoie, Long>("omInNevoie"));
        tableColumn1OmInNevoieUsername.setCellValueFactory(param -> new ReadOnlyStringWrapper(
                srvManager.getSrvPersoana().findPersoana(param.getValue().getOmInNevoie()).getUsername()
        ));
        tableColumn1OmSalvator.setCellValueFactory(new PropertyValueFactory<Nevoie, Long>("omSalvator"));
        tableColumn1OmSalvatorUsername.setCellValueFactory(param -> {
            Long omSalvatorId = param.getValue().getOmSalvator();
            if (omSalvatorId == null) return new ReadOnlyStringWrapper("");
            Persoana omSalvator = srvManager.getSrvPersoana().findPersoana(omSalvatorId);
            return new ReadOnlyStringWrapper(omSalvator.getUsername());
        });
        tableColumn1Status.setCellValueFactory(new PropertyValueFactory<Nevoie, String>("status"));

        tableColumn2Titlu.setCellValueFactory(new PropertyValueFactory<Nevoie, String>("titlu"));
        tableColumn2Descriere.setCellValueFactory(new PropertyValueFactory<Nevoie, String>("descriere"));
        tableColumn2Deadline.setCellValueFactory(new PropertyValueFactory<Nevoie, LocalDateTime>("deadline"));
        tableColumn2OmInNevoie.setCellValueFactory(new PropertyValueFactory<Nevoie, Long>("omInNevoie"));
        tableColumn2OmInNevoieUsername.setCellValueFactory(param -> new ReadOnlyStringWrapper(
                srvManager.getSrvPersoana().findPersoana(param.getValue().getOmInNevoie()).getUsername()
        ));

        tableView1.setRowFactory(new Callback<TableView<Nevoie>, TableRow<Nevoie>>() {
            public TableRow<Nevoie> call(TableView<Nevoie> tableview) {
                return new TableRow<Nevoie>() {
                    @Override
                    protected void updateItem(Nevoie item, boolean empty) {
                        super.updateItem(item, empty);

                        if (item == null || empty) {
                        } else {
                            setDisable(item.getOmSalvator() != null);
                        }
                    }
                };
            }
        });
    }

    private void tryUpdate() {
        updateApplicableNevoi();
        updateGoodDeeds();
        if (srvManager != null) {
            srvManager.getSrvNevoie().registerOnNevoieModified(onNevoieModified);
        }
        if (persoana != null) {
            labelPersoanaUsername.setText(persoana.getUsername());
            labelPersoanaId.setText(Long.toString(persoana.getId()));
            labelPersoanaOras.setText(persoana.getOras().toValue());
        }
    }

    private void updateApplicableNevoi() {
        if (srvManager != null && persoana != null) {
            Nevoie[] applicableNevoi = srvManager.getSrvNevoie().getApplicableNevoi(persoana.getOras(), persoana.getId());
            tableView1.setItems(FXCollections.observableList(Arrays.stream(applicableNevoi).toList()));
        }
    }

    private void updateGoodDeeds() {
        if (srvManager != null && persoana != null) {
            Nevoie[] goodDeeds = srvManager.getSrvNevoie().getGoodDeeds(persoana.getId());
            tableView2.setItems(FXCollections.observableList(Arrays.stream(goodDeeds).toList()));
        }
    }

    public void onButtonGetHelpAdaugaAction(ActionEvent actionEvent) {
        String titlu = textFieldGetHelpTitlu.getText();
        String descriere = textFieldGetHelpDescriere.getText();
        LocalDate deadline1 = datePickerGetHelpDeadline.getValue();

        boolean valid =
                titlu != null && !titlu.isEmpty()
                && descriere != null && !descriere.isEmpty()
                && deadline1 != null;

        if (valid) {
            LocalDateTime deadline = deadline1.atStartOfDay();
            srvManager.getSrvNevoie().addNevoie(
                    titlu,
                    descriere,
                    deadline,
                    persoana.getId()
            );
        } else {
            Alert alert = new Alert(Alert.AlertType.ERROR, "Nevoie invalida!", ButtonType.CLOSE);
            alert.showAndWait();
        }
    }

    public void onButtonHelpAlegeNevoieAction(ActionEvent actionEvent) {
        Nevoie nevoie = tableView1.getSelectionModel().getSelectedItem();
        if (nevoie != null && nevoie.getOmSalvator() == null) {
            srvManager.getSrvNevoie().assignNevoie(nevoie, persoana.getId());
            Alert alert = new Alert(Alert.AlertType.INFORMATION, "Nevoia aleasa v-a fost atribuita!", ButtonType.CLOSE);
            alert.showAndWait();
        }
    }
}