#include "IteratorMultime.h"
#include "Multime.h"

// θ(1)
IteratorMultime::IteratorMultime(Multime& m) : multime(m){
	this->p = &m;
}

// θ(1)
void IteratorMultime::prim() {
	this->p = &this->multime;
}

// θ(1)
void IteratorMultime::urmator() {
	this->p = this->p->next;
}

// θ(n)
TElem IteratorMultime::elimina() {
	if (this->p != nullptr && !this->p->head_and_empty) {
		TElem elem = this->p->elem;
		if (this->p != &this->multime) {
			this->p = this->p->next;
		}
		this->multime.sterge(elem);
		return elem;
	} else {
		throw "Iterator invalid.";
	}
}

// θ(1)
TElem IteratorMultime::element() const {
	return this->p->elem;
}

// θ(1)
bool IteratorMultime::valid() const {
	return this->p != nullptr && !this->p->head_and_empty;
}
