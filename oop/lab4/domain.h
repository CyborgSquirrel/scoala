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
void destroy_entity(Materie* m);
#endif // !DOMAIN_H_
