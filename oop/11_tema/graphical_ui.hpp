#ifndef graphical_ui_hpp_INCLUDED
#define graphical_ui_hpp_INCLUDED

#include "./srv.hpp"

#include <QAbstractTableModel>
#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QDir>
#include <QErrorMessage>
#include <QFile>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QString>
#include <QTableView>
#include <QTabWidget>
#include <QTextStream>
#include <QWindow>

QVariant cartiData(const QModelIndex &index, int role, const Carte &carte);
QVariant cartiHeaderData(int section, Qt::Orientation orientation, int role);

class SrvCartiModel : public QAbstractTableModel {
private:
	SrvCarti &srv_carti;
public:
	SrvCartiModel() = delete;
	SrvCartiModel(SrvCarti &srv_carti, QObject *parent=nullptr);
	
	void addCarte(
		const std::string &titlu,
		const std::string &autor,
		const std::string &gen,
		int an
	);
	void eraseCarte(size_t id);
	void updateCarte(
		size_t id,
		const std::string &titlu,
		const std::string &autor,
		const std::string &gen,
		int an
	);
	
	// QAbstractTableModel
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

class VectorCartiModel : public QAbstractTableModel {
private:
	std::vector<Carte> carti;
public:
	VectorCartiModel() = delete;
	VectorCartiModel(const std::vector<Carte> &carti, QObject *parent=nullptr);
	
	// QAbstractTableModel
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

class CartiPeAnModel : public QAbstractTableModel {
private:
	std::vector<std::pair<int, int>> carti_pe_an;
public:
	CartiPeAnModel() = delete;
	CartiPeAnModel(const std::map<int, int> &carti_pe_an, QObject *parent=nullptr);
	
	// QAbstractTableModel
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

template <class T>
T *addField(QFormLayout *layout, const QString &name) {
	QLabel *label = new QLabel(name);
	T *edit = new T;
	label->setBuddy(edit);
	layout->addRow(label, edit);
	return edit;
}

class ReportsGen {
private:
	QVBoxLayout *layout;
	std::vector<QPushButton*> buttons;
public:
	ReportsGen();
	void show();
	void update(SrvCarti &srv_carti);
};

class GraphicalUi {
private:
	QApplication app;
	SrvCarti &srv_carti;
	SrvInchirieriCarte &srv_inchirieri_carte;
	
	ReportsGen reportsGen;
	
	QGroupBox *boxCrud(SrvCartiModel *model);
	QGroupBox *boxReports();
	void showReportsGen();
public:
	GraphicalUi(
		int argc, char **argv,
		SrvCarti &srv_carti,
		SrvInchirieriCarte &srv_inchirieri_carte
	);
	
	int run();
};

#endif // graphical_ui_hpp_INCLUDED

