#include "./graphical_ui.hpp"

#include <QApplication>

int main(int argc, char **argv) {
	testOrder();
	testRepoOrder();
	testSrvOrder();
	
	RepoOrder repo("./orders.txt");
	SrvOrder srv(repo);
	
	QApplication application(argc, argv);
	GraphicalUI graphicalUi(srv);
	
	return application.exec();
}
