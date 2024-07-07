#pragma once
#ifndef REPOSITORY_H_
#define REPOSITORY_H_
#include "domain.h"
#include <string.h>

// CODEREVIEW:
// Cred ca numele functiilor sa fie, fie toate snake_case, fie toate CamelCase.

// CODEREVIEW:
// Din punct de vedere structural, cred ca aici lista si repo-ul sunt aceeasi chestie.
// Cred ca ar fi fost mai bine daca lista si repo-ul ar fi fost structuri separate (asa
// cred ca ar fi fost mai simplu sa fac lista de liste pentru undo).

// CODEREVIEW:
// Poate ar fi trebuit sa puna un get_len()?

typedef Materie* ElemType;
typedef struct {
	ElemType* elems;
	int cp;
	int lg;
}Lista;
Lista* create_empty();
void destroy_list(Lista* l);
void addRepo(Lista* repository, Materie* m);
ElemType get(Lista* l, int poz);
int ensureCapacity(Lista* l);
int modifyRepo(Lista* l, Materie* m);
int deleteRepo(Lista* l, char* nume);
Lista* get_all(Lista* l);
Lista* get_filtered(Lista* l,float cantitate);
int findbyname(Lista* l, char* nume);
#endif // !REPOSITORY_H_
