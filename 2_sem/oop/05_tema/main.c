#include "service.h"
#include "repository.h"
#include "ui.h"
#include "testare.h"
int main()
{
#ifdef ONLY_RUN_TESTS
	run_tests();
#else
	Repository* repo = create_empty_repository();
	Service* srv = create_service(repo);
	UI* user_interface = create_ui(srv);
	run(user_interface);
	destroy_ui(user_interface);
#endif
	return 0;
}
