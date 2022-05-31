#include "srv.hpp"

#include <cstdlib>
#include <iostream>

SrvTaxi::SrvTaxi(RepoTaxi &repo) : repo(repo) {
	
}

void SrvTaxi::simulate_one_step(int width, int height) {
	auto taxis = repo.get_all();
	int count = taxis.size();
	int number = rand()%count;
	for (int i = 0; i < number; ++i) {
		int index = rand()%count;
		auto &taxi = taxis[index];
		int new_lon = taxi.getLon() + taxi.getVLon();
		int new_lat = taxi.getLat() + taxi.getVLat();
		int new_vlon = taxi.getVLon() + (rand()%11-5);
		int new_vlat = taxi.getVLat() + (rand()%11-5);
		if (new_lon < 0 || new_lon > width) { new_vlon = -new_vlon; }
		if (new_lat < 0 || new_lat > height) { new_vlat = -new_vlat; }
		taxi.setLat(new_lat);
		taxi.setLon(new_lon);
		taxi.setVLon(new_vlon);
		taxi.setVLat(new_vlat);
		repo.update(taxi);
	}
	this->notify_all();
}

const std::vector<Taxi> &SrvTaxi::get_taxis() const {
	return repo.get_all();
}
