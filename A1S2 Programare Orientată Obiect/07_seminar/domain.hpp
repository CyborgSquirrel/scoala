#ifndef domain_hpp_INCLUDED
#define domain_hpp_INCLUDED

#include <string>
#include <iostream>

class Taxi {
private:
	int id;
	std::string sofer;
	int lon, lat;
	int vlon, vlat;
public:
	Taxi() = default;
	Taxi(int id, const std::string &sofer, int lon, int lat);
	
	int getId() const;
	int getLon() const;
	int getLat() const;
	int getVLon() const;
	int getVLat() const;
	
	void setLon(int);
	void setLat(int);
	void setVLon(int);
	void setVLat(int);
	
	friend std::ostream &operator<<(std::ostream &stream, const Taxi &taxi);
	friend std::istream &operator>>(std::istream &stream, Taxi &taxi);
	
	bool operator==(const Taxi &other) const;
};
std::ostream &operator<<(std::ostream &stream, const Taxi &taxi);
std::istream &operator>>(std::istream &stream, Taxi &taxi);

#endif // domain_hpp_INCLUDED

