#include "./repo.hpp"

#include <fstream>
#include <cassert>

void RepoOrder::readAllFromFile() {
	std::ifstream fin(m_filePath);
	std::string buf = "";
	while (std::getline(fin, buf)) {
		std::vector<std::string> fields;
		std::string field;
		for (auto c : buf) {
			if (c == ',') {
				fields.push_back(field);
				field.clear();
			} else {
				field += c;
			}
		}
		if (!field.empty()) {
			fields.push_back(field);
		}
		
		if (fields.size() >= 4) {
			int id = std::stoi(fields[0]);
			int number = std::stoi(fields[1]);
			std::string object = fields[2];
			Status status = Status::PENDING;
			if (fields[3] == "pending") {
				status = Status::PENDING;
			} else if (fields[3] == "confirmed") {
				status = Status::CONFIRMED;
			} else if (fields[3] == "cancelled") {
				status = Status::CANCELLED;
			} else if (fields[3] == "delivered") {
				status = Status::DELIVERED;
			}
			
			m_orders.push_back(Order(id, number, object, status));
		}
	}
}

RepoOrder::RepoOrder(std::string filePath) {
	m_filePath = filePath;
	readAllFromFile();
}

Order RepoOrder::find(int id) const {
	for (const auto &order : m_orders) {
		if (order.getId() == id) {
			return order;
		}
	}
	// TODO: exception
	return m_orders[0];
}
void RepoOrder::update(const Order &newOrder) {
	for (auto &order : m_orders) {
		if (order.getId() == newOrder.getId()) {
			order = newOrder;
			break;
		}
	}
	// TODO: exception if not found
}
const std::vector<Order> &RepoOrder::getAll() const {
	return m_orders;
}

void testRepoOrder() {
	RepoOrder repo("./test/orders.txt");
	
	auto orders = repo.getAll();
	
	assert(orders[0] == Order(0,0,"wood",Status::PENDING));
	assert(orders[1] == Order(1,1,"concrete",Status::CONFIRMED));
	assert(orders[2] == Order(2,2,"asbestos",Status::CANCELLED));
	
	assert(repo.find(3) == Order(3,3,"shafts",Status::DELIVERED));
	assert(repo.find(4) == Order(4,4,"truck",Status::PENDING));
	assert(repo.find(5) == Order(5,5,"car",Status::CONFIRMED));
	
	repo.update(Order(6,10,"ferrarri",Status::CANCELLED));
	assert(repo.find(6) == Order(6,10,"ferrarri",Status::CANCELLED));
}
