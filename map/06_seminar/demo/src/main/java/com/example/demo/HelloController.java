package com.example.demo;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.XYChart;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;

public class HelloController {
    @FXML
    public TextArea sussyText;
    @FXML
    public LineChart lineChartSussy;
    @FXML
    private Label welcomeText;
    @FXML
    private Button sussyButton;

    private XYChart.Series series = new XYChart.Series();
    private double btcPrice = 60000;
    private int btcIndex = 1;


    @FXML
    protected void initialize() {
        series.setName("stonks");
        lineChartSussy.getData().add(series);
    }

    @FXML
    protected void onHelloButtonClick() {
        welcomeText.setText("Welcome to JavaFX Application!");
        sussyButton.setText("Yeet 2.0");
        String text = sussyText.getText();
//        sussyText.setText(text + "nu mai vreu java\n");

        series.getData().add(new XYChart.Data<>(btcIndex, btcPrice));
        btcIndex += 1;
        btcPrice *= 0.95 + Math.random() * 0.03;
    }

    public void onSussyButtonClick(ActionEvent actionEvent) {
        series.getData().clear();
    }
}