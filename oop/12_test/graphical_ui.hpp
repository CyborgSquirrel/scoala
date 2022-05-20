#ifndef graphical_ui_hpp_INCLUDED
#define graphical_ui_hpp_INCLUDED

#include "./srv.hpp"

#include <QListWidget>

enum ListFilter {
	UNFILTERED, BY_PENDING, BY_CONFIRMED, BY_CANCELLED, BY_DELIVERED
};

class GraphicalUI {
private:
	SrvOrder &m_srv;
	ListFilter m_listFilter;
	
	QListWidget *m_list;
	
	void updateList();
public:
	GraphicalUI(SrvOrder &srv);
};

#endif // graphical_ui_hpp_INCLUDED

