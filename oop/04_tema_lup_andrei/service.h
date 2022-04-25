#pragma once
#ifndef SERVICE_H_
#define SERVICE_H_
#include "repository.h"
#include "validare.h"
#include "stdlib.h"
typedef struct {
	Lista* repository;
}Service;
Service* create_service(Lista* repository);
void destroy_service(Service* srv);
int addEntity(Service* srv, char* nume, char* producator, float cantitate);
int modifyEntity(Service* srv, char* nume, char* producator, float cantitate);
int deleteEntity(Service* srv, char* nume);
Lista* criterialist(Service* srv, float cantitate);
Lista* sortedEntities(Service* srv);
#endif // !SERVICE_H_
