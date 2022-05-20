#include "./graphical_ui.hpp"

#include <iostream>

#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>

QListWidgetItem *orderToListWidgetItem(const Order &order) {
	std::string status = "pending";
	QColor color = Qt::gray;
	if (order.getStatus() == Status::PENDING) {
		status = "pending";
		color = Qt::gray;
	} if (order.getStatus() == Status::CONFIRMED) {
		status = "confirmed";
		color = Qt::blue;
	} if (order.getStatus() == Status::CANCELLED) {
		status = "cancelled";
		color = Qt::red;
	} if (order.getStatus() == Status::DELIVERED) {
		status = "delivered";
		color = Qt::green;
	} 
	
	std::string text = std::to_string(order.getNumber()) + ", " + order.getObject() + ", " + status;
	
	auto item = new QListWidgetItem;
	item->setData(Qt::UserRole, QVariant(order.getId()));
	item->setText(QString::fromStdString(text));
	item->setBackground(QBrush {color});
	
	return item;
}

void GraphicalUI::updateList() {
	m_list->clear();
	
	std::vector<Order> orders;
	if (m_listFilter == ListFilter::UNFILTERED) {
		orders = m_srv.getOrders();
	} else if (m_listFilter == ListFilter::BY_PENDING) {
		orders = m_srv.getOrdersFilteredByStatus(Status::PENDING);
	} else if (m_listFilter == ListFilter::BY_CONFIRMED) {
		orders = m_srv.getOrdersFilteredByStatus(Status::CONFIRMED);
	} else if (m_listFilter == ListFilter::BY_CANCELLED) {
		orders = m_srv.getOrdersFilteredByStatus(Status::CANCELLED);
	} else if (m_listFilter == ListFilter::BY_DELIVERED) {
		orders = m_srv.getOrdersFilteredByStatus(Status::DELIVERED);
	}
	
	for (const auto &order : orders) {
		m_list->addItem(orderToListWidgetItem(order));
	}
}

GraphicalUI::GraphicalUI(SrvOrder &srv) : m_srv(srv) {
	m_listFilter = ListFilter::UNFILTERED;
	
	auto window = new QWidget;
	auto layoutMain = new QHBoxLayout;
	window->setLayout(layoutMain);
	
	m_list = new QListWidget;
	updateList();
	layoutMain->addWidget(m_list);
	
	auto layoutControls = new QVBoxLayout;
	layoutMain->addLayout(layoutControls);
	
	auto layoutUpdate = new QFormLayout;
		auto labelNumber = new QLabel("&Number");
		auto editNumber = new QLineEdit;
		labelNumber->setBuddy(editNumber);
		layoutUpdate->addRow(labelNumber, editNumber);
		
		auto labelObject = new QLabel("&Obiect");
		auto editObject = new QLineEdit;
		labelObject->setBuddy(editObject);
		layoutUpdate->addRow(labelObject, editObject);
		
		auto labelStatus = new QLabel("&Status");
		auto comboBoxStatus = new QComboBox;
			comboBoxStatus->addItem("pending");
			comboBoxStatus->addItem("confirmed");
			comboBoxStatus->addItem("cancelled");
			comboBoxStatus->addItem("delivered");
		labelStatus->setBuddy(comboBoxStatus);
		layoutUpdate->addRow(labelStatus, comboBoxStatus);
		
		auto buttonUpdate = new QPushButton("&update");
		layoutUpdate->addWidget(buttonUpdate);
	layoutControls->addLayout(layoutUpdate);
	
	QObject::connect(
		m_list, &QListWidget::currentItemChanged,
		[&srv, editNumber, editObject, comboBoxStatus](QListWidgetItem *current, QListWidgetItem *previous) {
			if (current != nullptr) {
				int id = current->data(Qt::UserRole).toInt();
				
				auto order = srv.findOrder(id);
				editNumber->setText(QString::number(order.getNumber()));
				editObject->setText(QString::fromStdString(order.getObject()));
				Status status = order.getStatus();
				if (status == Status::PENDING) {
					comboBoxStatus->setCurrentIndex(0);
				} else if (status == Status::CONFIRMED) {
					comboBoxStatus->setCurrentIndex(1);
				} else if (status == Status::CANCELLED) {
					comboBoxStatus->setCurrentIndex(2);
				} else if (status == Status::DELIVERED) {
					comboBoxStatus->setCurrentIndex(3);
				}
			}
		}
	);
	
	auto list = m_list;
	QObject::connect(
		buttonUpdate, &QPushButton::clicked,
		[this, &srv, list, editNumber, editObject, comboBoxStatus]() {
			auto current = list->currentItem();
			if (current != nullptr) {
				int id = current->data(Qt::UserRole).toInt();
				
				auto order = srv.findOrder(id);
				int number = editNumber->text().toInt();
				std::string object = editObject->text().toStdString();
				
				int statusIndex = comboBoxStatus->currentIndex();
				Status status = Status::PENDING;
				if (statusIndex == 0) {
					status = Status::PENDING;
				} else if (statusIndex == 1) {
					status = Status::CONFIRMED;
				} else if (statusIndex == 2) {
					status = Status::CANCELLED;
				} else if (statusIndex == 3) {
					status = Status::DELIVERED;
				}
				
				srv.updateOrder(id, number, object, status);
				this->updateList();
			}
		}
	);
	
	auto comboBox = new QComboBox;
		comboBox->addItem("unfiltered");
		comboBox->addItem("pending");
		comboBox->addItem("confirmed");
		comboBox->addItem("cancelled");
		comboBox->addItem("delivered");
	layoutControls->addWidget(comboBox);
	
	QObject::connect(
		comboBox, &QComboBox::currentTextChanged,
		[this](const QString &text) {
			if (text == "unfiltered") {
				this->m_listFilter = ListFilter::UNFILTERED;
			} else if (text == "pending") {
				this->m_listFilter = ListFilter::BY_PENDING;
			} else if (text == "confirmed") {
				this->m_listFilter = ListFilter::BY_CONFIRMED;
			} else if (text == "cancelled") {
				this->m_listFilter = ListFilter::BY_CANCELLED;
			} else if (text == "delivered") {
				this->m_listFilter = ListFilter::BY_DELIVERED;
			}
			this->updateList();
		}
	);
	
	layoutControls->addStretch();
	
	window->show();
}
