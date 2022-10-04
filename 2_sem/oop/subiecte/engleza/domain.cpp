#include "./domain.hpp"

std::string driverStatusToString(DriverStatus driverStatus) {
	if (driverStatus == DriverStatus::BABY) {
		return "BABY";
	} else if (driverStatus == DriverStatus::GROWNUP) {
		return "GROWNUP";
	} else if (driverStatus == DriverStatus::KNIGHT) {
		return "KNIGHT";
	} else {
		return "BABY";
	}
}

Driver::Driver(
	int id,
	const std::string &name,
	DriverStatus status,
	float lat,
	float lon,
	int score
) : m_id(id), m_name(name), m_status(status), m_lat(lat), m_lon(lon), m_score(score)
{ }

int Driver::getId() const { return m_id; };
const std::string &Driver::getName() const { return m_name; }
DriverStatus Driver::getStatus() const { return m_status; }
float Driver::getLat() const { return m_lat; }
float Driver::getLon() const { return m_lon; }
int Driver::getScore() const { return m_score; }

void Driver::setName(const std::string &name) { m_name = name; }
void Driver::setStatus(DriverStatus status) { m_status = status; }
void Driver::setLat(float lat) { m_lat = lat; }
void Driver::setLon(float lon) { m_lon = lon; }
void Driver::setScore(int score) { m_score = score; }

Report::Report(
	int id,
	const std::string &description,
	const std::string &reporter,
	float lat,
	float lon,
	bool valid
) : m_id(id), m_description(description), m_reporter(reporter), m_lat(lat), m_lon(lon), m_valid(valid)
{ }

int Report::getId() const { return m_id; };
const std::string &Report::getDescription() const { return m_description; }
const std::string &Report::getReporter() const { return m_reporter; }
float Report::getLat() const { return m_lat; }
float Report::getLon() const { return m_lon; }
std::vector<std::string> Report::getValidators() const { return m_validators; }
bool Report::getValid() const { return m_valid; }

void Report::setDescription(const std::string &description) { m_description = description; }
void Report::setReporter(const std::string &reporter) { m_reporter = reporter; }
void Report::setLat(float lat) { m_lat = lat; }
void Report::setLon(float lon) { m_lon = lon; }
void Report::setValid(bool valid) { m_valid = valid; }

void Report::addValidator(const std::string &validator) {
	m_validators.push_back(validator);
}
