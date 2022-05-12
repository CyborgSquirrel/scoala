#pragma once
#include<vector>
#include<utility>

using namespace std;

typedef int TCheie;
typedef int TValoare;

extern const TCheie NIL;
extern const TCheie ERASED;

typedef std::pair<TCheie, TValoare> TElem;

class IteratorMD;
class IteratorValori;

class MD
{
	friend class IteratorMD;
	friend class IteratorValori;

private:
	/* aici e reprezentarea */
	
	// intotdeauna putere a lui 2
	int m;
	int _dim;
	TElem *buf;
	
	// O(1)
	int h(TCheie c) const;
	// O(1)
	int d(TCheie c, int i) const;

public:
	void dbg() const;

	// constructorul implicit al MultiDictionarului
	// O(1)
	MD();

	// adauga o pereche (cheie, valoare) in MD
	// O(n)
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	// O(n)
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	// O(n)
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MD 
	// O(1)
	int dim() const;

	//verifica daca MultiDictionarul e vid 
	// O(1)
	bool vid() const;

	// se returneaza iterator pe MD
	// O(n)
	IteratorMD iterator() const;

	// destructorul MultiDictionarului
	// O(1)
	~MD();

	// creeaza un iterator peste valorile asociate cheii k. În cazul în care k nu este în multidicționar, iteratorul va fi nevalid imediate dupa creare. În caz contrar, elementul curent este prima valoare asociată cheii.
	// O(n)
	IteratorValori iterator(TCheie k);
};

