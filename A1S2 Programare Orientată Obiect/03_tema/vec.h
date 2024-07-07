#ifndef vec_h_INCLUDED
#define vec_h_INCLUDED

#include <stdlib.h>
#include <assert.h>

extern const char *const ERR_INVALID_INDEX;

struct Vec {
	int size, len;
	struct Cheltuiala *buf;
};

struct Vec vec_new(void);

void vec_drop(struct Vec *vec);

const char *const vec_get(
	struct Vec *vec,
	struct Cheltuiala *cheltuiala,
	int index
);

void vec_push(
	struct Vec *vec,
	struct Cheltuiala cheltuiala
);

const char *const vec_set(
	struct Vec *vec,
	int index,
	struct Cheltuiala cheltuiala
);

const char *const vec_erase(
	struct Vec *vec,
	int index
);

// void vec_clone() {}
// void vec_sort() {}

void test_vec(void);

#endif // vec_h_INCLUDED

