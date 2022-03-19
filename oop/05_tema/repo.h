#ifndef repo_h_INCLUDED
#define repo_h_INCLUDED

#include "./vec.h"
#include "./domain.h"

extern const char *const ERR_CHELTUIALA_IN_REPO;
extern const char *const ERR_CHELTUIALA_NOT_IN_REPO;

struct RepoCheltuieli {
	struct Vec vec;
};

// Creeaza un nou repository de cheltuieli.
// out: struct RepoCheltuieli
struct RepoCheltuieli repo_cheltuieli_new();

// Dealoca un repository de cheltuieli.
// in: pointer to struct RepoCheltuieli
void repo_cheltuieli_drop(struct RepoCheltuieli *repo_cheltuieli);

// Returneaza numarul de elemente in repo.
// in: pointer to struct RepoCheltuieli
// out: int
int repo_cheltuieli_len(struct RepoCheltuieli *repo_cheltuieli);

// Adauga o noua cheltuiala in repo.
// in: pointer to struct RepoCheltuieli
//     struct Cheltuiala
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const repo_cheltuieli_add(
	struct RepoCheltuieli *repo_cheltuieli,
	struct Cheltuiala cheltuiala
);

// Sterge o cheltuiala din repo.
// in: pointer to struct RepoCheltuieli
//     int
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const repo_cheltuieli_erase(
	struct RepoCheltuieli *repo_cheltuieli,
	int id
);

// Modifica o cheltuiala in repo.
// in: pointer to struct RepoCheltuieli
//     struct Cheltuiala
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const repo_cheltuieli_update(
	struct RepoCheltuieli *repo_cheltuieli,
	struct Cheltuiala cheltuiala
);

// Returneaza toate cheltuielile din repo.
// in: pointer to struct RepoCheltuieli
// out: struct Vec
struct Vec repo_cheltuieli_get_all(
	struct RepoCheltuieli *repo_cheltuieli
);

void test_repo();

#endif // repo_h_INCLUDED

