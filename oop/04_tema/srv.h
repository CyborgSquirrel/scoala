#ifndef srv_h_INCLUDED
#define srv_h_INCLUDED

#include "./repo.h"

struct SrvCheltuieli {
	int last_id;
	struct RepoCheltuieli repo;
};

// Creeaza un nou service de cheltuieli, cu repo-ul furnizat.
// in: struct RepoCheltuieli
// out: struct SrvCheltuieli
struct SrvCheltuieli srv_cheltuieli_new(struct RepoCheltuieli repo);

// Dealoca un service de cheltuieli
// in: pointer to SrvCheltuieli
void srv_cheltuieli_drop(struct SrvCheltuieli *srv_cheltuieli);

// Adauga o noua cheltuiala in repo, cu valorile furnizate.
// in: pointer to SrvCheltuieli
//     struct Data
//     float
//     enum Tip
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const srv_cheltuieli_add(
	struct SrvCheltuieli *srv_cheltuieli,
	struct Data data, float suma, enum Tip tip
);

// Modifica cheltuiala din repo cu id-ul furnizat, si ii atribuie valorile furnizate.
// in: pointer to struct SrvCheltuieli
//     int
//     struct Data
//     float
//     enum Tip
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const srv_cheltuieli_update(
	struct SrvCheltuieli *srv_cheltuieli,
	int id, struct Data data, float suma, enum Tip tip
);

// Sterge cheltuiala cu id-ul furnizat din repo.
// in: pointer to struct SrvCheltuieli
//     int
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const srv_cheltuieli_erase(
	struct SrvCheltuieli *srv_cheltuieli,
	int id
);

// Returneaza toate cheltuielile din repo.
// in: pointer to struct SrvCheltuieli
// out: struct Vec
struct Vec srv_cheltuieli_get_all(
	struct SrvCheltuieli *srv_cheltuieli
);

void test_srv();

#endif // srv_h_INCLUDED

