package gui;

import domain.Jucator;
import javafx.event.ActionEvent;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import srv.SrvApplication;
import srv.protocol.message.DTOClasamentItem;

public class GuiJucatorSfarsit {
    SrvApplication srvApplication;
    Jucator jucator;
    private DTOClasamentItem[] clasament;

    public VBox root;

    public Label label_jucator0Nume;
    public Label label_jucator0Punctaj;
    public Label label_jucator1Nume;
    public Label label_jucator1Punctaj;
    public Label label_jucator2Nume;
    public Label label_jucator2Punctaj;

    public Label[] labels_jucatorNume;
    public Label[] labels_jucatorPunctaj;

    public void initialize() {
        labels_jucatorNume = new Label[] {label_jucator0Nume, label_jucator1Nume, label_jucator2Nume};
        labels_jucatorPunctaj = new Label[] {label_jucator0Punctaj, label_jucator1Punctaj, label_jucator2Punctaj};
    }

    public void setClasament(DTOClasamentItem[] clasament) {
        this.clasament = clasament;
        tryUpdateClasament();
    }

    public void setSrvApplication(SrvApplication srvApplication) {
        this.srvApplication = srvApplication;
    }

    public void setJucator(Jucator jucator) {
        this.jucator = jucator;
    }

    private void tryUpdateClasament() {
        if (clasament == null) return;

        int index = 0;
        for (DTOClasamentItem DTOClasamentItem : clasament) {
            labels_jucatorNume[index].setText(DTOClasamentItem.getJucatorNume());
            labels_jucatorPunctaj[index].setText(String.valueOf(DTOClasamentItem.getPunctaj()));

            index += 1;
        }
    }

    public void onButtonLogOutAction(ActionEvent actionEvent) {
        srvApplication.logOut(jucator.getId());
        GuiUtils.getStage(root).close();
    }
}
