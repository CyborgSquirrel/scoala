#ifndef vec_h_INCLUDED
#define vec_h_INCLUDED

#include <stdlib.h>
#include <assert.h>

struct Vec {
	int size, len;
	struct Cheltuiala *buf;
};

struct Vec vec_new(void);

void vec_drop(struct Vec *vec);

struct Cheltuiala vec_get(
	struct Vec *vec,
	int index
);

void vec_push(
	struct Vec *vec,
	struct Cheltuiala cheltuiala
);

void vec_set(
	struct Vec *vec,
	int index,
	struct Cheltuiala cheltuiala
);

void vec_erase(
	struct Vec *vec,
	int index
);

// void vec_clone() {}
// void vec_sort() {}

void test_vec(void);

#endif // vec_h_INCLUDED

