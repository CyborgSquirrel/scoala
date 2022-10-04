#include "gui.hpp"
#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTimer>

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	
	RepoTaxi repo("./taxi.txt");
	SrvTaxi srv(repo);
	
	auto window = new QWidget;
	auto layout = new QHBoxLayout;
	window->setLayout(layout);
	
	auto gui = new Gui(srv);
	layout->addWidget(gui);
	
	auto button = new QPushButton("simulate");
	QObject::connect(
		button, &QPushButton::clicked,
		[&srv]() {
			srv.simulate_one_step(600, 400);
		}
	);
	layout->addWidget(button);
	QTimer timer;
	QObject::connect(
		&timer, &QTimer::timeout,
		[&srv]() {
			srv.simulate_one_step(600, 400);
		}
	);
	timer.start(1000/10);
	
	window->show();
	
	return app.exec();
}
