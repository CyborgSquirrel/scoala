#ifndef repo_hpp_INCLUDED
#define repo_hpp_INCLUDED

#include "./domain.hpp"
#include <string>
#include <vector>

class RepoTaxi {
private:
	std::string file_path;
	std::vector<Taxi> taxis;
	void read_all_from_file();
	void write_all_to_file() const;
public:
	RepoTaxi(const std::string &file_path);
	const std::vector<Taxi> &get_all();
	void update(const Taxi &taxi);
};

#endif // repo_hpp_INCLUDED

