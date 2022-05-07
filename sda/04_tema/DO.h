#pragma once

typedef int TCheie;
typedef int TValoare;

#define NULL_TVALOARE -1

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

class Iterator;

typedef  bool (*Conditie)(TCheie); 
typedef bool(*Relatie)(TCheie, TCheie);

extern const int NULL_NODE;
extern const int NULL_URM;
class Nod {
private:
	int urm;
	TElem elem;
	Nod();
public:
	friend class DO;
	// O(1)
	Nod(TElem elem, int urm);
	// O(1)
	TElem element() const;
	// O(1)
	int urmator();
};

class DO {
	friend class Iterator;
    private:
	/* aici e reprezentarea */
    int size;
	int d;
    Nod *buf;
    
	Relatie r;
	int prim;

    public:
    
    void dbg() const;
    
    DO() = delete;

	// O(1)
	// constructorul implicit al dictionarului
	DO(Relatie r);

	// O(n)
	// adauga o pereche (cheie, valoare) in dictionar
	//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	TValoare adauga(TCheie c, TValoare v);

	// O(n)
	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	TValoare cauta(TCheie c) const;


	// O(n)
	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	TValoare sterge(TCheie c);

	// O(n)
	// păstrează în dicționar numai acele perechi ale căror cheie respectă condiția dată 
	void filtreaza(Conditie cond); 

	// O(1)
	//returneaza numarul de perechi (cheie, valoare) din dictionar
	int dim() const;

	// O(1)
	//verifica daca dictionarul e vid
	bool vid() const;

	// O(1)
	// se returneaza iterator pe dictionar
	// iteratorul va returna perechile in ordine dupa relatia de ordine (pe cheie)
	Iterator iterator() const;


	// O(1)
	// destructorul dictionarului
	~DO();

};
