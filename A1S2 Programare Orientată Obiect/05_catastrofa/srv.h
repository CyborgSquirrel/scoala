#ifndef srv_h_INCLUDED
#define srv_h_INCLUDED

#include "./repo.h"

extern const char *const ERR_NOTHING_TO_UNDO;

struct SrvCheltuieli {
	int last_id;
	struct RepoCheltuieli repo;
	
	struct Vec undo_stack;
};

// Creeaza un nou service de cheltuieli, cu repo-ul furnizat.
// in: repo -- repository de cheltuieli
// out: struct SrvCheltuieli -- service-ul de cheltuieli creat
struct SrvCheltuieli srv_cheltuieli_new(struct RepoCheltuieli repo);

// Dealoca un service de cheltuieli
// in: srv_cheltuieli -- pointer la service-ul care va fi dealocat
void srv_cheltuieli_drop(struct SrvCheltuieli *srv_cheltuieli);

// Adauga o noua cheltuiala, cu valorile furnizate.
// in: srv_cheltuieli -- pointer la service-ul in care se va adauga cheltuiala
//     data -- data la care s-a produs cheltuiala
//     suma -- suma cheltuielii
//     tip -- tipul cheltuielii
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const srv_cheltuieli_add(
	struct SrvCheltuieli *srv_cheltuieli,
	struct Data data, float suma, enum Tip tip
);

// Modifica cheltuiala cu id-ul furnizat, si ii atribuie valorile furnizate.
// in: srv_cheltuieli -- pointer la service-ul in care se va modifica cheltuiala
//     id -- id-ul cheltuielii
//     data -- data la care s-a produs cheltuiala
//     suma -- suma cheltuielii
//     tip -- tipul cheltuielii
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const srv_cheltuieli_update(
	struct SrvCheltuieli *srv_cheltuieli,
	int id, struct Data data, float suma, enum Tip tip
);

// Sterge cheltuiala cu id-ul furnizat din repo.
// in: srv_cheltuieli -- pointer la service-ul din care se va sterge cheltuiala
//     id -- id-ul cheltuielii
// out: str cu eroare, sau NULL daca nu au fost erori
const char *const srv_cheltuieli_erase(
	struct SrvCheltuieli *srv_cheltuieli,
	int id
);

// Returneaza toate cheltuielile.
// in: srv_cheltuieli -- pointer la service-ul al carui cheltuieli vor fi returnate
// out: struct Vec -- vector cu toate cheltuielile
struct Vec srv_cheltuieli_get_all(
	struct SrvCheltuieli *srv_cheltuieli
);

// Reface ultima operatie.
// in: srv_cheltuieli -- pointer la service-ul in care se va reface ultima operatie
const char *const srv_cheltuieli_undo(
	struct SrvCheltuieli *srv_cheltuieli
);

void test_srv();

#endif // srv_h_INCLUDED

