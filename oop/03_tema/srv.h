#ifndef srv_h_INCLUDED
#define srv_h_INCLUDED

#include "./repo.h"

struct SrvCheltuieli {
	int last_id;
	struct RepoCheltuieli repo;
};

struct SrvCheltuieli srv_cheltuieli_new() {
	struct SrvCheltuieli srv_cheltuieli;
	srv_cheltuieli.last_id = 0;
	srv_cheltuieli.repo = repo_cheltuieli_new();
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

#endif // srv_h_INCLUDED

