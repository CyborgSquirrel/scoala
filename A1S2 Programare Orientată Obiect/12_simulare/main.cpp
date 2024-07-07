#include "./repo.hpp"
#include "./srv.hpp"

#include <iostream>

#include <QApplication>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QColor>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QString>
#include <QWidget>
#include <QListWidgetItem>

void addDeviceToList(QListWidget *list, const Device &device) {
	auto item = new QListWidgetItem;
	
	QColor colorCode = Qt::black;
	if (device.getColor() == DeviceColor::RED) {
		colorCode = Qt::red;
	} else if (device.getColor() == DeviceColor::BLUE) {
		colorCode = Qt::blue;
	} else if (device.getColor() == DeviceColor::BLACK) {
		colorCode = Qt::black;
	} else if (device.getColor() == DeviceColor::YELLOW) {
		colorCode = Qt::yellow;
	}
	
	std::string text = device.getModel() + " (" + std::to_string(device.getPrice()) + ")";
	// item->setText(QString::fromStdString(text));
	item->setData(Qt::UserRole, device.getId());
	
	item->setData(Qt::BackgroundRole, QBrush { colorCode, Qt::SolidPattern });
	
	auto widget = new QWidget;
	auto layout = new QFormLayout;
	widget->setLayout(layout);
	
	auto label = new QLabel(QString::fromStdString(text));
	auto button = new QPushButton;
	label->setBuddy(button);
	
	layout->addRow(label, button);
	layout->setSizeConstraint(QLayout::SetFixedSize);
	
	list->addItem(item);
	list->setItemWidget(item, widget);
	item->setSizeHint(widget->sizeHint());
}

enum SortingFunction {
	BY_MODEL, BY_YEAR, UNSORTED
};

class GraphicalUI {
private:
	SrvDevice &m_srvDevice;
	
	SortingFunction m_sortingFunction;
	
	QListWidget *m_listWidget;
public:
	void updateListWidget() {
		std::vector<Device> devices;
		if (m_sortingFunction == BY_MODEL) {
			devices = m_srvDevice.getSortedByModel();
		} else if (m_sortingFunction == BY_YEAR) {
			devices = m_srvDevice.getSortedByYear();
		} else if (m_sortingFunction == UNSORTED) {
			devices = m_srvDevice.getAll();
		}
		
		m_listWidget->clear();
		for (const auto &device : devices) {
			addDeviceToList(m_listWidget, device);
		}
	}
	
	GraphicalUI(SrvDevice &srvDevice) : m_srvDevice(srvDevice) {
		m_sortingFunction = SortingFunction::UNSORTED;
		
		auto window = new QWidget;
		auto layoutMain = new QHBoxLayout;
		window->setLayout(layoutMain);
		
		m_listWidget = new QListWidget;
		this->updateListWidget();
		layoutMain->addWidget(m_listWidget);
		
		auto layoutControls = new QVBoxLayout;
		layoutMain->addLayout(layoutControls);
		
		auto layoutEdits = new QFormLayout;
		layoutControls->addLayout(layoutEdits);
		
		auto labelModel = new QLabel("Model");
		auto lineEditModel = new QLineEdit;
		labelModel->setBuddy(lineEditModel);
		layoutEdits->addRow(labelModel, lineEditModel);
		
		auto labelYear = new QLabel("An");
		auto lineEditYear = new QLineEdit;
		labelYear->setBuddy(lineEditYear);
		layoutEdits->addRow(labelYear, lineEditYear);
		
		QObject::connect(
			m_listWidget, &QListWidget::currentItemChanged,
			[srvDevice, lineEditModel, lineEditYear](QListWidgetItem *current, QListWidgetItem *) {
				if (current != nullptr) {
					int id = current->data(Qt::UserRole).toInt();
					auto device = srvDevice.findById(id);
					lineEditModel->setText(QString::fromStdString(device.getModel()));
					lineEditYear->setText(QString::number(device.getYear()));
				}
			}
		);
		
		auto buttonSortareModel = new QPushButton("sortare model");
		QObject::connect(
			buttonSortareModel, &QPushButton::clicked,
			[this]() {
				this->m_sortingFunction = SortingFunction::BY_MODEL;
				this->updateListWidget();
			}
		);
		layoutControls->addWidget(buttonSortareModel);
		
		auto buttonSortareAn = new QPushButton("sortare an");
		QObject::connect(
			buttonSortareAn, &QPushButton::clicked,
			[this]() {
				this->m_sortingFunction = SortingFunction::BY_YEAR;
				this->updateListWidget();
			}
		);
		layoutControls->addWidget(buttonSortareAn);
		
		auto buttonNesortat = new QPushButton("nesortat");
		QObject::connect(
			buttonNesortat, &QPushButton::clicked,
			[this]() {
				this->m_sortingFunction = SortingFunction::UNSORTED;
				this->updateListWidget();
			}
		);
		layoutControls->addWidget(buttonNesortat);
		
		window->show();
	}
};

int main(int argc, char **argv) {
	test_device();
	test_repo_device();
	test_srv_device();
	
	auto repo = RepoDevice("./test.txt");
	auto srv = SrvDevice(repo);
	
	QApplication app(argc, argv);
	
	GraphicalUI graphicalUI(srv);
	
	return app.exec();
}
