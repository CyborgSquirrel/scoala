#pragma once

#include <vector>
#include <string>

typedef int TCheie;
typedef int TValoare;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

class Nod {
	friend class IteratorMDO;
private:
	Relatie m_r;
	Nod *m_lt, *m_rt;
	TElem m_elem;
	// O(h)
	static Nod **minim(Nod **nod);
public:
	// O(1)
	Nod(Relatie r);
	
	// O(h)
	static void adauga(Nod **nod, TCheie c, TValoare v, Relatie r);
	
	// O(h)
	static void cauta(Nod *nod, TCheie c, vector<TValoare> &v);
	
	// O(h)
	static bool sterge(Nod **nod, TCheie c, TValoare v);
	
	// O(n)
	static void valori(Nod *nod, vector<TValoare> &v);
	
	// O(n)
	~Nod();
	
	static void dbg(Nod *nod, std::string indent="", std::string prefix="r");
};

class MDO {
	friend class IteratorMDO;
private:
	/* aici e reprezentarea */
	Relatie m_r;
	Nod *m_rad;
	int m_dim;
	
public:
	void dbg();

	// constructorul implicit al MultiDictionarului Ordonat
	// O(1)
	MDO(Relatie r);

	// adauga o pereche (cheie, valoare) in MDO
	// O(h)
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	// O(h)
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	// O(h)
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MDO 
	// O(1)
	int dim() const;

	//verifica daca MultiDictionarul Ordonat e vid 
	// O(1)
	bool vid() const;

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	// O(h)
	IteratorMDO iterator() const;

	// destructorul 	
	// O(n)
	~MDO();

	// O(n)
	vector<TValoare> colectiaValorilor() const;
};
