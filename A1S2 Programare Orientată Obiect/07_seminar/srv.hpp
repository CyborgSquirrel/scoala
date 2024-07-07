#ifndef srv_hpp_INCLUDED
#define srv_hpp_INCLUDED

#include "./repo.hpp"
#include "./observer.hpp"

class SrvTaxi : public Observable {
private:
	RepoTaxi &repo;
public:
	SrvTaxi(RepoTaxi &repo);
	void simulate_one_step(int width, int height);
	const std::vector<Taxi> &get_taxis() const;
};

#endif // srv_hpp_INCLUDED

