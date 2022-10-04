#ifndef observer_hpp_INCLUDED
#define observer_hpp_INCLUDED

#include <vector>

class Observer {
public:
	virtual void updateObserver() = 0;
};

class Observable {
private:
	std::vector<Observer*> observers;
public:
	void add_observer(Observer *observer);
	void notify_all() const;
};

#endif // observer_hpp_INCLUDED

