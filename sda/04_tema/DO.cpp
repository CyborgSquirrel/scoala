#include "Iterator.h"
#include "DO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

const int NULL_NODE = -2;
const int NULL_URM = -1;
Nod::Nod() { this->elem.second = NULL_TVALOARE; this->urm = NULL_NODE; }

Nod::Nod(TElem elem, int urm) {
	this->elem = elem;
	this->urm = urm;
}

TElem Nod::element() const {
	return this->elem;
}

int Nod::urmator() {
	return this->urm;
}

void DO::dbg() const {
	// std::cout << "prim: " << this->prim << std::endl;
	// for (int i = 0; i < this->size; ++i) {
	// 	std::cout << this->buf[i].elem.first << " " << this->buf[i].elem.second << " " << this->buf[i].urm << std::endl;
	// }
	// std::cout << std::endl;
	int const*p = &this->prim;
	while (*p >= 0) {
		std::cout << this->buf[*p].elem.first << " ";
		p = &this->buf[*p].urm;
	}
	std::cout << std::endl;
}


DO::DO(Relatie r) {
	this->size = 10;
	this->d = 0;
	this->buf = new Nod[this->size];
	this->r = r;
	this->prim = -1;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
	int *p = &this->prim;
	while (*p >= 0 && this->r(this->buf[*p].elem.first, c)) {
		if (this->buf[*p].elem.first == c) {
			TValoare old_v = this->buf[*p].elem.second;
			this->buf[*p].elem.second = v;
			return old_v;
		}
		p = &this->buf[*p].urm;
	}
	
	this->d += 1;
	int q;
	if (this->d > this->size) { q = this->size; }
	else {
		for (int i = 0; i < this->size; ++i) {
			if (this->buf[i].urm == NULL_NODE) {
				q = i;
				break;
			}
		}
	}
	int old_p = *p;
	*p = q;
	
	if (this->d > this->size) {
		int old_size = this->size;
		Nod *old_buf = this->buf;
		this->size *= 2;
		this->buf = new Nod[this->size];
		for (int i = 0; i < old_size; ++i) {
			this->buf[i] = old_buf[i];
		}
		delete[] old_buf;
	}
	
	buf[q] = Nod(make_pair(c, v), old_p);
	
	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
	int const*p = &this->prim;
	while (*p >= 0 && this->r(this->buf[*p].elem.first, c)) {
		if (this->buf[*p].elem.first == c) {
			return this->buf[*p].elem.second;
		}
		p = &this->buf[*p].urm;
	}
	return NULL_TVALOARE;
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
	int *p = &this->prim;
	while (*p >= 0 && this->r(this->buf[*p].elem.first, c)) {
		if (this->buf[*p].elem.first == c) {
			this->d -= 1;
			
			int urm = this->buf[*p].urm;
			TValoare v = this->buf[*p].elem.second;
			
			this->buf[*p].elem.second = NULL_TVALOARE;
			this->buf[*p].urm = NULL_NODE;
			*p = urm;
			
			return v;
		}
		p = &this->buf[*p].urm;
	}
	
	return NULL_TVALOARE;
}

void DO::filtreaza(Conditie cond) {
	int *p = &this->prim;
	while (*p >= 0) {
		if (!cond(this->buf[*p].elem.first)) {
			this->d -= 1;
			
			int urm = this->buf[*p].urm;
			
			this->buf[*p].elem.second = NULL_TVALOARE;
			this->buf[*p].urm = NULL_NODE;
			*p = urm;
		} else {
			p = &this->buf[*p].urm;
		}
	}
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
	return Iterator(*this);
}

DO::~DO() {
	delete[] this->buf;
}
