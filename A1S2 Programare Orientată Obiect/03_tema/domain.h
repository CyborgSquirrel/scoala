#ifndef domain_h_INCLUDED
#define domain_h_INCLUDED

#include <stdio.h>
#include <stdlib.h>

enum Tip { MANCARE, TRANSPORT, TELEFON_INTERNET, IMBRACAMINTE, ALTELE };

// Converteste un tip in reprezentarea sa ca string.
// in: tip -- tipul pentru care se va returna reprezentarea ca string
// out: pointer to char -- reprezentarea ca string a tipului
char *tip_as_str(enum Tip tip);

struct Data {
	int zi, luna, an;
};

// Creeaza o noua data, cu parametrii specificati.
// in: zi -- int
//     luna -- int
//     an -- int
// out: struct Data
struct Data data_new(int zi, int luna, int an);

// Verifica daca doua dati sunt egale.
// in: lhs -- pointer to struct Data
//     rhs -- pointer to struct Data
// out: int, 1 daca datile sunt egale, 0 altfel
int data_eq(struct Data *lhs, struct Data *rhs);

// Afiseaza data furnizata pe stdout.
// in: data -- pointer to struct Data
void data_print(struct Data *data);

struct Cheltuiala {
	int id;
	struct Data data;
	float suma;
	enum Tip tip;
};

// Creeaza o cheltuiala noua.
// in: id -- int
//     data -- struct Data
//     suma -- float
//     tip -- enum Tip
// out: struct Cheltuiala
struct Cheltuiala cheltuiala_new(
	int id, struct Data data, float suma, enum Tip tip
);

// Verifica daca doua cheltuieli sunt egale.
// in: lhs -- pointer to struct Cheltuiala
//     rhs -- pointer to struct Cheltuiala
// out: int, 1 daca cheltuielile sunt egale, 0 altfel
int cheltuiala_eq(struct Cheltuiala *lhs, struct Cheltuiala *rhs);

// Afiseaza cheltuiala furnizata pe stdout.
// in: cheltuiala -- pointer to struct Cheltuiala
void cheltuiala_print(struct Cheltuiala *cheltuiala);

void test_domain(void);

#endif // domain_h_INCLUDED

