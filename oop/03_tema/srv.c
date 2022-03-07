#include "./domain.h"
#include "./repo.h"
#include "./srv.h"

struct SrvCheltuieli srv_cheltuieli_new(struct RepoCheltuieli repo) {
	struct SrvCheltuieli srv_cheltuieli;
	srv_cheltuieli.last_id = 0;
	srv_cheltuieli.repo = repo;
	return srv_cheltuieli;
}

void srv_cheltuieli_drop(struct SrvCheltuieli *srv_cheltuieli) {
	assert(srv_cheltuieli);
	repo_cheltuieli_drop(&srv_cheltuieli->repo);
}

void srv_cheltuieli_add(
	struct SrvCheltuieli *srv_cheltuieli,
	struct Data data, float suma, enum Tip tip
) {
	assert(srv_cheltuieli);
	struct Cheltuiala cheltuiala = cheltuiala_new(
		srv_cheltuieli->last_id,
		data, suma, tip
	);
	srv_cheltuieli->last_id++;
	repo_cheltuieli_add(&srv_cheltuieli->repo, cheltuiala);
}

void srv_cheltuieli_update(
	struct SrvCheltuieli *srv_cheltuieli,
	int id, struct Data data, float suma, enum Tip tip
) {
	assert(srv_cheltuieli);
	struct Cheltuiala cheltuiala = cheltuiala_new(
		id, data, suma, tip
	);
	repo_cheltuieli_update(&srv_cheltuieli->repo, cheltuiala);
}

void srv_cheltuieli_erase(
	struct SrvCheltuieli *srv_cheltuieli,
	int id
) {
	assert(srv_cheltuieli);
	repo_cheltuieli_erase(&srv_cheltuieli->repo, id);
}


void test_srv_cheltuieli_add() {
	struct SrvCheltuieli srv_cheltuieli = srv_cheltuieli_new(repo_cheltuieli_new());
	
	for (int i = 0; i < 100; ++i) {
		srv_cheltuieli_add(&srv_cheltuieli, data_new(12, 5, 2007), 95.32, ALTELE);
	}
	
	srv_cheltuieli_drop(&srv_cheltuieli);
}

void test_srv_cheltuieli_update() {
	struct SrvCheltuieli srv_cheltuieli = srv_cheltuieli_new(repo_cheltuieli_new());
	
	for (int i = 0; i < 100; ++i) {
		srv_cheltuieli_add(&srv_cheltuieli, data_new(12, 5, 2007), 95.32, ALTELE);
	}
	for (int i = 0; i < 100; ++i) {
		srv_cheltuieli_update(&srv_cheltuieli, i, data_new(14, 9, 2077), 1000.77, TELEFON_INTERNET);
	}
	
	srv_cheltuieli_drop(&srv_cheltuieli);
}

void test_srv_cheltuieli_erase() {
	struct SrvCheltuieli srv_cheltuieli = srv_cheltuieli_new(repo_cheltuieli_new());
	
	for (int i = 0; i < 100; ++i) {
		srv_cheltuieli_add(&srv_cheltuieli, data_new(12, 5, 2007), 95.32, ALTELE);
	}
	for (int i = 0; i < 100; ++i) {
		srv_cheltuieli_erase(&srv_cheltuieli, i);
	}
	
	srv_cheltuieli_drop(&srv_cheltuieli);
}

void test_srv() {
	test_srv_cheltuieli_add();
	test_srv_cheltuieli_update();
	test_srv_cheltuieli_erase();
}
