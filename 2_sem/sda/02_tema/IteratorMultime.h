#pragma once

class Multime;
typedef int TElem;

class IteratorMultime
{
	friend class Multime;
private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorMultime(Multime& m);

	//contine o referinta catre containerul pe care il itereaza
	Multime& multime;
	/* aici e reprezentarea  specifica a iteratorului */
	Multime *p;

public:

		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();
		
		// elimină și returnează elementul curent referit de iterator 
		//după efectuarea operației, elementul curent referit de iterator este următorul element din mulțime, sau, în cazul în care elementul eliminat a fost ultimul, iterator devine nevalid 
		// aruncă excepție în cazul în care iteratorul este nevalid 
		TElem elimina();

		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElem element() const;
};
