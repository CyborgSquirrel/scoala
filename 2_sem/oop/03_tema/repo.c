#include "./repo.h"
#include "./vec.h"
#include "./domain.h"

const char *const ERR_CHELTUIALA_IN_REPO = "cheltuiala furnizata este deja in repo";
const char *const ERR_CHELTUIALA_NOT_IN_REPO = "cheltuiala cu indicele furnizat nu exista in repo";

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
	assert(repo_cheltuieli);
	return repo_cheltuieli->vec.len;
}

int __repo_cheltuieli_find(
	struct RepoCheltuieli *repo_cheltuieli,
	int id
) {
	assert(repo_cheltuieli);
	for (int i = 0; i < repo_cheltuieli->vec.len; ++i) {
		struct Cheltuiala cheltuiala;
		assert(vec_get(&repo_cheltuieli->vec, &cheltuiala, i) == NULL);
		if (cheltuiala.id == id) {
			return i;
		}
	}
	return -1;
}

const char *const repo_cheltuieli_add(
	struct RepoCheltuieli *repo_cheltuieli,
	struct Cheltuiala cheltuiala
) {
	assert(repo_cheltuieli);
	int index = __repo_cheltuieli_find(repo_cheltuieli, cheltuiala.id);
	if (index != -1) return ERR_CHELTUIALA_IN_REPO;
	vec_push(&repo_cheltuieli->vec, cheltuiala);
	return NULL;
}

const char *const repo_cheltuieli_erase(
	struct RepoCheltuieli *repo_cheltuieli,
	int id
) {
	assert(repo_cheltuieli);
	int index = __repo_cheltuieli_find(repo_cheltuieli, id);
	if (index == -1) return ERR_CHELTUIALA_NOT_IN_REPO;
	assert(vec_erase(&repo_cheltuieli->vec, index) == NULL);
	return NULL;
}

const char *const repo_cheltuieli_update(
	struct RepoCheltuieli *repo_cheltuieli,
	struct Cheltuiala cheltuiala
) {
	assert(repo_cheltuieli);
	int index = __repo_cheltuieli_find(repo_cheltuieli, cheltuiala.id);
	if (index == -1) return ERR_CHELTUIALA_NOT_IN_REPO;
	assert(vec_set(&repo_cheltuieli->vec, index, cheltuiala) == NULL);
	return NULL;
}

void test_repo_cheltuieli_len() {
	struct RepoCheltuieli repo_cheltuieli = repo_cheltuieli_new();
	struct Cheltuiala cheltuiala = cheltuiala_new(0, data_new(22, 1, 2014), 3.50, MANCARE);
	
	for (int i = 0; i < 100; ++i) {
		cheltuiala.id = i;
		assert(repo_cheltuieli_add(&repo_cheltuieli, cheltuiala) == NULL);
		assert(repo_cheltuieli_len(&repo_cheltuieli) == i+1);
	}
	
	repo_cheltuieli_drop(&repo_cheltuieli);
}

void test_repo_cheltuieli_find() {
	struct RepoCheltuieli repo_cheltuieli = repo_cheltuieli_new();
	struct Cheltuiala cheltuiala = cheltuiala_new(0, data_new(22, 1, 2014), 3.50, MANCARE);
	
	for (int i = 0; i < 10; ++i) {
		cheltuiala.id = i*3;
		assert(repo_cheltuieli_add(&repo_cheltuieli, cheltuiala) == NULL);
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
		assert(repo_cheltuieli_add(&repo_cheltuieli, cheltuiala) == NULL);
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
		assert(repo_cheltuieli_add(&repo_cheltuieli, cheltuiala) == NULL);
		len++;
	}
	for (int i = 0; i < 100; i += 2) {
		assert(repo_cheltuieli_erase(&repo_cheltuieli, i) == NULL);
		len--;
		assert(repo_cheltuieli_len(&repo_cheltuieli) == len);
	}
	for (int i = 1; i < 100; i += 2) {
		assert(repo_cheltuieli_erase(&repo_cheltuieli, i) == NULL);
		len--;
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
		assert(repo_cheltuieli_add(&repo_cheltuieli, cheltuiala_1) == NULL);
	}
	for (int i = 0; i < 100; i += 2) {
		cheltuiala_2.id = i;
		assert(repo_cheltuieli_update(&repo_cheltuieli, cheltuiala_2) == NULL);
	}
	for (int i = 1; i < 100; i += 2) {
		cheltuiala_2.id = i;
		assert(repo_cheltuieli_update(&repo_cheltuieli, cheltuiala_2) == NULL);
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
