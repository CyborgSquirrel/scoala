package gui;

import domain.DTOPozitie;
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
    public Label label_punctaj;
    public Label label_gropi;
    public Label label_pozitieClasament;

    public TableView<DTOClasamentItem> tableView;
    public TableColumn<DTOClasamentItem, String> tableColumn_alias;
    public TableColumn<DTOClasamentItem, String> tableColumn_punctaj;
    public TableColumn<DTOClasamentItem, String> tableColumn_durataSecunde;

    public void setSrvApplication(SrvApplication srvApplication) {
        this.srvApplication = srvApplication;
        trySubscribe();
        tryUpdateTable();
    }

    private void tryUpdateTable() {
        if (srvApplication == null) return;

        updateTable();
    }

    private void trySubscribe() {
        if (srvApplication == null) return;

        srvApplication.subscribeOnJocSfarsit(() -> {
            updateTable();
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
        tableColumn_durataSecunde.setCellValueFactory(param -> new ReadOnlyStringWrapper(String.valueOf(param.getValue().getDurataSecunde())));
        tableColumn_punctaj.setCellValueFactory(param -> new ReadOnlyStringWrapper(String.valueOf(param.getValue().getPuncte())));
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

            label_punctaj.setText("Punctaj: " + dtoSfarsitJoc.getPunctaj());
            label_pozitieClasament.setText("Pozitie clasament: " + dtoSfarsitJoc.getPozitieClasament());

            StringBuilder gropiBuilder = new StringBuilder();
            {
                boolean needsComma = false;
                for (DTOPozitie dtoPozitie : dtoSfarsitJoc.getGropi()) {
                    if (needsComma) {
                        gropiBuilder.append(", ");
                    } else {
                        needsComma = true;
                    }
                    gropiBuilder
                            .append("(")
                            .append(dtoPozitie.getLinie()+1)
                            .append(", ")
                            .append(dtoPozitie.getColoana()+1)
                            .append(")");
                }
            }
            String gropi = gropiBuilder.toString();
            label_gropi.setText("Gropi: " + gropi);

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
