#include "repository.h"
#include "vec.h"
Repository* create_empty_repository()
{
	Repository* rez = (Repository*)malloc(sizeof(Repository));
	if (rez != NULL)
	{
		rez->elems = create_empty(
			sizeof(Materie*),
			copy_materie_generic,
			destroy_entity_generic
		);
	}
	return rez;
}
void destroy_repository(Repository* l)
{
	/*
	* Metoda care elibereaza zona de memorie ocupata de lista de entitati.
	* input : lista l
	* output: - 
	*/
	destroy_vec(l->elems);
	free(l);
}

void addRepo(Repository* l, Materie* m)
{
	int i;
	for (i = 0;i < l->elems->lg;i++)
	{
		Materie* temp;
		vec_get(l->elems, &temp, i);
		if (strcmp(m->nume, temp->nume) == 0)
		{
			m->cantitate += temp->cantitate;
			vec_erase(l->elems, i);
			break;
		}
	}
	vec_push(l->elems, m);
}

Materie* get(Repository* l, int poz)
{
	Materie* m;
	vec_get(l->elems, &m, poz);
	return m;
}

int findbyname(Repository* l, char* nume)
{
	for (int i = 0;i < l->elems->lg;i++)
	{
		Materie* temp;
		vec_get(l->elems, &temp, i);
		if (strcmp(temp->nume, nume) == 0)
			return i;
	}
	return -1;
		
}
int modifyRepo(Repository* l, Materie* m)
{
	int poz = findbyname(l, m->nume);
	if (poz == -1)
		return -1;
	vec_erase(l->elems, poz);
	vec_push(l->elems, m);
	return 0;
}

int deleteRepo(Repository* l, char* nume)
{
	int poz = findbyname(l, nume);
	if (poz == -1)
		return -1;
	return vec_erase(l->elems, poz);
	// for (int i = poz;i < l->elems->lg;i++)
	// {
		// Materie* destroy = l->elems[i];
		// l->elems[i] = l->elems[i + 1];
		// destroy_entity(destroy);
	// }
	// l->lg -= 1;
}
Vec* get_filtered(Repository* l, float cantitate)
{
	Vec* rez = create_empty(sizeof(Materie*), copy_materie_generic, destroy_entity_generic);
	for (int i = 0;i < l->elems->lg;i++)
	{
		Materie* temp;
		vec_get(l->elems, &temp, i);
		if (temp->cantitate < cantitate) {
			vec_push(rez, copy_materie(temp));
		}
	}
	return rez;
}
Vec* get_filtered_above(Repository* l,float cantitate)
{
	Vec* rez = create_empty(sizeof(Materie*), copy_materie_generic, destroy_entity_generic);
	for (int i = 0;i < l->elems->lg;i++)
	{
		Materie* temp;
		vec_get(l->elems, &temp, i);
		if (temp->cantitate > cantitate) {
			vec_push(rez, copy_materie(temp));
		}
	}
	return rez;
}
Vec* get_all(Repository* l)
{
	return l->elems;
}
int get_len(Repository* l)
{
	/*
	 * Metoda care returneaza lungimea repo-ului l.
	 * input : l - repo-ul al carui lungime va fi returnata
	 * output: lungimea repo-ului
	 */
	return l->elems->lg;
}
Repository* copy_repository(Repository* l)
{
	/*
	 * Metoda care copiaza valoarea listei de la adresa src, la adresa dest.
	 * input : dest - pointer la lista destinatie
	 *         src - pointer la lista sursa
	 * output: -
	 */
	Repository* copy = malloc(sizeof(Repository));
	copy->elems = copy_vec(l->elems);
	return copy;
}
void destroy_repository_generic(void* l)
{
	/*
	 * Metoda care dealoca lista de la adresa l.
	 * input : l - pointer la lista care va fi dealocata
	 * output: -
	 */
	destroy_repository(*((Repository**) l));
}
