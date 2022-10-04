// decomenteaza linia de mai jos ca sa rulezi teste (si comenteaz-o ca sa rulezi programul)
// #define ONLY_RUN_TESTS

#ifndef ONLY_RUN_TESTS
	#include "./ui.hpp"
#endif

#include <vector>
#include <string>
#include <iostream>

#include "./exception.hpp"
#include "./srv.hpp"

class TestCase {
private:
	void (*test)();
	std::string name;
public:
	TestCase(void (*test)(), const std::string &name)
		: test(test), name(name) { }
	void run() const {
		std::cout << "Running " << this->name << " tests" << "\n";
		this->test();
		std::cout << "Finished " << this->name << " tests" << "\n";
	}
};

int main() {
#ifdef ONLY_RUN_TESTS
	const std::vector<TestCase> tests = {
		{ test_domain , "domain" },
		{ test_repo   , "repo"   },
		{ test_srv    , "srv"    },
	};
	
	for (const auto &test : tests) {
		test.run();
	}
#else
	RepoCarti repo_carti;
	RepoInchirieriCarte repo_inchirieri_carte;
	SrvCarti srv_carti { repo_carti };
	SrvInchirieriCarte srv_inchirieri_carte { repo_carti, repo_inchirieri_carte };
	Ui ui { srv_carti, srv_inchirieri_carte };
	ui.run();
#endif
	return 0;
}
