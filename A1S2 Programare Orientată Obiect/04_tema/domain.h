#ifndef domain_h_INCLUDED
#define domain_h_INCLUDED

#include <stdio.h>
#include <stdlib.h>

enum Tip { MANCARE, TRANSPORT, TELEFON_INTERNET, IMBRACAMINTE, ALTELE };

// Converteste un tip in reprezentarea sa ca string.
// in: tip -- tipul pentru care se va returna reprezentarea ca string
// out: str -- reprezentarea ca string a tipului
char *tip_as_str(enum Tip tip);

struct Data {
	int zi, luna, an;
};

// Creeaza o noua data, cu parametrii specificati.
// in: zi -- ziua datii
//     luna -- luna datii
//     an -- anul datii
// out: struct Data -- data creata
struct Data data_new(int zi, int luna, int an);

// Verifica daca doua dati sunt egale.
// in: lhs -- pointer la data care va fi comparata
//     rhs -- pointer la data care va fi comparata
// out: int -- 1 daca datile sunt egale, 0 altfel
int data_eq(struct Data *lhs, struct Data *rhs);

// Verifica daca prima data este inaintea celei de-a doua.
// in: lhs -- pointer la data care va fi comparata
//     rhs -- pointer la data care va fi comparata
// out: int -- 1 daca prima data este inaintea celei de-a doua, 0 altfel
int data_before(struct Data *lhs, struct Data *rhs);

// Verifica daca prima data este dupa celei de-a doua.
// in: lhs -- pointer la data care va fi comparata
//     rhs -- pointer la data care va fi comparata
// out: int -- 1 daca prima data este dupa celei de-a doua, 0 altfel
int data_after(struct Data *lhs, struct Data *rhs);

// Afiseaza data furnizata in fluxul furnizat.
// in: file -- fluxul in care se va afisa data (de exemplu: stdout)
//     data -- data care va fi afisata
void data_print(FILE *file, struct Data *data);

struct Cheltuiala {
	int id;
	struct Data data;
	float suma;
	enum Tip tip;
};

// Creeaza o cheltuiala noua.
// in: id -- id-ul cheltuielii
//     data -- data la care s-a produs cheltuiala
//     suma -- suma cheltuielii
//     tip -- tipul cheltuielii
// out: struct Cheltuiala -- cheltuiala creata
struct Cheltuiala cheltuiala_new(
	int id, struct Data data, float suma, enum Tip tip
);

// Verifica daca doua cheltuieli sunt egale.
// in: lhs -- cheltuiala care va fi comparata
//     rhs -- cheltuiala care va fi comparata
// out: int -- 1 daca cheltuielile sunt egale, 0 altfel
int cheltuiala_eq(struct Cheltuiala *lhs, struct Cheltuiala *rhs);

// Afiseaza cheltuiala furnizata in fluxul furnizat.
// in: file -- fluxul in care se va afisa cheltuiala (de exemplu: stdout)
//     cheltuiala -- cheltuiala care va fi afisata
void cheltuiala_print(FILE *file, struct Cheltuiala *cheltuiala);

void test_domain(void);

#endif // domain_h_INCLUDED

