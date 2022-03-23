#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;

Nod::Nod(TElem elem, Nod *urm) {
	this->elem = elem;
	this->urm = urm;
}

TElem Nod::element() const {
	return this->elem;
}

Nod *Nod::urmator() {
	return this->urm;
}


DO::DO(Relatie r) {
	this->r = r;
	this->prim = nullptr;
	this->d = 0;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
	Nod **p = &this->prim;
	while (*p != nullptr && this->r((*p)->elem.first, c)) {
		if ((*p)->elem.first == c) {
			TValoare old_v = (*p)->elem.second;
			(*p)->elem.second = v;
			return old_v;
		}
		p = &((*p)->urm);
	}
	
	this->d += 1;
	*p = new Nod(make_pair(c, v), *p);
	
	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
	Nod * const*p = &this->prim;
	while (*p != nullptr && this->r((*p)->elem.first, c)) {
		if ((*p)->elem.first == c) {
			return (*p)->elem.second;
		}
		p = &((*p)->urm);
	}
	return NULL_TVALOARE;
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
	Nod **p = &this->prim;
	while (*p != nullptr && this->r((*p)->elem.first, c)) {
		if ((*p)->elem.first == c) {
			this->d -= 1;
			
			Nod *urm = (*p)->urm;
			TValoare v = (*p)->elem.second;
			
			delete *p;
			(*p) = urm;
			
			return v;
		}
		p = &((*p)->urm);
	}
	
	return NULL_TVALOARE;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
	return this->d;
}

//verifica daca dictionarul e vid
bool DO::vid() const {
	return this->d == 0;
}

Iterator DO::iterator() const {
	return  Iterator(*this);
}

DO::~DO() {
	Nod *p = this->prim;
	while (p != nullptr) {
		Nod *q = p;
		p = p->urm;
		delete q;
	}
}
