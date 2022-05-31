#include "./domain.hpp"

Taxi::Taxi(int id, const std::string &sofer, int lon, int lat)
	: id(id), sofer(sofer), lon(lon), lat(lat)
{
	
}

int Taxi::getId() const { return id; };
int Taxi::getLon() const { return lon; }
int Taxi::getLat() const { return lat; }
int Taxi::getVLon() const { return vlon; }
int Taxi::getVLat() const { return vlat; }


void Taxi::setLon(int lon) { this->lon = lon; }
void Taxi::setLat(int lat) { this->lat = lat; }
void Taxi::setVLon(int vlon) { this->vlon = vlon; }
void Taxi::setVLat(int vlat) { this->vlat = vlat; }


std::ostream &operator<<(std::ostream &stream, const Taxi &taxi) {
	stream << taxi.id << " " << taxi.sofer << " " << taxi.lon << " " << taxi.lat << " " << taxi.vlon << " " << taxi.vlat;
	return stream;
}
std::istream &operator>>(std::istream &stream, Taxi &taxi) {
	stream >> taxi.id >> taxi.sofer >> taxi.lon >> taxi.lat >> taxi.vlon >> taxi.vlat;
	return stream;
}

bool Taxi::operator==(const Taxi &other) const {
	return id == other.id;
}
