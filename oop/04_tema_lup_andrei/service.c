#include "service.h"

Service* create_service(Lista* repository)
{
	Service* srv = (Service*)malloc(sizeof(Service));
	if (srv != NULL)
	{
		srv->repository = repository;
	}
	return srv;
}
void destroy_service(Service* srv)
{
	destroy_list(srv->repository);
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
	if (modifyRepo(srv->repository, m) == -1)
	{
		destroy_entity(m);
		return -1;//inexistent
	}
	destroy_entity(m);
	return 0;//ok
}
int deleteEntity(Service* srv, char* nume)
{
	return deleteRepo(srv->repository, nume);
}

Lista* criterialist(Service* srv, float cantitate)
{
	Lista* rez = get_filtered(srv->repository,cantitate);
	return rez;

}
Lista* sortedEntities(Service* srv)
{
	Lista* rez = get_all(srv->repository);
	ElemType aux;
	for (int i = 0;i < rez->lg - 1;i++)
	{
		Materie* temp = get(rez, i);
		for (int j = i + 1;j < rez->lg;j++)
		{
			Materie* temp2 = get(rez, j);
			if (temp->cantitate > temp2->cantitate)
			{
				aux = rez->elems[i];
				rez->elems[i] = rez->elems[j];
				rez->elems[j] = aux;
			}
		}
	}
	return rez;
}