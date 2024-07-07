#include "./repo.hpp"

#include <fstream>
#include <iostream>

void RepoDriver::readAllFromFile() {
	m_drivers.clear();
	
	std::ifstream fin(m_filePath);
	std::string line;
	while (std::getline(fin, line)) {
		std::vector<std::string> fields;
		std::string field = "";
		for (auto c : line) {
			if (c == ',') {
				fields.push_back(field);
				field.clear();
			} else {
				field += c;
			}
		}
		fields.push_back(field);
		
		if (fields.size() >= 6) {
			int id = std::stoi(fields[0]);
			std::string name = fields[1];
			DriverStatus status = DriverStatus::BABY;
			std::string statusString = fields[2];
			if (statusString == "BABY") {
				status = DriverStatus::BABY;
			} else if (statusString == "GROWNUP") {
				status = DriverStatus::GROWNUP;
			} else if (statusString == "KNIGHT") {
				status = DriverStatus::KNIGHT;
			}
			float lat = std::stof(fields[3]);
			float lon = std::stof(fields[4]);
			int score = std::stoi(fields[5]);
			
			Driver driver(id, name, status, lat, lon, score);
			m_drivers.push_back(driver);
		}
	}
}

RepoDriver::RepoDriver(const std::string &filePath)
: m_filePath(filePath)
{
	readAllFromFile();
}

void RepoDriver::update(Driver driver) {
	for (auto &oldDriver : m_drivers) {
		if (oldDriver.getId() == driver.getId()) {
			oldDriver = driver;
			return;
		}
	}
	throw "not found";
}

Driver RepoDriver::find(int id) {
	for (const auto &driver : m_drivers) {
		if (driver.getId() == id) {
			return driver;
		}
	}
	throw "not found";
}

const std::vector<Driver> &RepoDriver::getAll() const {
	return m_drivers;
}

void RepoReport::readAllFromFile() {
	m_reports.clear();
	
	std::ifstream fin(m_filePath);
	std::string line;
	while (std::getline(fin, line)) {
		std::vector<std::string> fields;
		std::string field = "";
		for (auto c : line) {
			if (c == ',') {
				fields.push_back(field);
				field.clear();
			} else {
				field += c;
			}
		}
		fields.push_back(field);
		
		if (fields.size() >= 6) {
			int id = std::stoi(fields[0]);
			std::string description = fields[1];
			std::string name = fields[2];
			float lat = std::stof(fields[3]);
			float lon = std::stof(fields[4]);
			bool valid = std::stoi(fields[5]);
			
			Report report(id, description, name, lat, lon, valid);
			m_reports.push_back(report);
		}
	}
}
RepoReport::RepoReport(const std::string &filePath)
: m_filePath(filePath)
{
	readAllFromFile();
}
const std::vector<Report> &RepoReport::getAll() const {
	return m_reports;
}

void RepoReport::add(Report report) {
	m_reports.push_back(report);
}

void RepoReport::update(Report report) {
	for (auto &oldReport : m_reports) {
		if (oldReport.getId() == report.getId()) {
			oldReport = report;
			return;
		}
	}
	throw "not found";
}

Report RepoReport::find(int id) {
	for (const auto &report : m_reports) {
		if (report.getId() == id) {
			return report;
		}
	}
	throw "not found";
}

int RepoReport::getNextId() const {
	int id = 0;
	for (const auto report : m_reports) {
		if (report.getId() > id) {
			id = report.getId()+1;
		}
	}
	return id;
}
