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

// Creeaza un nou vector de cheltuieli.
// in: element_size -- sizeof al elementului care va fi stocat in vector (in octeti)
// out: struct Vec
struct Vec vec_new(
	int element_size,
	void (*element_clone)(void *, void *),
	void (*element_drop)(void *)
);

// Dealoca un vector.
// in: *vec -- vectorul care va fi dealocat
void vec_drop(struct Vec *vec);

void vec_drop_generic(void *vec);

// Extrage un element din vector.
// in: *vec -- vectorul din care se extrage elementul
//     *element -- TODO
//     int index
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const vec_get(
	struct Vec *vec,
	void *element,
	int index
);

// Adauga un element la sfarsitul vectorului.
// in: pointer to struct Vec
//     struct Cheltuiala
void vec_push(
	struct Vec *vec,
	void *element
);

// Atribuie unui element din vector, la indicele specificat, valoare furnizata.
// in: pointer to struct Vec
//     int
//     struct Cheltuiala
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const vec_set(
	struct Vec *vec,
	int index,
	void *element
);

// Sterge unui element din vector, la indicele specificat.
// in: pointer to struct Vec
//     int
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const vec_erase(
	struct Vec *vec,
	int index
);

// Creeaza o copie a unui vector.
// in: pointer to struct Vec
// out: struct Vec
void vec_clone(
	struct Vec *dest,
	struct Vec *src
);

void vec_clone_generic(void *dest, void *src);

// Sorteaza un vector.
// in: pointer to struct Vec
//     comparison function
void vec_sort(
	struct Vec *vec,
	int (*lt)(void *, void *)
);

void test_vec(void);

#endif // vec_h_INCLUDED

