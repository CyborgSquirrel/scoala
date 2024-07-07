#include "./srv.hpp"

#include <cassert>

SrvOrder::SrvOrder(RepoOrder &repo) : m_repo(repo) {
	
}

Order SrvOrder::findOrder(int id) {
	return m_repo.find(id);
}
void SrvOrder::updateOrder(int id, int number, const std::string &object, Status status) {
	m_repo.update(Order(id, number, object, status));
}
const std::vector<Order> &SrvOrder::getOrders() const {
	return m_repo.getAll();
}
std::vector<Order> SrvOrder::getOrdersFilteredByStatus(Status filterStatus) const {
	auto orders = m_repo.getAll();
	std::vector<Order> filtered;
	for (const auto &order : orders) {
		if (order.getStatus() == filterStatus) {
			filtered.push_back(order);
		}
	}
	return filtered;
}

void testSrvOrder() {
	RepoOrder repo("./test/orders.txt");
	SrvOrder srv(repo);
	
	auto orders = srv.getOrders();
	
	assert(orders[0] == Order(0,0,"wood",Status::PENDING));
	assert(orders[1] == Order(1,1,"concrete",Status::CONFIRMED));
	assert(orders[2] == Order(2,2,"asbestos",Status::CANCELLED));
	
	assert(srv.findOrder(3) == Order(3,3,"shafts",Status::DELIVERED));
	assert(srv.findOrder(4) == Order(4,4,"truck",Status::PENDING));
	assert(srv.findOrder(5) == Order(5,5,"car",Status::CONFIRMED));
	
	srv.updateOrder(6,10,"ferrarri",Status::CANCELLED);
	assert(srv.findOrder(6) == Order(6,10,"ferrarri",Status::CANCELLED));
	
	std::vector<Order> orders_by_pending_correct = {
		Order(0,0,"wood",Status::PENDING),
		Order(4,4,"truck",Status::PENDING),
	};
	auto orders_by_pending = srv.getOrdersFilteredByStatus(Status::PENDING);
	assert(orders_by_pending == orders_by_pending_correct);
}
