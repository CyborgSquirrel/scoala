#include "./domain.hpp"

#include <cassert>

Order::Order(int id, int number, const std::string &object, Status status) {
	m_id = id;
	m_number = number;
	m_object = object;
	m_status = status;
}

int Order::getId() const {
	return m_id;
}
int Order::getNumber() const {
	return m_number;
}
const std::string &Order::getObject() const {
	return m_object;
}
Status Order::getStatus() const {
	return m_status;
}

void Order::setNumber(int number) {
	m_number = number;
}
void Order::setObject(const std::string &object) {
	m_object = object;
}
void Order::setStatus(Status status) {
	m_status = status;
}

bool Order::operator==(const Order &other) const {
	return m_id == other.m_id
		&& m_number == other.m_number
		&& m_object == other.m_object
		&& m_status == other.m_status;
}

void testOrder() {
	Order order_1 = Order(0, 0, "wood", Status::PENDING);
	Order order_1_copy = Order(0, 0, "wood", Status::PENDING);
	
	assert(order_1.getId() == 0);
	assert(order_1.getNumber() == 0);
	assert(order_1.getObject() == "wood");
	assert(order_1.getStatus() == Status::PENDING);
	
	assert(order_1 == order_1_copy);
	
	order_1.setNumber(2);
	order_1.setObject("asbestos");
	order_1.setStatus(Status::CANCELLED);
	
	assert(order_1.getNumber() == 2);
	assert(order_1.getObject() == "asbestos");
	assert(order_1.getStatus() == Status::CANCELLED);
}
