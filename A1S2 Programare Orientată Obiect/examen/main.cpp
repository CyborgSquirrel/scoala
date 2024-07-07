#include "./domain.hpp"
#include "./repo.hpp"
#include "./srv.hpp"
#include "./gui.hpp"

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

int main(int argc, char **argv) {
	testDomain();
	testRepo();
	testSrv();
	
	RepoMelodie repo { "./melodii.txt" };
	SrvMelodie srv { repo };
	
	QApplication app { argc, argv };
	
	auto window = makeGui(srv);
	window->show();
	
	return app.exec();
}
