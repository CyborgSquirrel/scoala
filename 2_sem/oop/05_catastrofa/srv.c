#include "./domain.h"
#include "./repo.h"
#include "./srv.h"

const char *const ERR_NOTHING_TO_UNDO = "nu mai exista operatii care sa fie refacute";

struct SrvCheltuieli srv_cheltuieli_new(struct RepoCheltuieli repo) {
	struct SrvCheltuieli srv_cheltuieli;
	srv_cheltuieli.last_id = 0;
	srv_cheltuieli.repo = repo;
	srv_cheltuieli.undo_stack = vec_new(
		sizeof(struct RepoCheltuieli),
		repo_cheltuieli_clone_generic,
		repo_cheltuieli_drop_generic
	);
	return srv_cheltuieli;
}

void srv_cheltuieli_drop(struct SrvCheltuieli *srv_cheltuieli) {
	assert(srv_cheltuieli);
	repo_cheltuieli_drop(&srv_cheltuieli->repo);
	vec_drop(&srv_cheltuieli->undo_stack);
}

const char *const srv_cheltuieli_add(
	struct SrvCheltuieli *srv_cheltuieli,
	struct Data data, float suma, enum Tip tip
) {
	const char *err = NULL;
	assert(srv_cheltuieli);
	struct Cheltuiala cheltuiala = cheltuiala_new(
		srv_cheltuieli->last_id,
		data, suma, tip
	);
	srv_cheltuieli->last_id++;
	
	struct RepoCheltuieli repo_clone;
	repo_cheltuieli_clone(&repo_clone, &srv_cheltuieli->repo);
	
	if ((err = repo_cheltuieli_add(&srv_cheltuieli->repo, cheltuiala)) != NULL) {
		repo_cheltuieli_drop(&repo_clone);
		return err;
	}
	
	vec_push(&srv_cheltuieli->undo_stack, &repo_clone);
	repo_cheltuieli_drop(&repo_clone);
	
	return NULL;
}

const char *const srv_cheltuieli_update(
	struct SrvCheltuieli *srv_cheltuieli,
	int id, struct Data data, float suma, enum Tip tip
) {
	const char *err = NULL;
	assert(srv_cheltuieli);
	struct Cheltuiala cheltuiala = cheltuiala_new(
		id, data, suma, tip
	);
	
	struct RepoCheltuieli repo_clone;
	repo_cheltuieli_clone(&repo_clone, &srv_cheltuieli->repo);
	
	if ((err = repo_cheltuieli_update(&srv_cheltuieli->repo, cheltuiala)) != NULL) {
		repo_cheltuieli_drop(&repo_clone);
		return err;
	}
	
	vec_push(&srv_cheltuieli->undo_stack, &repo_clone);
	repo_cheltuieli_drop(&repo_clone);
	
	return NULL;
}

const char *const srv_cheltuieli_erase(
	struct SrvCheltuieli *srv_cheltuieli,
	int id
) {
	const char *err = NULL;
	assert(srv_cheltuieli);
	
	struct RepoCheltuieli repo_clone;
	repo_cheltuieli_clone(&repo_clone, &srv_cheltuieli->repo);
	
	if ((err = repo_cheltuieli_erase(&srv_cheltuieli->repo, id)) != NULL) {
		repo_cheltuieli_drop(&repo_clone);
		return err;
	}
	
	vec_push(&srv_cheltuieli->undo_stack, &repo_clone);
	repo_cheltuieli_drop(&repo_clone);
	
	return NULL;
}

struct Vec srv_cheltuieli_get_all(
	struct SrvCheltuieli *srv_cheltuieli
) {
	assert(srv_cheltuieli);
	return repo_cheltuieli_get_all(&srv_cheltuieli->repo);
}

const char *const srv_cheltuieli_undo(
	struct SrvCheltuieli *srv_cheltuieli
) {
	const char *err = NULL;
	assert(srv_cheltuieli);
	if (srv_cheltuieli->undo_stack.len == 0) return ERR_NOTHING_TO_UNDO;
	
	repo_cheltuieli_drop(&srv_cheltuieli->repo);
	
	err = vec_get(
		&srv_cheltuieli->undo_stack,
		(void *) &srv_cheltuieli->repo,
		srv_cheltuieli->undo_stack.len-1
	);
	assert(err == NULL);
	
	err = vec_erase(&srv_cheltuieli->undo_stack, srv_cheltuieli->undo_stack.len-1);
	assert(err == NULL);
	
	return NULL;
}

void test_srv_cheltuieli_add(void) {
	struct SrvCheltuieli srv_cheltuieli = srv_cheltuieli_new(repo_cheltuieli_new());
	
	for (int i = 0; i < 100; ++i) {
		assert(srv_cheltuieli_add(&srv_cheltuieli, data_new(12, 5, 2007), 95.32, ALTELE) == NULL);
	}
	
	srv_cheltuieli_drop(&srv_cheltuieli);
}

void test_srv_cheltuieli_update(void) {
	struct SrvCheltuieli srv_cheltuieli = srv_cheltuieli_new(repo_cheltuieli_new());
	
	for (int i = 0; i < 100; ++i) {
		assert(srv_cheltuieli_add(&srv_cheltuieli, data_new(12, 5, 2007), 95.32, ALTELE) == NULL);
	}
	for (int i = 0; i < 100; ++i) {
		assert(srv_cheltuieli_update(&srv_cheltuieli, i, data_new(14, 9, 2077), 1000.77, TELEFON_INTERNET) == NULL);
	}
	assert(srv_cheltuieli_update(&srv_cheltuieli, 200, data_new(14, 9, 2077), 1000.77, TELEFON_INTERNET) == ERR_CHELTUIALA_NOT_IN_REPO);
	
	srv_cheltuieli_drop(&srv_cheltuieli);
}

void test_srv_cheltuieli_erase(void) {
	struct SrvCheltuieli srv_cheltuieli = srv_cheltuieli_new(repo_cheltuieli_new());
	
	for (int i = 0; i < 100; ++i) {
		assert(srv_cheltuieli_add(&srv_cheltuieli, data_new(12, 5, 2007), 95.32, ALTELE) == NULL);
	}
	for (int i = 0; i < 100; ++i) {
		assert(srv_cheltuieli_erase(&srv_cheltuieli, i) == NULL);
	}
	assert(srv_cheltuieli_erase(&srv_cheltuieli, 200) == ERR_CHELTUIALA_NOT_IN_REPO);
	
	srv_cheltuieli_drop(&srv_cheltuieli);
}

void test_srv_cheltuieli_get_all(void) {
	struct SrvCheltuieli srv_cheltuieli = srv_cheltuieli_new(repo_cheltuieli_new());
	struct Data data = data_new(22, 1, 2014);
	float suma = 3.50;
	enum Tip tip = MANCARE;
	
	for (int i = 0; i < 100; ++i) {
		srv_cheltuieli_add(&srv_cheltuieli, data, suma, tip);
	}
	
	struct Vec vec = srv_cheltuieli_get_all(&srv_cheltuieli);
	for (int i = 0; i < 100; ++i) {
		struct Cheltuiala cheltuiala = cheltuiala_new(i, data, suma, tip);
		struct Cheltuiala cheltuiala_get;
		vec_get(&vec, &cheltuiala_get, i);
		assert(cheltuiala_eq(&cheltuiala, &cheltuiala_get));
	}
	vec_drop(&vec);
	
	srv_cheltuieli_drop(&srv_cheltuieli);
}

void test_srv_cheltuieli_undo(void) {
	struct SrvCheltuieli srv_cheltuieli = srv_cheltuieli_new(repo_cheltuieli_new());
	
	struct Data data = data_new(22, 1, 2014);
	float suma = 3.50;
	enum Tip tip = MANCARE;
	
	assert(srv_cheltuieli_undo(&srv_cheltuieli) == ERR_NOTHING_TO_UNDO);
	
	srv_cheltuieli_add(&srv_cheltuieli, data, suma, tip);
	srv_cheltuieli_update(&srv_cheltuieli, 0, data, suma+1, tip);
	srv_cheltuieli_erase(&srv_cheltuieli, 0);
	
	assert(srv_cheltuieli_undo(&srv_cheltuieli) == NULL);
	assert(repo_cheltuieli_len(&srv_cheltuieli.repo) == 1);
	
	assert(srv_cheltuieli_undo(&srv_cheltuieli) == NULL);
	assert(repo_cheltuieli_len(&srv_cheltuieli.repo) == 1);
	
	assert(srv_cheltuieli_undo(&srv_cheltuieli) == NULL);
	assert(repo_cheltuieli_len(&srv_cheltuieli.repo) == 0);
	
	assert(srv_cheltuieli_undo(&srv_cheltuieli) == ERR_NOTHING_TO_UNDO);
	
	srv_cheltuieli_drop(&srv_cheltuieli);
}

void test_srv() {
	test_srv_cheltuieli_add();
	test_srv_cheltuieli_update();
	test_srv_cheltuieli_erase();
	test_srv_cheltuieli_get_all();
	test_srv_cheltuieli_undo();
}
