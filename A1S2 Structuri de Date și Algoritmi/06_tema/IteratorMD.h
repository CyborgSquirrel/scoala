#pragma once
#include "MD.h"

class MD;

class IteratorMD
{
	friend class MD;

private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	// O(n)
	IteratorMD(const MD& c);

	//contine o referinta catre containerul pe care il itereaza
	const MD& md;

	/* aici e reprezentarea  specifica a iteratorului */
	int index;

	// O(n)
	void skip();

public:

	//reseteaza pozitia iteratorului la inceputul containerului
	// O(1)
	void prim();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	// O(n)
	void urmator();

	//verifica daca iteratorul e valid (indica un element al containerului)
	// O(1)
	bool valid() const;

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	// O(1)
	TElem element() const;
};

class IteratorValori
{
	friend class MD;

private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorValori(const MD& c, TCheie k);

	//contine o referinta catre containerul pe care il itereaza
	const MD& md;

	/* aici e reprezentarea  specifica a iteratorului */
	TCheie k;
	int i;

	// O(n)
	void skip();

public:

	//reseteaza pozitia iteratorului la inceputul containerului
	// O(1)
	void prim();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	// O(n)
	void urmator();

	//verifica daca iteratorul e valid (indica un element al containerului)
	// O(1)
	bool valid() const;

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	// O(1)
	TValoare element() const;
};
