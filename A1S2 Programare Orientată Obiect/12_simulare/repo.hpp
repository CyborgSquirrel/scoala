#ifndef repo_hpp_INCLUDED
#define repo_hpp_INCLUDED

#include "domain.hpp"

#include <vector>
#include <string>

class RepoDevice {
private:
	std::vector<Device> m_devices;
	std::string m_filePath;
	
	void readAllFromFile();
	void writeAllToFile() const;
public:
	RepoDevice(const std::string &filePath);
	const std::vector<Device> &getAll() const;
	Device find(int id) const;
};

void test_repo_device();

#endif // repo_hpp_INCLUDED

