#ifndef valid_h_INCLUDED
#define valid_h_INCLUDED

#include "./domain.h"

// Verifica daca o data este valida.
// in: struct Data
// out: int, 1 daca data este valida, 0 altfel
int validate_data(struct Data *data);

// Verifica daca o suma este valida.
// in: float
// out: int, 1 daca suma este valida, 0 altfel
int validate_suma(float suma);

void test_validate();

#endif // valid_h_INCLUDED

