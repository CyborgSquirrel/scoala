#include "service.h"
#include "repository.h"
#include "ui.h"
#include "testare.h"

// CODEREVIEW:
// Nu toate functiile sunt documentate.

int main()
{
#ifdef ONLY_RUN_TESTS
	run_tests();
#else
	Lista* repo = create_empty();
	Service* srv = create_service(repo);
	UI* user_interface = create_ui(srv);
	run(user_interface);
	destroy_ui(user_interface);
#endif
	return 0;
}
