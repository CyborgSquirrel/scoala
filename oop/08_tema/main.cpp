// decomenteaza linia de mai jos ca sa rulezi teste (si comenteaz-o ca sa rulezi programul)
// #define ONLY_RUN_TESTS

#ifndef ONLY_RUN_TESTS
	#include "./ui.hpp"
#endif

#include "./exception.hpp"
#include "./srv.hpp"

int main() {
#ifdef ONLY_RUN_TESTS
	test_domain();
	test_repo();
	test_srv();
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
