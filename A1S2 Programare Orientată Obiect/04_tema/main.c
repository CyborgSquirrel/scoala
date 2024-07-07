#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "./domain.h"
#include "./srv.h"
#include "./valid.h"
#include "./console_ui.h"

void test_all() {
	test_vec();
	test_domain();
	test_validate();
	test_repo();
	test_srv();
}

int main(int argc, char **argv) {
	test_all();
	
	struct RepoCheltuieli repo_cheltuieli = repo_cheltuieli_new();
	struct SrvCheltuieli srv_cheltuieli = srv_cheltuieli_new(repo_cheltuieli);
	struct ConsoleUi console_ui = console_ui_new(srv_cheltuieli);
	console_ui_run(&console_ui);
	console_ui_drop(&console_ui);
	
	return 0;
}
