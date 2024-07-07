#include "./domain.hpp"

#include <cassert>

Device::Device(int id, const std::string &type, const std::string &model, int year, DeviceColor color, float price) {
	m_id = id;
	m_type = type;
	m_model = model;
	m_year = year;
	m_color = color;
	m_price = price;
}

int Device::getId() const {
	return m_id;
}
const std::string &Device::getType() const {
	return m_type;
}
const std::string &Device::getModel() const {
	return m_model;
}
int Device::getYear() const {
	return m_year;
}
DeviceColor Device::getColor() const {
	return m_color;
}
float Device::getPrice() const {
	return m_price;
}

void Device::setType(const std::string &type) {
	m_type = type;
}
void Device::setModel(const std::string &model) {
	m_model = model;
}
void Device::setYear(int year) {
	m_year = year;
}
void Device::setColor(DeviceColor color) {
	m_color = color;
}
void Device::setPrice(float price) {
	m_price = price;
}

bool Device::operator==(const Device &other) {
	return m_id == other.m_id
		&& m_type == other.m_type
		&& m_model == other.m_model
		&& m_year == other.m_year
		&& m_color == other.m_color
		&& m_price == other.m_price;
}

void test_device() {
	Device device(0, "phone", "iphone", 2009, DeviceColor::RED, 399);
	
	assert(device.getId() == 0);
	assert(device.getType() == "phone");
	assert(device.getModel() == "iphone");
	assert(device.getYear() == 2009);
	assert(device.getColor() == DeviceColor::RED);
	assert(device.getPrice() == 399);
	
	device.setType("dishwasher");
	device.setModel("whirpool");
	device.setYear(1990);
	device.setColor(DeviceColor::BLACK);
	device.setPrice(200);
	
	assert(device.getType() == "dishwasher");
	assert(device.getModel() == "whirpool");
	assert(device.getYear() == 1990);
	assert(device.getColor() == DeviceColor::BLACK);
	assert(device.getPrice() == 200);
}
