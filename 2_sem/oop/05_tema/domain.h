#pragma once
#ifndef DOMAIN_H_
#define DOMAIN_H_
#include <string.h>
#include <stdlib.h>
typedef struct {
	char* nume;
	char* producator;
	float cantitate;
}Materie;
Materie* creare_materie(char* nume, char* producator, float cantitate);
Materie* copy_materie(Materie* m);
void* copy_materie_generic(void* m);
void destroy_entity(Materie* m);
void destroy_entity_generic(void* m);
#endif // !DOMAIN_H_
