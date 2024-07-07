#ifndef gui_hpp_INCLUDED
#define gui_hpp_INCLUDED

#include "./srv.hpp"
#include "./observer.hpp"
#include <QWidget>
#include <QPixmap>

class Gui : public QWidget, public Observer {
private:
	QPixmap pixmap;
	SrvTaxi &srv;
public:
	Gui(SrvTaxi &srv);
	void paintEvent(QPaintEvent *event) override;
	void updateObserver() override;
};

#endif // gui_hpp_INCLUDED

