#include "domain.h"

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