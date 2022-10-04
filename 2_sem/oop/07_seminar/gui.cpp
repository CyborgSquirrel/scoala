#include "gui.hpp"
#include <QPainter>
#include <QTransform>
#include <cmath>
#include <iostream>

Gui::Gui(SrvTaxi &srv) : srv(srv) {
	srv.add_observer(this);
	this->setFixedHeight(400);
	this->setFixedWidth(600);
	pixmap.load("/home/andrei/scoala/oop/07_seminar/taxi.png");
	pixmap = pixmap.scaledToWidth(40);
}

void Gui::paintEvent(QPaintEvent *event) {
	QPainter painter { this };
	auto taxis = srv.get_taxis();
	for (const auto &taxi : taxis) {
		int lon = taxi.getLon();
		int lat = taxi.getLat();
		int vlon = taxi.getVLon();
		int vlat = taxi.getVLat();
		auto angle = atan2(vlat, vlon);
		auto new_pixmap = pixmap.transformed(QTransform().rotateRadians(angle));
		painter.drawPixmap(lon, lat, new_pixmap);
	}
}

void Gui::updateObserver() {
	this->update();
}
