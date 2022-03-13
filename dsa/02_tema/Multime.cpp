#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

Multime::Multime() {
	this->next = nullptr;
	this->elem = NULL_TELEM;
	this->head_and_empty = true;
 }
 
 void Multime::dbg() {
	std::cout << "[ ";
	if (!this->head_and_empty) {
		Multime *p = this;
		while (p->next != nullptr) {
			std::cout << p->elem << " ";
			p = p->next;
		}
		std::cout << p->elem << " ";
	}
	std::cout << "]" << std::endl;
 }

// O(n)
bool Multime::adauga(TElem elem) {
	if (this->head_and_empty) {
		this->elem = elem;
		this->head_and_empty = false;
		return true;
	}
	
	Multime *p = this;
	while (p->next != nullptr) {
		if (elem == p->elem) return false;
		p = p->next;
	}
	if (elem == p->elem) return false;
	p->next = new Multime;
	p = p->next;
	p->elem = elem;
	p->head_and_empty = false;
	return true;
}

// O(n)
bool Multime::sterge(TElem elem) {
	if (this->head_and_empty) return false;
	
	if (this->elem == elem) {
		if (this->next == nullptr) {
			this->head_and_empty = true;
		} else {
			Multime *next = this->next;
			this->elem = next->elem;
			this->next = next->next;
			next->next = nullptr;
			delete next;
		}
		return true;
	}
	
	Multime *p = this;
	while (p->next != nullptr) {
		Multime *next = p->next;
		if (elem == next->elem) {
			p->next = next->next;
			/// VERY IMPORTANT
			// next->next must be nullptr, because otherwise, when it is
			// deleted, it will call its destructor, and yeet the whole
			// list
			next->next = nullptr;
			delete next;
			return true;
		}
		p = p->next;
	}
	return false;
}

// O(n)
bool Multime::cauta(TElem elem) const {
	if (this->head_and_empty) return false;
	const Multime *p = this;
	while (p->next != nullptr) {
		if (elem == p->elem) return true;
		p = p->next;
	}
	return elem == p->elem;
}

// O(n)
int Multime::dim() const {
	if (this->head_and_empty) return 0;
	int dim = 1;
	const Multime *p = this;
	while (p->next != nullptr) {
		p = p->next;
		dim++;
	}
	return dim;
}

// O(1)
bool Multime::vida() const {
	return this->head_and_empty;
}

// O(n)
Multime::~Multime() {
	Multime *p = this;
	while (p->next != nullptr) {
		Multime *q = p;
		p = p->next;
		if (q != this) {
			/// VERY IMPORTANT
			// look at sterge to see the reason for this
			q->next = nullptr;
			delete q;
		}
	}
	if (p != this) delete p;
}

// O(1)
IteratorMultime Multime::iterator() {
	return IteratorMultime(*this);
}

