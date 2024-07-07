#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "./vec.h"
#include "./domain.h"
#include "./valid.h"
#include "./repo.h"
#include "./srv.h"

#ifndef ONLY_RUN_TESTS
	#include "./console_ui.h"
#endif

int main(int argc, char **argv) {
	
#ifdef ONLY_RUN_TESTS
	test_domain();
	test_vec();
	test_validate();
	test_repo();
	test_srv();
#else
	struct RepoCheltuieli repo_cheltuieli = repo_cheltuieli_new();
	struct SrvCheltuieli srv_cheltuieli = srv_cheltuieli_new(repo_cheltuieli);
	struct ConsoleUi console_ui = console_ui_new(srv_cheltuieli);
	console_ui_run(&console_ui);
	console_ui_drop(&console_ui);
#endif
	
	return 0;
}
