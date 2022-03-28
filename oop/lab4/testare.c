#include "testare.h"
void test_add_repo()
{
	Lista* repotest = create_empty();
	assert(repotest->lg == 0);
	Materie* m = creare_materie("a", "b", 1);
	addRepo(repotest, m);
	assert(repotest->lg == 1);
	Materie* temp = get(repotest, 0);
	assert(strcmp(temp->nume, "a") == 0);
	addRepo(repotest, m);
	assert(repotest->lg == 1);
	assert(temp->cantitate == 2);
	destroy_list(repotest);
}
void test_add_capacity()
{
	Lista* repotest = create_empty();
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
	assert(repotest->cp == 20);
	assert(ensureCapacity(repotest) == 20);
	destroy_list(repotest);
}
void test_modify_repo()
{
	Lista* repotest = create_empty();
	Materie* m = creare_materie("a", "b", 1);
	addRepo(repotest, m);
	assert(modifyRepo(repotest, m) == 0);
	m = creare_materie("ana", "are", 3);
	assert(modifyRepo(repotest,m)  == -1);
	destroy_list(repotest);
	destroy_entity(m);

}
void test_find_by_name()
{
	Lista* repotest = create_empty();
	Materie* m = creare_materie("a", "b", 1);
	addRepo(repotest, m);
	assert(findbyname(repotest, "c") == -1);
	assert(findbyname(repotest, "a") == 0);
	destroy_list(repotest);
}

void test_delete_repo()
{
	Lista* repotest = create_empty();
	Materie* m = creare_materie("a", "b", 1);
	addRepo(repotest, m);
	assert(deleteRepo(repotest, "b") == -1);
	assert(deleteRepo(repotest, "a") == 0);
	destroy_list(repotest);
}

void test_get_all()
{
	Lista* repotest = create_empty();
	Materie* m = creare_materie("a", "b", 1);
	addRepo(repotest, m);
	Lista* rez = get_all(repotest);
	assert(rez->lg == 1);
	destroy_list(rez);
	destroy_list(repotest);
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
	Lista* repotest = create_empty();
	Service* srvtest = create_service(repotest);
	assert(addEntity(srvtest, "", "ana", 5) == -2);
	assert(addEntity(srvtest, "ana", "are", 2) == 0);
	assert(addEntity(srvtest, "ana2", "are", 2) == 0);
	destroy_service(srvtest);
}
void test_modify_service()
{
	Lista* repotest = create_empty();
	Service* srvtest = create_service(repotest);
	assert(modifyEntity(srvtest, "", "ana", 5) == -2);
	assert(addEntity(srvtest, "ana", "are", 2) == 0);
	assert(modifyEntity(srvtest, "ana", "are", 5) == 0);
	assert(modifyEntity(srvtest, "dan", "are", 2) == -1);
	destroy_service(srvtest);
}
void test_delete_service()
{
	Lista* repotest = create_empty();
	Service* srvtest = create_service(repotest);
	assert(addEntity(srvtest, "ana", "are", 2) == 0);
	assert(deleteEntity(srvtest, "dan") == -1);
	assert(deleteEntity(srvtest, "ana") == 0);
	destroy_service(srvtest);
}

void test_criteria_list()
{
	Lista* repotest = create_empty();
	Service* srvtest = create_service(repotest);
	assert(addEntity(srvtest, "ana", "are", 2)==0);
	assert(addEntity(srvtest, "ana2", "are", 10)==0);
	assert(addEntity(srvtest, "ana3", "are", 20)==0);
	assert(addEntity(srvtest, "ana4", "are", 5)==0);
	Lista* criteria = criterialist(srvtest, 15);
	assert(criteria->lg == 3);
	destroy_list(criteria);
	destroy_service(srvtest);
}
void test_sorted_list()
{
	Lista* repotest = create_empty();
	Service* srvtest = create_service(repotest);
	assert(addEntity(srvtest, "ana", "are", 2) == 0);
	assert(addEntity(srvtest, "ana2", "are", 10) == 0);
	assert(addEntity(srvtest, "ana3", "are", 20) == 0);
	assert(addEntity(srvtest, "ana4", "are", 5) == 0);
	Lista* sortat = sortedEntities(srvtest);
	assert(sortat->elems[0]->cantitate == 2);
	destroy_list(sortat);
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
	test_sorted_list();
}