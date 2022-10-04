#include "./srv.hpp"

#include <cmath>
#include <stdexcept>
#include <iostream>

SrvException::SrvException(const std::string &message)
: m_message(message)
{ }
const std::string &SrvException::getMessage() const {
	return m_message;
}

SrvDriver::SrvDriver(RepoDriver &repo)
: m_repo(repo)
{ }

Driver SrvDriver::findDriver(int id) const {
	return m_repo.find(id);
}

void SrvDriver::moveDriver(int id, float deltaLat, float deltaLon) {
	auto driver = m_repo.find(id);
	driver.setLat(driver.getLat() + deltaLat);
	driver.setLon(driver.getLon() + deltaLon);
	m_repo.update(driver);
}

const std::vector<Driver> &SrvDriver::getAll() const {
	return m_repo.getAll();
}

SrvReport::SrvReport(RepoReport &repo, RepoDriver &repoDriver)
: m_repo(repo), m_repoDriver(repoDriver)
{ }

const std::vector<Report> &SrvReport::getAll() const {
	return m_repo.getAll();
}

void SrvReport::addReport(
	const Driver &reporter,
	const std::string &description,
	float lat, float lon
) {
	float deltaLat = reporter.getLat() - lat;
	float deltaLon = reporter.getLon() - lon;
	float dist = sqrtf(deltaLat*deltaLat + deltaLon*deltaLon);
	if (description == "") {
		throw SrvException {"description is empty"};
	}
	if (dist > 20) {
		throw SrvException {"reporter is too far"};
	} else {
		m_repo.add(Report(m_repo.getNextId(), description, reporter.getName(), lat, lon, false));
	}
}

void SrvReport::validateReport(
	int id,
	const Driver &validator
) {
	auto report = m_repo.find(id);
	
	if (!report.getValid()) {
		if (validator.getName() != report.getReporter()) { 
			std::vector<std::string> validators = report.getValidators();
			bool validatorFound = false;
			for (int i = 0; !validatorFound && i < validators.size(); ++i) {
				const auto &otherValidator = validators[i];
				if (otherValidator == validator.getName()) {
					validatorFound = true;
				}
			}
			
			if (!validatorFound) {
				report.addValidator(validator.getName());
				if (report.getValidators().size() >= 2) {
					report.setValid(true);
				}
				m_repo.update(report);
				
				if (report.getValid()) {
					auto drivers = m_repoDriver.getAll();
					Driver driver;
					bool driverFound = false;
					for (int i = 0; !driverFound && i < drivers.size(); ++i) {
						driver = drivers[i];
						if (driver.getName() == report.getReporter()) {
							driverFound = true;
						}
					}
					
					if (driverFound) {
						driver.setScore(driver.getScore()+1);
						if (driver.getScore() == 10) {
							driver.setStatus(DriverStatus::GROWNUP);
							m_repoDriver.update(driver);
						} else if (driver.getScore() == 15) {
							driver.setStatus(DriverStatus::KNIGHT);
							m_repoDriver.update(driver);
						}
					}
				}
			}
		}
	}
}

std::vector<Report> SrvReport::getAllNear(
	float lat, float lon,
	float radius
) const {
	std::vector<Report> foundReports;
	auto reports = m_repo.getAll();
	for (const auto &report : reports) {
		float deltaLat = report.getLat() - lat;
		float deltaLon = report.getLon() - lon;
		float dist = sqrtf(deltaLat*deltaLat + deltaLon*deltaLon);
		if (dist <= radius) {
			foundReports.push_back(report);
		}
	}
	return foundReports;
}
