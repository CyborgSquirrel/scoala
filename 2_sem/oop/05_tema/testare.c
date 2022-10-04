#include "testare.h"
void test_add_repo()
{
	Repository* repotest = create_empty_repository();
	assert(get_len(repotest) == 0);
	Materie* m = creare_materie("a", "b", 1);
	addRepo(repotest, m);
	assert(get_len(repotest) == 1);
	Materie* temp = get(repotest, 0);
	assert(strcmp(temp->nume, "a") == 0);
	m = creare_materie("a", "b", 1);
	addRepo(repotest, m);
	temp = get(repotest, 0);
	assert(get_len(repotest) == 1);
	assert(temp->cantitate == 2);
	destroy_repository(repotest);
}
void test_add_capacity()
{
	Repository* repotest = create_empty_repository();
	addRepo(repotest, creare_materie("a", "b", 1));
	addRepo(repotest, creare_materie("b", "b", 1));
	addRepo(repotest, creare_materie("c", "b", 1));
	addRepo(repotest, creare_materie("d", "b", 1));
	addRepo(repotest, creare_materie("e", "b", 1));
	addRepo(repotest, creare_materie("f", "b", 1));
	addRepo(repotest, creare_materie("g", "b", 1));
	addRepo(repotest, creare_materie("h", "b", 1));
	addRepo(repotest, creare_materie("i", "b", 1));
	addRepo(repotest, creare_materie("j", "b", 1));
	addRepo(repotest, creare_materie("k", "b", 1));
	// assert(repotest->cp == 20);
	assert(repotest->elems->cp == 20);
	// assert(ensureCapacity(repotest) == 20);
	destroy_repository(repotest);
}
void test_modify_repo()
{
	Repository* repotest = create_empty_repository();
	Materie* m = creare_materie("a", "b", 1);
	addRepo(repotest, m);
	m = creare_materie("a", "xyz", 3);
	assert(modifyRepo(repotest, m) == 0);
	m = creare_materie("ana", "are", 3);
	assert(modifyRepo(repotest,m)  == -1);
	destroy_repository(repotest);
	destroy_entity(m);

}
void test_find_by_name()
{
	Repository* repotest = create_empty_repository();
	Materie* m = creare_materie("a", "b", 1);
	addRepo(repotest, m);
	assert(findbyname(repotest, "c") == -1);
	assert(findbyname(repotest, "a") == 0);
	destroy_repository(repotest);
}

void test_delete_repo()
{
	Repository* repotest = create_empty_repository();
	Materie* m = creare_materie("a", "b", 1);
	addRepo(repotest, m);
	m = creare_materie("x", "y", 1);
	addRepo(repotest, m);
	assert(deleteRepo(repotest, "b") == -1);
	assert(deleteRepo(repotest, "a") == 0);
	destroy_repository(repotest);
}

void test_get_all()
{
	Repository* repotest = create_empty_repository();
	Materie* m = creare_materie("a", "b", 1);
	addRepo(repotest, m);
	Vec* rez = get_all(repotest);
	assert(rez->lg == 1);
	destroy_repository(repotest);
}
void test_validare()
{
	Materie* m = creare_materie("faina", "banel", 1);
	assert(validare(m) == 1);
	m->cantitate = -2;
	strcpy(m->nume, "");
	strcpy(m->producator, "");
	assert(validare(m) == -2);
	strcpy(m->nume, "ana");
	strcpy(m->producator, "mere");
	assert(validare(m) == -2);
	destroy_entity(m);
}
void test_add_service()
{
	Repository* repotest = create_empty_repository();
	Service* srvtest = create_service(repotest);
	assert(addEntity(srvtest, "", "ana", 5) == -2);
	assert(addEntity(srvtest, "ana", "are", 2) == 0);
	assert(addEntity(srvtest, "ana2", "are", 2) == 0);
	destroy_service(srvtest);
}
void test_modify_service()
{
	Repository* repotest = create_empty_repository();
	Service* srvtest = create_service(repotest);
	assert(modifyEntity(srvtest, "", "ana", 5) == -2);
	assert(addEntity(srvtest, "ana", "are", 2) == 0);
	assert(modifyEntity(srvtest, "ana", "are", 5) == 0);
	assert(modifyEntity(srvtest, "dan", "are", 2) == -1);
	destroy_service(srvtest);
}
void test_delete_service()
{
	Repository* repotest = create_empty_repository();
	Service* srvtest = create_service(repotest);
	assert(addEntity(srvtest, "ana", "are", 2) == 0);
	assert(deleteEntity(srvtest, "dan") == -1);
	assert(deleteEntity(srvtest, "ana") == 0);
	destroy_service(srvtest);
}

void test_criteria_list()
{
	Repository* repotest = create_empty_repository();
	Service* srvtest = create_service(repotest);
	assert(addEntity(srvtest, "ana", "are", 2)==0);
	assert(addEntity(srvtest, "ana2", "are", 10)==0);
	assert(addEntity(srvtest, "ana3", "are", 20)==0);
	assert(addEntity(srvtest, "ana4", "are", 5)==0);
	Vec* criteria = criterialist(srvtest, 15);
	assert(criteria->lg == 3);
	destroy_vec(criteria);
	destroy_service(srvtest);
}
void test_criteria_list_above()
{
	Repository* repotest = create_empty_repository();
	Service* srvtest = create_service(repotest);
	assert(addEntity(srvtest, "ana", "are", 2)==0);
	assert(addEntity(srvtest, "ana2", "are", 10)==0);
	assert(addEntity(srvtest, "ana3", "are", 20)==0);
	assert(addEntity(srvtest, "ana4", "are", 5)==0);
	Vec* criteria = criterialist_above(srvtest, 15);
	assert(criteria->lg == 1);
	destroy_vec(criteria);
	destroy_service(srvtest);
}
void test_sorted_list()
{
	Repository* repotest = create_empty_repository();
	Service* srvtest = create_service(repotest);
	assert(addEntity(srvtest, "ana", "are", 2) == 0);
	assert(addEntity(srvtest, "ana2", "are", 10) == 0);
	assert(addEntity(srvtest, "ana3", "are", 20) == 0);
	assert(addEntity(srvtest, "ana4", "are", 5) == 0);
	Vec* sortat = sortedEntities(srvtest);
	Materie* m;
	vec_get(sortat, &m, 0);
	assert(m->cantitate == 2);
	destroy_vec(sortat);
	destroy_service(srvtest);
}

void test_undo() {
	Repository* repotest = create_empty_repository();
	Service* srvtest = create_service(repotest);
	assert(undo(srvtest) != 0);
	
	assert(addEntity(srvtest, "ana", "are", 2) == 0);
	assert(modifyEntity(srvtest, "ana", "n-are", 4) == 0);
	assert(deleteEntity(srvtest, "ana") == 0);
	
	assert(undo(srvtest) == 0);
	assert(get_len(srvtest->repository) == 1);
	
	assert(undo(srvtest) == 0);
	assert(get_len(srvtest->repository) == 1);
	
	assert(undo(srvtest) == 0);
	assert(get_len(srvtest->repository) == 0);
	
	assert(undo(srvtest) != 0);
	
	destroy_service(srvtest);
}

void run_tests()
{
	test_add_repo();
	test_add_capacity();
	test_modify_repo();
	test_find_by_name();
	test_delete_repo();
	test_get_all();
	test_validare();
	test_add_service();
	test_modify_service();
	test_delete_service();
	test_criteria_list();
	test_criteria_list_above();
	test_sorted_list();
	test_undo();
}
