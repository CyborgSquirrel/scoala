#pragma once
#ifndef SERVICE_H_
#define SERVICE_H_
#include "repository.h"
#include "validare.h"
#include "stdlib.h"
typedef struct {
	Repository* repository;
	Vec* undo_stack;
}Service;
Service* create_service(Repository* repository);
void destroy_service(Service* srv);
int addEntity(Service* srv, char* nume, char* producator, float cantitate);
int modifyEntity(Service* srv, char* nume, char* producator, float cantitate);
int deleteEntity(Service* srv, char* nume);
Vec* criterialist(Service* srv, float cantitate);
Vec* criterialist_above(Service* srv, float cantitate);
Vec* sortedEntities(Service* srv);
int undo(Service* srv);
#endif // !SERVICE_H_
