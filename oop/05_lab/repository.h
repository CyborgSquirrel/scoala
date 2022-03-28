#pragma once
#ifndef REPOSITORY_H_
#define REPOSITORY_H_
#include "domain.h"
#include "vec.h"
#include <string.h>
typedef struct {
	Vec* elems;
} Repository;
Repository* create_empty_repository();
void destroy_repository(Repository* l);
void addRepo(Repository* repository, Materie* m);
Materie* get(Repository* l, int poz);
int modifyRepo(Repository* l, Materie* m);
int deleteRepo(Repository* l, char* nume);
Vec* get_all(Repository* l);
Vec* get_filtered(Repository* l,float cantitate);
Vec* get_filtered_above(Repository* l,float cantitate);
int findbyname(Repository* l, char* nume);
int get_len(Repository* l);

Repository* copy_repository(Repository* l);
void destroy_repository_generic(void* l);

#endif // !REPOSITORY_H_
