// decomenteaza linia de mai jos ca sa rulezi teste (si comenteaz-o ca sa rulezi programul)
// #define ONLY_RUN_TESTS

#ifndef ONLY_RUN_TESTS
	#include "./ui.hpp"
#endif

#include "./vec.hpp"
#include "./exception.hpp"
#include "./srv.hpp"

int main() {
#ifdef ONLY_RUN_TESTS
	test_vec();
	test_exception();
	test_domain();
	test_repo();
	test_srv();
#else
	RepoCarti repo {};
	SrvCarti srv {repo};
	Ui ui {srv};
	ui.run();
#endif
	return 0;
}
