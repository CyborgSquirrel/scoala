#ifndef repo_h_INCLUDED
#define repo_h_INCLUDED

#include "./vec.h"

extern const char *const ERR_CHELTUIALA_IN_REPO;
extern const char *const ERR_CHELTUIALA_NOT_IN_REPO;

struct RepoCheltuieli {
	struct Vec vec;
};

// Creeaza un nou repository de cheltuieli.
// out: struct RepoCheltuieli
struct RepoCheltuieli repo_cheltuieli_new();

// Dealoca un repository de cheltuieli.
// in: repo_cheltuieli -- repo-ul care va fi dealocat
void repo_cheltuieli_drop(struct RepoCheltuieli *repo_cheltuieli);

// Returneaza numarul de elemente in repo.
// in: repo_cheltuieli -- pointer la repo-ul al carui lungime va fi returnata
// out: int -- lungimea repo-ului
int repo_cheltuieli_len(struct RepoCheltuieli *repo_cheltuieli);

// Adauga o noua cheltuiala in repo.
// in: repo_cheltuieli -- pointer la repo-ul in care se va adauga cheltuiala
//     cheltuiala -- cheltuiala care va fi adaugata in repo
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const repo_cheltuieli_add(
	struct RepoCheltuieli *repo_cheltuieli,
	struct Cheltuiala cheltuiala
);

// Sterge o cheltuiala din repo.
// in: repo_cheltuieli -- pointer la repo-ul din care se va sterge cheltuiala
//     id -- id-ul cheltuielii care va fi stearsa din repo
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const repo_cheltuieli_erase(
	struct RepoCheltuieli *repo_cheltuieli,
	int id
);

// Modifica o cheltuiala in repo.
// in: repo_cheltuieli -- pointer la repo-ul din care se va sterge cheltuiala
//     cheltuiala -- cheltuiala care va fi modificata in repo
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const repo_cheltuieli_update(
	struct RepoCheltuieli *repo_cheltuieli,
	struct Cheltuiala cheltuiala
);

// Returneaza toate cheltuielile din repo.
// in: repo_cheltuieli -- pointer la repo-ul al carui cheltuieli vor fi returnate
// out: struct Vec -- vector cu toate cheltuielile din repo
struct Vec repo_cheltuieli_get_all(
	struct RepoCheltuieli *repo_cheltuieli
);

void test_repo();

#endif // repo_h_INCLUDED

