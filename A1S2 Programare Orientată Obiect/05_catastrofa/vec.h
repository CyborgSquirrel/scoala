#ifndef vec_h_INCLUDED
#define vec_h_INCLUDED

#include <stdlib.h>
#include <assert.h>

extern const char *const ERR_INVALID_INDEX;

struct Vec {
	int allocated_len, len;
	void *buf;
	
	int element_size;
	void (*element_clone)(void *, void *);
	void (*element_drop)(void *);
};

// Creeaza un nou vector, care stocheaza un tip generic.
// in: element_size -- sizeof al elementului (in octeti)
//     element_clone -- functie care face copie al unui element
//     element_drop -- functie care dealoca un element
// out: struct Vec
struct Vec vec_new(
	int element_size,
	void (*element_clone)(void *, void *),
	void (*element_drop)(void *)
);

// Dealoca un vector.
// in: vec -- pointer la vectorul care va fi dealocat
void vec_drop(struct Vec *vec);

// Dealoca un vector, care este transmis prin void *.
// in: vec -- pointer la vectorul care va fi dealocat
void vec_drop_generic(void *vec);

// Extrage un element din vector.
// in: vec -- pointer la vectorul din care se extrage elementul
//     value -- pointer la locul in care se va salva elementul extras
//     index -- indicele elementului care sa fie extras
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const vec_get(
	struct Vec *vec,
	void *value,
	int index
);

// Adauga un element la sfarsitul vectorului.
// in: vec -- pointer la vectorul la sfarsitul caruia se adauga elementul
//     value -- pointer la elementul care va fi adaugat
void vec_push(
	struct Vec *vec,
	void *value
);

// Atribuie unui element din vector, la indicele specificat, valoarea furnizata.
// in: vec -- pointer la vectorul in care se va face atribuirea
//     index -- indicele elementului caruia i se atribuie valoarea
//     value -- pointer la valoarea care va fi atribuita elementului din vector
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const vec_set(
	struct Vec *vec,
	int index,
	void *value
);

// Sterge un element din vector, la indicele specificat.
// in: vec -- pointer la vectorul din care se va face stergerea
//     index -- indicele elementului care va fi sters
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const vec_erase(
	struct Vec *vec,
	int index
);

// Copiaza vectorul sursa in vectorul destinatie.
// in: dest -- pointer la vectorul destinatie (care nu a fost initializat cu nici o valoare)
//     src -- pointer la vectorul sursa
void vec_clone(
	struct Vec *dest,
	struct Vec *src
);

// Copiaza vectorul sursa in vectorul destinatie, vectorii fiind transmisi prin void *.
// in: dest -- pointer la vectorul destinatie (care nu a fost initializat cu nici o valoare)
//     src -- pointer la vectorul sursa
void vec_clone_generic(void *dest, void *src);

// Sorteaza un vector.
// in: vec -- pointer la vectorul care va fi sortat
//     lt -- functia care va fi folosita pentru compararea elementelor (la sortare)
void vec_sort(
	struct Vec *vec,
	int (*lt)(void *, void *)
);

void test_vec(void);

#endif // vec_h_INCLUDED

