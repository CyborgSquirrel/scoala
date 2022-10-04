#include "domain.h"
#include <stdio.h>

void destroy_entity(Materie* m)
{
	/*
	* Metoda care elibereaza memoria ocupata de o materie prima m.
	* input: Materie m
	* output: - 
	*/
	free(m->nume);
	free(m->producator);
	free(m);
}

void destroy_entity_generic(void* m) {
	destroy_entity(*((Materie**) m));
}

Materie* copy_materie(Materie* m)
{
	/*
	 * Metoda care copiaza materia m.
	 * input : m - materia care este copiata
	 * output: copia lui m
	 */
	Materie* c = malloc(sizeof(Materie));
	int nrc = strlen(m->nume) + 1;
	c->nume = (char*) malloc(nrc * sizeof(char));
	strcpy(c->nume, m->nume);
	nrc = strlen(m->producator) + 1;
	c->producator = (char*) malloc(nrc * sizeof(char));
	strcpy(c->producator, m->producator);
	c->cantitate = m->cantitate;
	return c;
}

void* copy_materie_generic(void* m)
{
	/*
	 * Metoda care copiaza materia m, transmisa prin void*.
	 * input : m - materia care este copiata
	 * output: copia lui m
	 */
	return copy_materie(*((Materie**) m));
}

Materie* creare_materie(char* nume, char* producator, float cantitate)
{
	/*
	* Metoda care creaza o materie prima.
	* input: nume - numele materiei prime char pointer
	*	     producator - numele producatorului char pointer
	*		 cantitate - cantitatea materiei prime, numar real pozitiv
	* Output: m - materie prima
	*/
	Materie* m = (Materie*)malloc(sizeof(Materie));
	if (m != NULL)
	{
		int nrc = strlen(nume) + 1;
		m->nume = (char*)malloc(nrc * sizeof(char));
		strcpy(m->nume, nume);
		nrc = strlen(producator) + 1;
		m->producator = malloc(nrc * sizeof(char));
		strcpy(m->producator, producator);
		m->cantitate = cantitate;
	}
	
	return m;
}

