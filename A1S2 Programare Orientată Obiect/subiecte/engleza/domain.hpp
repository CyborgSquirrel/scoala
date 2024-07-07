#ifndef domain_hpp_INCLUDED
#define domain_hpp_INCLUDED

#include <string>
#include <vector>

enum class DriverStatus {
	BABY, GROWNUP, KNIGHT
};

std::string driverStatusToString(DriverStatus driverStatus);

class Driver {
private:
	int m_id;
	std::string m_name;
	DriverStatus m_status;
	float m_lat;
	float m_lon;
	int m_score;
public:
	Driver() = default;
	Driver(
		int id,
		const std::string &name,
		DriverStatus status,
		float lat,
		float lon,
		int score
	);
	
	int getId() const;
	const std::string &getName() const;
	DriverStatus getStatus() const;
	float getLat() const;
	float getLon() const;
	int getScore() const;
	
	void setName(const std::string &name);
	void setStatus(DriverStatus status);
	void setLat(float lat);
	void setLon(float lon);
	void setScore(int score);
};

class Report {
private:
	int m_id;
	std::string m_description;
	std::string m_reporter;
	float m_lat;
	float m_lon;
	bool m_valid;
	std::vector<std::string> m_validators;
public:
	Report(
		int id,
		const std::string &description,
		const std::string &reporter,
		float lat,
		float lon,
		bool valid
	);
	
	int getId() const;
	const std::string &getDescription() const;
	const std::string &getReporter() const;
	float getLat() const;
	float getLon() const;
	std::vector<std::string> getValidators() const;
	bool getValid() const;
	
	void setDescription(const std::string &description);
	void setReporter(const std::string &reporter);
	void setLat(float lat);
	void setLon(float lon);
	void setValid(bool valid);
	
	void addValidator(const std::string &validator);
};

#endif // domain_hpp_INCLUDED

