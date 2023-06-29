package gui;

import domain.Jucator;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import srv.SrvApplication;
import srv.protocol.message.DTOJucatorUpdate;
import srv.protocol.message.UpdateStartJoc;
import srv.protocol.message.DTOStartJocJucator;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class GuiJucatorJoaca {
    SrvApplication srvApplication;
    Jucator jucator;
    Integer jocId;

    public VBox root;

    public ToggleGroup radioGroup;

    public Label label_jucator0Nume;
    public Label label_jucator0Punctaj;
    public Label label_jucator0Cuvant;

    public RadioButton radioButton_jucator1Ghici;
    public Label label_jucator1Nume;
    public Label label_jucator1Punctaj;
    public Label label_jucator1Cuvant;

    public RadioButton radioButton_jucator2Ghici;
    public Label label_jucator2Nume;
    public Label label_jucator2Punctaj;
    public Label label_jucator2Cuvant;

    public ComboBox<String> comboBox_litera;
    public Button button_ghici;

    public Label[] labels_jucatorNume;
    public Label[] labels_jucatorPunctaj;
    public Label[] labels_jucatorCuvant;
    public String[] cuvinte;
    public int[] punctaje;
    public Map<Integer, Integer> jucatorIdToIndex;
    public Map<Integer, Integer> jucatorIndexToId;

    public void initialize() {
        labels_jucatorNume = new Label[] {label_jucator0Nume, label_jucator1Nume, label_jucator2Nume};
        labels_jucatorPunctaj = new Label[] {label_jucator0Punctaj, label_jucator1Punctaj, label_jucator2Punctaj};
        labels_jucatorCuvant = new Label[] {label_jucator0Cuvant, label_jucator1Cuvant, label_jucator2Cuvant};
        cuvinte = new String[] {"", "", ""};
        punctaje = new int[] {0, 0, 0};

        radioButton_jucator1Ghici.setUserData(1);
        radioButton_jucator2Ghici.setUserData(2);
    }

    public void setSrvApplication(SrvApplication srvApplication) {
        this.srvApplication = srvApplication;
        tryRegisterOnRundaSfarsit();
    }

    public void setJucator(Jucator jucator) {
        this.jucator = jucator;
    }

    public void setJocId(Integer jocId) {
        this.jocId = jocId;
        tryRegisterOnRundaSfarsit();
    }

    private void tryRegisterOnRundaSfarsit() {
        if (srvApplication == null) return;
        if (jocId == null) return;

        srvApplication.registerOnRundaSfarsit(
                jocId,
                updateSfarsitRunda -> {
                    for (DTOJucatorUpdate DTOJucatorUpdate : updateSfarsitRunda.getRundaJucatorUpdates()) {
                        int idPropunator = DTOJucatorUpdate.getPropunatorJucatorId();
                        int indexPropunator = jucatorIdToIndex.get(idPropunator);

                        int idGhicitor = DTOJucatorUpdate.getGhicitorJucatorId();
                        int indexGhicitor = jucatorIdToIndex.get(idGhicitor);

                        char litera = DTOJucatorUpdate.getLitera();
                        StringBuilder stringBuilder = new StringBuilder(cuvinte[indexPropunator]);
                        for (Integer position : DTOJucatorUpdate.getPositions()) {
                            stringBuilder.setCharAt(position, litera);
                        }

                        punctaje[indexGhicitor] += DTOJucatorUpdate.getPunctaj();
                        labels_jucatorPunctaj[indexGhicitor].setText(String.valueOf(punctaje[indexGhicitor]));

                        cuvinte[indexPropunator] = stringBuilder.toString();
                        labels_jucatorCuvant[indexPropunator].setText(cuvinte[indexPropunator]);
                    }

                    button_ghici.setDisable(false);
                }
        );

        srvApplication.registerOnJocSfarsit(
                jocId,
                updateSfarsitJoc -> {
                    FXMLLoader fxmlLoader = new FXMLLoader();
                    fxmlLoader.setLocation(getClass().getResource("/gui/jucatorSfarsit.fxml"));
                    try {
                        Stage stage = GuiUtils.getStage(root);
                        Parent root = fxmlLoader.load();

                        GuiJucatorSfarsit guiJucatorSfarsit = fxmlLoader.getController();
                        guiJucatorSfarsit.setClasament(updateSfarsitJoc.getClasament());
                        guiJucatorSfarsit.setJucator(jucator);
                        guiJucatorSfarsit.setSrvApplication(srvApplication);

                        Scene scene = new Scene(root, GuiConstants.SCENE_WIDTH, GuiConstants.SCENE_HEIGHT);
                        stage.setScene(scene);
                        stage.show();
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                }
        );
    }

    public void processUpdateStartJoc(UpdateStartJoc updateStartJoc) {
        jucatorIdToIndex = new HashMap<>();
        jucatorIndexToId = new HashMap<>();

        {
            int index = 0;
            jucatorIdToIndex.put(jucator.getId(), index);
            jucatorIndexToId.put(index, jucator.getId());
            index += 1;

            for (DTOStartJocJucator DTOStartJocJucator : updateStartJoc.getJucatori()) {
                int id = DTOStartJocJucator.getId();
                if (jucatorIdToIndex.containsKey(id)) {
                    continue;
                }

                jucatorIdToIndex.put(id, index);
                jucatorIndexToId.put(index, id);
                index += 1;
            }
        }

        for (DTOStartJocJucator DTOStartJocJucator : updateStartJoc.getJucatori()) {
            int id = DTOStartJocJucator.getId();
            int index = jucatorIdToIndex.get(id);
            labels_jucatorNume[index].setText(DTOStartJocJucator.getNume());
            labels_jucatorPunctaj[index].setText(String.valueOf(punctaje[index]));
            StringBuilder cuvant = new StringBuilder();
            for (int i = 0; i < DTOStartJocJucator.getCuvantLungime(); ++i) {
                cuvant.append("_");
            }
            cuvinte[index] = cuvant.toString();
            labels_jucatorCuvant[index].setText(cuvinte[index]);
        }
    }

    public void onButtonGhiciAction(ActionEvent actionEvent) {
        String literaObject = (String) comboBox_litera.getValue();
        if (literaObject == null) {
            return;
        }
        char litera = literaObject.charAt(0);

        Toggle toggleGhici = radioGroup.getSelectedToggle();
        if (toggleGhici == null) {
            return;
        }
        int ghicitorJucatorIndex = (Integer) toggleGhici.getUserData();
        int ghicitorJucatorId = jucatorIndexToId.get(ghicitorJucatorIndex);

        button_ghici.setDisable(true);
        srvApplication.jucatorGhiceste(jocId, jucator.getId(), ghicitorJucatorId, litera);
    }

    public void onButtonLogOutAction(ActionEvent actionEvent) {
        srvApplication.logOut(jucator.getId());
        GuiUtils.getStage(root).close();
    }
}
