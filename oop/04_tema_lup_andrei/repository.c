#include "repository.h"
Lista* create_empty()
{
	Lista* rez = (Lista*)malloc(sizeof(Lista));
	if (rez != NULL)
	{
		rez->cp = 10;
		rez->elems = malloc(sizeof(Materie) * rez->cp);
		rez->lg = 0;
	}
	return rez;
}
void destroy_list(Lista* l)
{
	/*
	* Metoda care elibereaza zona de memorie ocupata de lista de entitati.
	* input : lista l
	* output: - 
	*/
	for (int i = 0;i < l->lg;i++)
	{
		ElemType temp = l->elems[i];
		destroy_entity(temp);
	}
	free(l->elems);
	free(l);
}

void addRepo(Lista* l, ElemType m)
{
	int i, existent = 0;
	for (i = 0;i < l->lg;i++)
	{
		Materie* temp = get(l, i);
		if (strcmp(m->nume, temp->nume) == 0)
		{
			strcpy(temp->nume, m->nume);
			strcpy(temp->producator, m->producator);
			temp->cantitate +=m->cantitate;
			existent = 1;
			break;
		}
	}
	if (!existent)
	{
		ensureCapacity(l);
		l->elems[l->lg] = m;
		l->lg += 1;
	}
}

ElemType get(Lista* l, int poz)
{
	return l->elems[poz];
}

int ensureCapacity(Lista* l)
{
	if (l->lg < l->cp) {
		return l->cp; //we have room
	}
	//alocate more memory
	int newCapacity = l->cp* 2;
	int size = sizeof(ElemType) * newCapacity;
	if (size == 0)
		exit(1);
	ElemType* nElems = malloc(size);
	if (nElems != NULL)
	{
		//copy elems
		for (int i = 0; i < l->lg; i++) {
			nElems[i] = l->elems[i];
		}
		//dealocate old vector
		free(l->elems);
		l->elems = nElems;
		l->cp = newCapacity;
	}
	
	return l->cp;
}

int findbyname(Lista* l, char* nume)
{
	for (int i = 0;i < l->lg;i++)
	{
		Materie* temp = get(l, i);
		if (strcmp(temp->nume, nume) == 0)
			return i;
	}
	return -1;
		
}

// CODEREVIEW:
// Daca numele sau producatorul noului element este mai lung decat cel al elementului
// care este modificat, atunci va fi un buffer overflow.
// De asemenea, cred ca modifyRepo ar trebui sa inlocuiasca obiectul modificat cu un nou
// obiect, si sa nu modifice campurile obiectului.
int modifyRepo(Lista* l, ElemType m)
{
	int poz = findbyname(l, m->nume);
	if (poz == -1)
		return -1;
	Materie* m2 = get(l, poz);
	strcpy(m2->nume, m->nume);
	strcpy(m2->producator, m->producator);
	m2->cantitate = m->cantitate;
	return 0;
}

// CODEREVIEW:
// Functia asta nu functioneaza daca deletezi o materie care e la sfarsit.
// Numele functiei ma face sa gandesc ca deleteaza repo-ul, dar de fapt deleteaza
// un element din repo. Cred ca era mai bine daca il numea, de exemplu,
// deleteFromRepo.
int deleteRepo(Lista* l, char* nume)
{
	int poz = findbyname(l, nume);
	if (poz == -1)
		return -1;
	for (int i = poz;i < l->lg;i++)
	{
		Materie* destroy = l->elems[i];
		l->elems[i] = l->elems[i + 1];
		destroy_entity(destroy);

	}
	l->lg -= 1;
	return 0;
}
Lista* get_filtered(Lista* l,float cantitate)
{
	Lista* rez = create_empty();
	for (int i = 0;i < l->lg;i++)
	{
		Materie* temp = get(l, i);
		if (temp->cantitate < cantitate)
			addRepo(rez, creare_materie(temp->nume, temp->producator, temp->cantitate));

	}
	return rez;
}
Lista* get_all(Lista* l)
{
	Lista* rez = create_empty();
	for (int i = 0;i < l->lg;i++)
	{
		Materie* temp = get(l, i);
		addRepo(rez, creare_materie(temp->nume, temp->producator, temp->cantitate));

	}
	return rez;
}
