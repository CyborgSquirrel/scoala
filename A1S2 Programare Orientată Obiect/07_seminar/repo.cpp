#include "./repo.hpp"

#include <fstream>
#include <algorithm>

void RepoTaxi::read_all_from_file() {
	std::fstream fin(file_path);
	taxis.clear();
	Taxi taxi;
	while (fin >> taxi) {
		taxis.push_back(taxi);
	}
}

void RepoTaxi::write_all_to_file() const {
	std::ofstream fout(file_path);
	for (const auto &taxi : taxis) {
		fout << taxi << "\n";
	}
}

RepoTaxi::RepoTaxi(const std::string &file_path) : file_path(file_path) {
	
}

const std::vector<Taxi> &RepoTaxi::get_all() {
	read_all_from_file();
	return taxis;
}

void RepoTaxi::update(const Taxi &taxi) {
	read_all_from_file();
	auto it = std::find(taxis.begin(), taxis.end(), taxi);
	if (it == taxis.end()) {
		throw std::exception();
	}
	*it = taxi;
	write_all_to_file();
}
