#include "./repo.h"
#include "./vec.h"
#include "./domain.h"

struct RepoCheltuieli repo_cheltuieli_new() {
	struct RepoCheltuieli repo_cheltuieli;
	repo_cheltuieli.vec = vec_new();
	return repo_cheltuieli;
}

void repo_cheltuieli_drop(struct RepoCheltuieli *repo_cheltuieli) {
	assert(repo_cheltuieli);
	vec_drop(&repo_cheltuieli->vec);
}

int repo_cheltuieli_len(struct RepoCheltuieli *repo_cheltuieli) {
	return repo_cheltuieli->vec.len;
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

void test_repo_cheltuieli_len() {
	struct RepoCheltuieli repo_cheltuieli = repo_cheltuieli_new();
	struct Cheltuiala cheltuiala = cheltuiala_new(0, data_new(22, 1, 2014), 3.50, MANCARE);
	
	for (int i = 0; i < 100; ++i) {
		cheltuiala.id = i;
		repo_cheltuieli_add(&repo_cheltuieli, cheltuiala);
		assert(repo_cheltuieli_len(&repo_cheltuieli) == i+1);
	}
	
	repo_cheltuieli_drop(&repo_cheltuieli);
}

void test_repo_cheltuieli_find() {
	struct RepoCheltuieli repo_cheltuieli = repo_cheltuieli_new();
	struct Cheltuiala cheltuiala = cheltuiala_new(0, data_new(22, 1, 2014), 3.50, MANCARE);
	
	for (int i = 0; i < 10; ++i) {
		cheltuiala.id = i*3;
		repo_cheltuieli_add(&repo_cheltuieli, cheltuiala);
	}
	for (int i = 0; i < 10; ++i) {
		assert(__repo_cheltuieli_find(&repo_cheltuieli, i*3) != -1);
		assert(__repo_cheltuieli_find(&repo_cheltuieli, i*3+1) == -1);
		assert(__repo_cheltuieli_find(&repo_cheltuieli, i*3+2) == -1);
	}
	
	repo_cheltuieli_drop(&repo_cheltuieli);
}

void test_repo_cheltuieli_add() {
	struct RepoCheltuieli repo_cheltuieli = repo_cheltuieli_new();
	struct Cheltuiala cheltuiala = cheltuiala_new(0, data_new(22, 1, 2014), 3.50, MANCARE);
	
	for (int i = 0; i < 100; ++i) {
		cheltuiala.id = i;
		repo_cheltuieli_add(&repo_cheltuieli, cheltuiala);
		assert(repo_cheltuieli_len(&repo_cheltuieli) == i+1);
	}
	
	repo_cheltuieli_drop(&repo_cheltuieli);
}

void test_repo_cheltuieli_erase() {
	struct RepoCheltuieli repo_cheltuieli = repo_cheltuieli_new();
	struct Cheltuiala cheltuiala = cheltuiala_new(0, data_new(22, 1, 2014), 3.50, MANCARE);
	
	int len = 0;
	for (int i = 0; i < 100; ++i) {
		cheltuiala.id = i;
		repo_cheltuieli_add(&repo_cheltuieli, cheltuiala);
		len++;
	}
	for (int i = 0; i < 100; i += 2) {
		repo_cheltuieli_erase(&repo_cheltuieli, i); len--;
		assert(repo_cheltuieli_len(&repo_cheltuieli) == len);
	}
	for (int i = 1; i < 100; i += 2) {
		repo_cheltuieli_erase(&repo_cheltuieli, i); len--;
		assert(repo_cheltuieli_len(&repo_cheltuieli) == len);
	}
	
	repo_cheltuieli_drop(&repo_cheltuieli);
}

void test_repo_cheltuieli_update() {
	struct RepoCheltuieli repo_cheltuieli = repo_cheltuieli_new();
	struct Cheltuiala cheltuiala_1 = cheltuiala_new(0, data_new(22, 1, 2014), 3.50, MANCARE);
	struct Cheltuiala cheltuiala_2 = cheltuiala_new(0, data_new(22, 1, 2077), 1000, MANCARE);
	
	for (int i = 0; i < 100; ++i) {
		cheltuiala_1.id = i;
		repo_cheltuieli_add(&repo_cheltuieli, cheltuiala_1);
	}
	for (int i = 0; i < 100; i += 2) {
		cheltuiala_2.id = i;
		repo_cheltuieli_update(&repo_cheltuieli, cheltuiala_2);
	}
	for (int i = 1; i < 100; i += 2) {
		cheltuiala_2.id = i;
		repo_cheltuieli_update(&repo_cheltuieli, cheltuiala_2);
	}
	
	repo_cheltuieli_drop(&repo_cheltuieli);
}

void test_repo() {
	test_repo_cheltuieli_len();
	test_repo_cheltuieli_find();
	test_repo_cheltuieli_add();
	test_repo_cheltuieli_erase();
	test_repo_cheltuieli_update();
}
