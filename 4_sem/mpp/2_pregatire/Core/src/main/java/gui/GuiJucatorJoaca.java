package gui;

import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.layout.VBox;
import srv.SrvApplication;
import srv.protocol.message.DTOClasamentItem;
import srv.protocol.message.DTOSfarsitJoc;
import srv.protocol.message.ResponseAlegePozitie;

import java.util.Arrays;

public class GuiJucatorJoaca {
    SrvApplication srvApplication;
    int jocId;

    boolean jocFinalizat = false;

    public VBox node_final;
    public Label label_indiciu;
    public Label label_pozitieIndiciu;
    public Label label_numarIncercariSau10;
    public Label label_pozitieClasament;

    public TableView<DTOClasamentItem> tableView;
    public TableColumn<DTOClasamentItem, String> tableColumn_alias;
    public TableColumn<DTOClasamentItem, String> tableColumn_inceput;
    public TableColumn<DTOClasamentItem, String> tableColumn_incercari;
    public TableColumn<DTOClasamentItem, String> tableColumn_indiciu;

    public void setSrvApplication(SrvApplication srvApplication) {
        this.srvApplication = srvApplication;
        trySubscribe();
    }

    private void trySubscribe() {
        if (srvApplication == null) return;

        srvApplication.subscribeOnJocSfarsit(() -> {
            if (jocFinalizat) {
                updateTable();
            }
        });
    }

    private void updateTable() {
        DTOClasamentItem[] clasament = srvApplication.getClasament();
        tableView.setItems(FXCollections.observableList(Arrays.stream(clasament).toList()));
    }

    public void setJocId(int jocId) {
        this.jocId = jocId;
    }

    public void initialize() {
        tableColumn_alias.setCellValueFactory(param -> new ReadOnlyStringWrapper(param.getValue().getAliasJucator()));
        tableColumn_inceput.setCellValueFactory(param -> new ReadOnlyStringWrapper(param.getValue().getTimestampInceput().toString()));
        tableColumn_incercari.setCellValueFactory(param -> new ReadOnlyStringWrapper(String.valueOf(param.getValue().getIncercari())));
        tableColumn_indiciu.setCellValueFactory(param -> new ReadOnlyStringWrapper(param.getValue().getIndiciu()));
    }

    private void button(ActionEvent actionEvent, int linie, int coloana) {
        if (jocFinalizat) return;

        ResponseAlegePozitie responseAlegePozitie = srvApplication.alegePozitie(jocId, linie, coloana);
        Button button = (Button) actionEvent.getSource();

        if (responseAlegePozitie.getDistanta() != null) {
            button.setText(responseAlegePozitie.getDistanta().toString());
        }

        if (responseAlegePozitie.getDtoSfarsitJoc() != null) {
            DTOSfarsitJoc dtoSfarsitJoc = responseAlegePozitie.getDtoSfarsitJoc();

            if (dtoSfarsitJoc.getIndiciu() != null) {
                label_indiciu.setText("Indiciu: " + dtoSfarsitJoc.getIndiciu());
            }
            label_pozitieIndiciu.setText("Pozitie indiciu: " + dtoSfarsitJoc.getLinieIndiciu() + " " + dtoSfarsitJoc.getColoanaIndiciu());
            label_pozitieClasament.setText("Pozitie clasament: " + dtoSfarsitJoc.getPozitieClasament());
            label_numarIncercariSau10.setText("Numar incercari: " + dtoSfarsitJoc.getNumarIncercariSau10());

            node_final.setVisible(true);
            jocFinalizat = true;
            updateTable();
        }
    }

    public void button00(ActionEvent actionEvent) {
        button(actionEvent, 0, 0);
    }

    public void button01(ActionEvent actionEvent) {
        button(actionEvent,0, 1);
    }

    public void button02(ActionEvent actionEvent) {
        button(actionEvent,0, 2);
    }

    public void button03(ActionEvent actionEvent) {
        button(actionEvent,0, 3);
    }

    public void button10(ActionEvent actionEvent) {
        button(actionEvent,1, 0);
    }

    public void button11(ActionEvent actionEvent) {
        button(actionEvent,1, 1);
    }

    public void button12(ActionEvent actionEvent) {
        button(actionEvent,1, 2);
    }

    public void button13(ActionEvent actionEvent) {
        button(actionEvent,1, 3);
    }

    public void button20(ActionEvent actionEvent) {
        button(actionEvent,2, 0);
    }

    public void button21(ActionEvent actionEvent) {
        button(actionEvent,2, 1);
    }

    public void button22(ActionEvent actionEvent) {
        button(actionEvent,2, 2);
    }

    public void button23(ActionEvent actionEvent) {
        button(actionEvent,2, 3);
    }

    public void button30(ActionEvent actionEvent) {
        button(actionEvent,3, 0);
    }

    public void button31(ActionEvent actionEvent) {
        button(actionEvent,3, 1);
    }

    public void button32(ActionEvent actionEvent) {
        button(actionEvent,3, 2);
    }

    public void button33(ActionEvent actionEvent) {
        button(actionEvent,3, 3);
    }
}
