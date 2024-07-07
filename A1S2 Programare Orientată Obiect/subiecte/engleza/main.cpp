#include "./srv.hpp"

#include <iostream>

#include <QApplication>
#include <QListView>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QAbstractListModel>

class NearbyReportsModel : public QAbstractListModel {
private:
	int m_driverId;
	const SrvDriver &m_srvDriver;
	const SrvReport &m_srvReport;
	
	std::vector<Report> m_nearbyReports;
	
	float m_radius;
public:
	void updateReports() {
		beginResetModel();
		auto driver = m_srvDriver.findDriver(m_driverId);
		m_nearbyReports = m_srvReport.getAllNear(driver.getLat(), driver.getLon(), m_radius);
		endResetModel();
	}
	
	NearbyReportsModel(int driverId, const SrvDriver &srvDriver, const SrvReport &srvReport)
	: m_driverId(driverId), m_srvDriver(srvDriver), m_srvReport(srvReport), m_radius(10)
	{
		updateReports();
	}
	
	void setRadius(float radius) {
		m_radius = radius;
		updateReports();
	}
	
	int rowCount(const QModelIndex &parent = QModelIndex()) const {
		return m_nearbyReports.size();
	}
	
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const {
		if (role == Qt::DisplayRole) {
			auto report = m_nearbyReports[index.row()];
			auto text = report.getReporter()
				+ " " + report.getDescription();
			return QVariant(QString::fromStdString(text));
		} else {
			return QVariant();
		}
	}
};

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	
	RepoDriver repoDriver("./drivers.txt");
	RepoReport repoReport("./reports.txt");
	
	SrvDriver srvDriver(repoDriver);
	SrvReport srvReport(repoReport, repoDriver);
	
	auto drivers = srvDriver.getAll();
	for (const auto &driver : drivers) {
		auto window = new QWidget;
		window->setWindowTitle(QString::fromStdString(driver.getName()));
		
		auto layout = new QVBoxLayout;
		window->setLayout(layout);
		
		auto labelStatus = new QLabel(QString::fromStdString(driverStatusToString(driver.getStatus())));
		layout->addWidget(labelStatus);
		auto labelLat = new QLabel(QString::number(driver.getLat()));
		layout->addWidget(labelLat);
		auto labelLon = new QLabel(QString::number(driver.getLon()));
		layout->addWidget(labelLon);
		auto labelScore = new QLabel(QString::number(driver.getScore()));
		layout->addWidget(labelScore);
		
		std::string windowColor = "white";
		DriverStatus status = driver.getStatus();
		if (status == DriverStatus::BABY) {
			windowColor = "green";
		} else if (status == DriverStatus::GROWNUP) {
			windowColor = "yellow";
		} else if (status == DriverStatus::KNIGHT) {
			windowColor = "red";
		}
		window->setStyleSheet(
			QString::fromStdString("QWidget { background: " + windowColor + "; }")
		);
		
		int id = driver.getId();
		auto buttonAddReport = new QPushButton("add report");
		QObject::connect(
			buttonAddReport, &QPushButton::clicked,
			[id, &srvDriver, &srvReport]() {
				auto windowAddReport = new QWidget;
				auto layout = new QFormLayout;
				windowAddReport->setLayout(layout);
				
				auto labelDescription = new QLabel("description");
				auto lineEditDescription = new QLineEdit;
				labelDescription->setBuddy(lineEditDescription);
				layout->addRow(labelDescription, lineEditDescription);
				
				auto labelLat = new QLabel("lat");
				auto lineEditLat = new QLineEdit;
				labelLat->setBuddy(lineEditLat);
				layout->addRow(labelLat, lineEditLat);
				
				auto labelLon = new QLabel("lon");
				auto lineEditLon = new QLineEdit;
				labelLon->setBuddy(lineEditLon);
				layout->addRow(labelLon, lineEditLon);
				
				auto buttonAdd = new QPushButton("add");
				QObject::connect(
					buttonAdd, &QPushButton::clicked,
					[id, &srvDriver, &srvReport, lineEditDescription, lineEditLat, lineEditLon]() {
						auto driver = srvDriver.findDriver(id);
						
						std::string description = lineEditDescription->text().toStdString();
						float lat = lineEditLat->text().toFloat();
						float lon = lineEditLon->text().toFloat();
						
						srvReport.addReport(driver, description, lat, lon);
					}
				);
				layout->addWidget(buttonAdd);
				
				windowAddReport->show();
			}
		);
		layout->addWidget(buttonAddReport);
		
		auto model = new NearbyReportsModel(id, srvDriver, srvReport);;
		auto view = new QListView;
		view->setModel(model);
		layout->addWidget(view);
		
		auto slider = new QSlider;
		slider->setMinimum(1);
		slider->setMaximum(50);
		slider->setOrientation(Qt::Horizontal);
		QObject::connect(
			slider, &QSlider::valueChanged,
			[model](int value) {
				model->setRadius(value);
			}
		);
		layout->addWidget(slider);
		
		auto layoutMovement = new QHBoxLayout;;
		auto buttonNorth = new QPushButton("north");
		QObject::connect(
			buttonNorth, &QPushButton::clicked,
			[id, &srvDriver, model]() {
				srvDriver.moveDriver(id, 0, 1);
				model->updateReports();
			}
		);
		layoutMovement->addWidget(buttonNorth);
		
		auto buttonEast = new QPushButton("east");
		QObject::connect(
			buttonEast, &QPushButton::clicked,
			[id, &srvDriver, model]() {
				srvDriver.moveDriver(id, 1, 0);
				model->updateReports();
			}
		);
		layoutMovement->addWidget(buttonEast);
		
		auto buttonSouth = new QPushButton("south");
		QObject::connect(
			buttonSouth, &QPushButton::clicked,
			[id, &srvDriver, model]() {
				srvDriver.moveDriver(id, 0, -1);
				model->updateReports();
			}
		);
		layoutMovement->addWidget(buttonSouth);
		
		auto buttonWest = new QPushButton("west");
		QObject::connect(
			buttonWest, &QPushButton::clicked,
			[id, &srvDriver, model]() {
				srvDriver.moveDriver(id, -1, 0);
				model->updateReports();
			}
		);
		layoutMovement->addWidget(buttonWest);
		layout->addLayout(layoutMovement);
		
		window->show();
	}
	
	return app.exec();
}
