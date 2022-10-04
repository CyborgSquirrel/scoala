#ifndef repo_hpp_INCLUDED
#define repo_hpp_INCLUDED

#include "./domain.hpp"

#include <vector>

class RepoDriver {
private:
	std::vector<Driver> m_drivers;
	std::string m_filePath;
	
	void readAllFromFile();
public:
	RepoDriver(const std::string &filePath);
	const std::vector<Driver> &getAll() const;
	void update(Driver driver);
	Driver find(int id);
};

class RepoReport {
private:
	std::vector<Report> m_reports;
	std::string m_filePath;
	
	void readAllFromFile();
public:
	RepoReport(const std::string &filePath);
	const std::vector<Report> &getAll() const;
	void add(Report report);
	void update(Report report);
	Report find(int id);
	
	int getNextId() const;
};

#endif // repo_hpp_INCLUDED

