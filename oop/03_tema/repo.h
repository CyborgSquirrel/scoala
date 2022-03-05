#ifndef repo_h_INCLUDED
#define repo_h_INCLUDED

#include "./vec.h"

struct RepoCheltuieli {
	struct Vec vec;
};

struct RepoCheltuieli repo_cheltuieli_new() {
	struct RepoCheltuieli repo_cheltuieli;
	repo_cheltuieli.vec = vec_new();
	return repo_cheltuieli;
}

void repo_cheltuieli_drop(struct RepoCheltuieli *repo_cheltuieli) {
	assert(repo_cheltuieli);
	vec_drop(&repo_cheltuieli->vec);
}

int __repo_cheltuieli_find(
	struct RepoCheltuieli *repo_cheltuieli,
	int id
) {
	assert(repo_cheltuieli);
	for (int i = 0; i < repo_cheltuieli->vec.len; ++i) {
		if (vec_get(&repo_cheltuieli->vec, i).id == id) {
			return i;
		}
	}
	return -1;
}

void repo_cheltuieli_add(
	struct RepoCheltuieli *repo_cheltuieli,
	struct Cheltuiala cheltuiala
) {
	assert(repo_cheltuieli);
	int index = __repo_cheltuieli_find(repo_cheltuieli, cheltuiala.id);
	assert(index == -1);
	vec_push(&repo_cheltuieli->vec, cheltuiala);
}

void repo_cheltuieli_erase(
	struct RepoCheltuieli *repo_cheltuieli,
	int id
) {
	assert(repo_cheltuieli);
	int index = __repo_cheltuieli_find(repo_cheltuieli, id);
	assert(index != -1);
	vec_erase(&repo_cheltuieli->vec, index);
}

void repo_cheltuieli_update(
	struct RepoCheltuieli *repo_cheltuieli,
	struct Cheltuiala cheltuiala
) {
	assert(repo_cheltuieli);
	int index = __repo_cheltuieli_find(repo_cheltuieli, cheltuiala.id);
	assert(index != -1);
	vec_set(&repo_cheltuieli->vec, index, cheltuiala);
}

#endif // repo_h_INCLUDED

