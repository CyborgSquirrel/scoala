#include "./observer.hpp"


void Observable::add_observer(Observer *observer) {
	observers.push_back(observer);
}
void Observable::notify_all() const {
	for (auto observer : observers) {
		observer->updateObserver();
	}
}
