#include "./srv.hpp"

#include <algorithm>
#include <cassert>

SrvDevice::SrvDevice(RepoDevice &repoDevice) : m_repoDevice(repoDevice) {
	
}

const std::vector<Device> &SrvDevice::getAll() const {
	return m_repoDevice.getAll();
}

std::vector<Device> SrvDevice::getSortedByModel() const {
	auto devices = m_repoDevice.getAll();
	std::sort(
		devices.begin(), devices.end(),
		[](const Device &lhs, const Device &rhs) {
			return lhs.getModel() < rhs.getModel();
		}
	);
	return devices;
}

std::vector<Device> SrvDevice::getSortedByYear() const {
	auto devices = m_repoDevice.getAll();
	std::sort(
		devices.begin(), devices.end(),
		[](const Device &lhs, const Device &rhs) {
			return lhs.getYear() < rhs.getYear();
		}
	);
	return devices;
}

Device SrvDevice::findById(int id) const {
	return m_repoDevice.find(id);
}

void test_srv_device() {
	auto repo = RepoDevice("./test.txt");
	auto srv = SrvDevice(repo);
	
	auto unsorted = srv.getAll();
	assert(unsorted[0] == Device(0, "phone", "iphone", 2009, DeviceColor::RED, 399));
	
	auto sortedByYear = srv.getSortedByYear();
	assert(sortedByYear[0] == Device(8, "dishwasher", "general electric", 1980, DeviceColor::RED, 399));
	
	auto sortedByModel = srv.getSortedByModel();
	assert(sortedByModel[0] == Device(9, "powertool", "bormasina", 2020, DeviceColor::RED, 399));
}
