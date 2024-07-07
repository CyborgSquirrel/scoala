#include "./repo.hpp"

#include <fstream>
#include <vector>
#include <string>
#include <cassert>

void RepoDevice::readAllFromFile() {
	std::ifstream fin(m_filePath);
	std::string buf;
	while (getline(fin, buf)) {
		std::vector<std::string> fields;
		std::string currentField = "";
		for (auto c : buf) {
			if (c == ',') {
				fields.push_back(currentField);
				currentField.clear();
			} else {
				currentField += c;
			}
		}
		if (!currentField.empty()) {
			fields.push_back(currentField);
		}
		
		if (fields.size() >= 5) {
			int id = std::stoi(fields[0]);
			std::string type = fields[1];
			std::string model = fields[2];
			int year = std::stoi(fields[3]);
			DeviceColor color = DeviceColor::BLACK;
			if (fields[4] == "RED") {
				color = DeviceColor::RED;
			} else if (fields[4] == "BLUE") {
				color = DeviceColor::BLUE;
			} else if (fields[4] == "BLACK") {
				color = DeviceColor::BLACK;
			} else if (fields[4] == "YELLOW") {
				color = DeviceColor::YELLOW;
			}
			float price = std::stof(fields[5]);
			
			auto device = Device(id, type, model, year, color, price);
			m_devices.push_back(device);
		}
	}
}
void RepoDevice::writeAllToFile() const {
	std::ofstream fout(m_filePath);
	for (const auto &device : m_devices) {
		fout <<        device.getType()
			 << "," << device.getModel()
			 << "," << device.getYear()
			 << "," << device.getColor()
			 << "," << device.getPrice()
			 << "\n";
	}
}

RepoDevice::RepoDevice(const std::string &filePath) {
	m_filePath = filePath;
	this->readAllFromFile();
}

const std::vector<Device> &RepoDevice::getAll() const {
	return m_devices;
}

Device RepoDevice::find(int id) const {
	for (const auto &device : m_devices) {
		if (device.getId() == id) {
			return device;
		}
	}
	return m_devices[0];
}

void test_repo_device() {
	auto repo = RepoDevice("./test.txt");
	
	auto devices = repo.getAll();
	
	assert(devices[0] == Device(0, "phone", "iphone", 2009, DeviceColor::RED, 399));
}
