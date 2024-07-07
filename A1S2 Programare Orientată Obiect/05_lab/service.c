#include "service.h"

Service* create_service(Repository* repository)
{
	Service* srv = (Service*)malloc(sizeof(Service));
	if (srv != NULL)
	{
		srv->repository = repository;
		srv->undo_stack = create_empty(sizeof(Repository*), NULL, destroy_repository_generic);
	}
	return srv;
}
void destroy_service(Service* srv)
{
	destroy_repository(srv->repository);
	destroy_vec(srv->undo_stack);
	free(srv);
}

int addEntity(Service* srv, char* nume, char* producator, float cantitate)
{
	Materie* m = creare_materie(nume, producator, cantitate);
	if (validare(m) == -2)
	{
		destroy_entity(m);
		return -2;
	}
	Repository* copy = copy_repository(srv->repository);
	vec_push(srv->undo_stack, copy);
	addRepo(srv->repository,m);
	return 0;
}
int modifyEntity(Service* srv, char* nume, char* producator, float cantitate)
{
	Materie* m = creare_materie(nume, producator, cantitate);
	if (validare(m) == -2)
	{
		destroy_entity(m);
		return -2;
	}
	
	Repository* copy = copy_repository(srv->repository);
	if (modifyRepo(srv->repository, m) == -1)
	{
		destroy_entity(m);
		destroy_repository(copy);
		return -1;//inexistent
	}
	vec_push(srv->undo_stack, copy);
	return 0;//ok
}
int deleteEntity(Service* srv, char* nume)
{
	Repository* copy = copy_repository(srv->repository);
	int rez = deleteRepo(srv->repository, nume);
	if (rez != 0) {
		destroy_repository(copy);
		return rez;
	}
	vec_push(srv->undo_stack, copy);
	return 0;
}

Vec* criterialist(Service* srv, float cantitate)
{
	Vec* rez = get_filtered(srv->repository,cantitate);
	return rez;
}
Vec* criterialist_above(Service* srv, float cantitate)
{
	Vec* rez = get_filtered_above(srv->repository,cantitate);
	return rez;
}
Vec* sortedEntities(Service* srv, CmpFn cmp)
{
	Vec* rez = get_all(srv->repository);
	rez = copy_vec(rez);
	for (int i = 0;i < rez->lg - 1;i++)
	{
		Materie* temp;
		vec_get(rez, &temp, i);
		
		for (int j = i + 1;j < rez->lg;j++)
		{
			Materie* temp2;
			vec_get(rez, &temp2, j);
			if (cmp(temp, temp2))
			{
				Materie* aux = copy_materie(temp);
				Materie* aux2 = copy_materie(temp2);
				vec_set(rez, i, aux2);
				vec_set(rez, j, aux);
				vec_get(rez, &temp, i);
			}
		}
	}
	return rez;
}

int __ascendingCantitateCmp(Materie* lhs, Materie* rhs)
	{ return lhs->cantitate > rhs->cantitate; }
Vec* ascendingCantitateSort(Service* srv) {
	/*
	 * Returneaza materiile sortate ascendent dupa cantitate.
	 * input : srv - service-ul al carui materii vor fi sortate si returnate
	 * output: vector cu materiile sortate ascendent dupa cantitate
	 */
	return sortedEntities(srv, __ascendingCantitateCmp);
}

int __descendingCantitateCmp(Materie* lhs, Materie* rhs)
	{ return lhs->cantitate < rhs->cantitate; }
Vec* descendingCantitateSort(Service* srv) {
	/*
	 * Returneaza materiile sortate descendent dupa cantitate.
	 * input : srv - service-ul al carui materii vor fi sortate si returnate
	 * output: vector cu materiile sortate ascendent dupa cantitate
	 */
	return sortedEntities(srv, __descendingCantitateCmp);
}

int undo(Service* srv) {
	/*
	 * Reface ultima operatie.
	 * input : srv - service-ul in care se va reface ultima operatie
	 * output: 0, daca operatia a fost refacuta cu succes, si -6 altfel
	 */
	if (srv->undo_stack->lg <= 0) return -6;
	destroy_repository(srv->repository);
	vec_pop(srv->undo_stack, &srv->repository);
	return 0;
}
