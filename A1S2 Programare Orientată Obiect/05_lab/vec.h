#pragma once
#ifndef VEC_H_
#define VEC_H_

#include <stdlib.h>
#include <assert.h>

typedef void* ElemType;
typedef ElemType (*CopyFn)(ElemType);
typedef void (*DestroyFn)(ElemType);

typedef struct {
	int cp, lg;
	ElemType elems;
	
	int element_size;
	CopyFn element_copy;
	DestroyFn element_destroy;
} Vec;

/*
 * Creeaza un nou vector, care stocheaza un tip generic.
 * input : element_size - sizeof al elementului (in octeti)
 *         element_copy - functie care face copie al unui element
 *         element_destroy - functie care dealoca un element
 * output: pointer la Vec
 */
Vec* create_empty(
	int element_size,
	CopyFn element_copy,
	DestroyFn element_destroy
);

/*
 * Dealoca un vector, si toate elementele lui.
 * input : vec - pointer la vectorul care va fi dealocat
 * output: -
 */
void destroy_vec(Vec* vec);

/*
 * Extrage un element din vector.
 * input : vec - pointer la vectorul din care se extrage elementul
 *         value - pointer la locul in care se va salva elementul extras
 *         index - indicele elementului care sa fie extras
 * output: 0, daca operatiunea a fost efectuata cu succes, si -3 altfel
 */
int vec_get(
	Vec* vec,
	ElemType value,
	int index
);

/*
 * Adauga un element la sfarsitul vectorului.
 * input : vec - pointer la vectorul la sfarsitul caruia se adauga elementul
 *         value - pointer la elementul care va fi adaugat
 * output: -
 */
void vec_push(
	Vec* vec,
	ElemType value
);

/*
 * Atribuie unui element din vector, la indicele specificat, valoarea furnizata.
 * input : vec - pointer la vectorul in care se va face atribuirea
 *         index - indicele elementului caruia i se atribuie valoarea
 *         value - valoarea care va fi atribuita elementului din vector
 * output: 0, daca operatiunea a fost efectuata cu succes, si -4 altfel
 */
int vec_set(
	Vec* vec,
	int index,
	ElemType value
);

/*
 * Extrage elementul de la finalul vectorului.
 * input : vec - pointer la vectorul in care se va face atribuirea
 *         value - pointer la valoarea in care va fi salvat elementul extras
 * output: 0, daca operatiunea a fost efectuata cu succes, si -7 altfel
 */
int vec_pop(
	Vec* vec,
	ElemType value
);

/*
 * Sterge un element din vector, la indicele specificat.
 * input : vec - pointer la vectorul din care se va face stergerea
 *         index - indicele elementului care va fi sters
 * output: 0, daca operatiunea a fost efectuata cu succes, si -5 altfel
 */
int vec_erase(
	Vec* vec,
	int index
);

/*
 * Creeaza o copie a vectorului furnizat.
 * input : vec - pointer la vectorul care va fi copiat
 * output: pointer la copia vectorului
 */
Vec* copy_vec(
	Vec* vec
);

#endif // !VEC_H_

