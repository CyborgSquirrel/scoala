#ifndef srv_hpp_INCLUDED
#define srv_hpp_INCLUDED

#include "./repo.hpp"

class SrvDevice {
private:
	RepoDevice &m_repoDevice;
public:
	SrvDevice(RepoDevice &repoDevice);
	const std::vector<Device> &getAll() const;
	std::vector<Device> getSortedByModel() const;
	std::vector<Device> getSortedByYear() const;
	Device findById(int id) const;
};

void test_srv_device();

#endif // srv_hpp_INCLUDED

