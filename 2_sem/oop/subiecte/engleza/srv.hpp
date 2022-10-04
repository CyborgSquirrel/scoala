#ifndef srv_hpp_INCLUDED
#define srv_hpp_INCLUDED

#include "./repo.hpp"

class SrvException {
private:
	std::string m_message;
public:
	SrvException(const std::string &message);
	const std::string &getMessage() const;
};

class SrvDriver {
private:
	RepoDriver &m_repo;
public:
	SrvDriver(RepoDriver &repo);
	Driver findDriver(int id) const;
	void moveDriver(int id, float deltaLat, float deltaLon);
	const std::vector<Driver> &getAll() const;
};

class SrvReport {
private:
	RepoReport &m_repo;
	RepoDriver &m_repoDriver;
public:
	SrvReport(RepoReport &repo, RepoDriver &repoDriver);
	const std::vector<Report> &getAll() const;
	void addReport(
		const Driver &reporter,
		const std::string &description,
		float lat, float lon
	);
	void validateReport(
		int id,
		const Driver &validator
	);
	std::vector<Report> getAllNear(
		float lat, float lon,
		float radius
	) const;
};

#endif // srv_hpp_INCLUDED

