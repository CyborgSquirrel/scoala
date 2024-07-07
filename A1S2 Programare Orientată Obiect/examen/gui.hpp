#ifndef gui_hpp_INCLUDED
#define gui_hpp_INCLUDED

#include "./domain.hpp"
#include "./repo.hpp"
#include "./srv.hpp"

#include <iostream>
#include <functional>

#include <QApplication>
#include <QErrorMessage>
#include <QPointF>
#include <QPainter>
#include <QFormLayout>
#include <QTableView>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QItemSelectionModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QAbstractTableModel>

class SrvMelodieModel : public QAbstractTableModel {
private:
	SrvMelodie &m_srv;
	std::vector<Melodie> m_melodii;
	
	int m_callbackId;
public:
	SrvMelodieModel(SrvMelodie &srv);
	~SrvMelodieModel();
	
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

class MyWidget : public QWidget {
private:
	SrvMelodie &m_srv;
	int m_callbackId;
	
	float getRadius(int j);
public:
	MyWidget(SrvMelodie &srv);
	~MyWidget();
	void paintEvent(QPaintEvent *event) override;
};

void tryCatchErrorMessage(std::function<void()> f);

MyWidget *makeGui(SrvMelodie &srv);

#endif // gui_hpp_INCLUDED

