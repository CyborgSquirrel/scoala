#pragma once

#include "MDO.h"
#include <vector>


class IteratorMDO{
	friend class MDO;
private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	// O(h)
	IteratorMDO(const MDO& dictionar);

	//contine o referinta catre containerul pe care il itereaza
	const MDO& m_dict;
	/* aici e reprezentarea  specifica a iteratorului */
	vector<Nod*> m_stiva;
public:

		//reseteaza pozitia iteratorului la inceputul containerului
		// O(h)
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		// O(h)
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		// O(1)
		bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		// O(1)
		TElem element() const;
};

