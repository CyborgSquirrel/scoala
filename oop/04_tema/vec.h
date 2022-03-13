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
// in: pointer to struct Vec
void vec_drop(struct Vec *vec);

// Extrage un element din vector.
// in: pointer to struct Vec
//     pointer to struct Cheltuiala
//     int index
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const vec_get(
	struct Vec *vec,
	struct Cheltuiala *cheltuiala,
	int index
);

// Adauga un element la sfarsitul vectorului.
// in: pointer to struct Vec
//     struct Cheltuiala
void vec_push(
	struct Vec *vec,
	struct Cheltuiala cheltuiala
);

// Atribuie unui element din vector, la indicele specificat, valoare furnizata.
// in: pointer to struct Vec
//     int
//     struct Cheltuiala
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const vec_set(
	struct Vec *vec,
	int index,
	struct Cheltuiala cheltuiala
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
struct Vec vec_clone(
	struct Vec *vec
);

// Sorteaza un vector.
// in: pointer to struct Vec
//     comparison function
void vec_sort(
	struct Vec *vec,
	int (*lt)(struct Cheltuiala *, struct Cheltuiala *)
);

void test_vec(void);

#endif // vec_h_INCLUDED

