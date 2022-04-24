#ifndef graphical_ui_hpp_INCLUDED
#define graphical_ui_hpp_INCLUDED

#include "./srv.hpp"

#include <QAbstractTableModel>
#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QDir>
#include <QFile>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QTableView>
#include <QTabWidget>
#include <QTextStream>
#include <QWindow>

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

QLineEdit *addField(QLayout *layout, const QString &name);
QGroupBox *boxCrud(SrvCartiModel *model);
QGroupBox *boxReports(SrvCartiModel *model);

class GraphicalUi {
private:
	QApplication app;
	SrvCarti &srv_carti;
	SrvInchirieriCarte &srv_inchirieri_carte;
public:
	GraphicalUi(
		int argc, char **argv,
		SrvCarti &srv_carti,
		SrvInchirieriCarte &srv_inchirieri_carte
	);
	
	int run();
};

#endif // graphical_ui_hpp_INCLUDED

