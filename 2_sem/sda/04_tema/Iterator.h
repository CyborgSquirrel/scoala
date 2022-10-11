#pragma once

#include "DO.h"

class Iterator{
	friend class DO;
private:
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	Iterator(const DO& dictionar);

	//contine o referinta catre containerul pe care il itereaza
	const DO& dict;

	/* aici e reprezentarea specifica a iteratorului */
	int p;

public:

		// O(1)
		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();

		// O(1)
		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();

		// O(1)
		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid() const;

		// O(1)
		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElem element() const;
};
