#include "IteratorMultime.h"
#include "Multime.h"

// O(1)
IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
	this->p = &m;
}

// O(1)
void IteratorMultime::prim() {
	this->p = &this->multime;
}

// O(1)
void IteratorMultime::urmator() {
	this->p = this->p->next;
}

// O(1)
TElem IteratorMultime::element() const {
	return this->p->elem;
}

// O(1)
bool IteratorMultime::valid() const {
	return this->p != nullptr && !this->p->head_and_empty;
}
