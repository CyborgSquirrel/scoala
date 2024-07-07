#ifndef vec_h_INCLUDED
#define vec_h_INCLUDED

#include <stdlib.h>
#include <assert.h>

extern const char *const ERR_INVALID_INDEX;

struct Vec {
	int size, len;
	struct Cheltuiala *buf;
};

// Creeaza un nou vector de cheltuieli.
// out: struct Vec
struct Vec vec_new(void);

// Dealoca un vector.
// in: vec -- pointer la vectorul care va fi dealocat
void vec_drop(struct Vec *vec);

// Extrage o cheltuiala din vector.
// in: vec -- pointer la vectorul din care se extrage cheltuiala
//     cheltuiala -- pointer la variabila in care se va salva cheltuiala extrasa
//     index -- indicele cheltuielii care sa fie extrasa
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const vec_get(
	struct Vec *vec,
	struct Cheltuiala *cheltuiala,
	int index
);

// Adauga o cheltuiala la sfarsitul vectorului.
// in: vec -- pointer la vectorul la sfarsitul caruia se adauga elementul
//     cheltuiala -- cheltuiala care va fi adaugata
void vec_push(
	struct Vec *vec,
	struct Cheltuiala cheltuiala
);

// Atribuie unei cheltuieli din vector, la indicele specificat, valoarea furnizata.
// in: vec -- pointer la vectorul in care se va face atribuirea
//     index -- indicele elementului caruia i se atribuie valoarea
//     cheltuiala -- valoarea care va fi atribuita cheltuielii din vector
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const vec_set(
	struct Vec *vec,
	int index,
	struct Cheltuiala cheltuiala
);

// Sterge un cheltuiala din vector, la indicele specificat.
// in: vec -- pointer la vectorul din care se va face stergerea
//     index -- indicele cheltuielii care va fi stearsa
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const vec_erase(
	struct Vec *vec,
	int index
);

// Creeaza o copie a vectorului furnizat.
// in: vec -- pointer la vectorul care va fi copiat
// out: struct Vec -- copia vectorului furnizat
struct Vec vec_clone(
	struct Vec *vec
);

// Sorteaza un vector.
// in: vec -- pointer la vectorul care va fi sortat
//     lt -- functia care va fi folosita pentru compararea elementelor (la sortare)
void vec_sort(
	struct Vec *vec,
	int (*lt)(struct Cheltuiala *, struct Cheltuiala *)
);

void test_vec(void);

#endif // vec_h_INCLUDED

