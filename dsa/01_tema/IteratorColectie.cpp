#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	this->index = this->col.lo - this->col.actual_lo;
	this->freq = 0;
}

void IteratorColectie::prim() {
	this->index = this->col.lo - this->col.actual_lo;
	this->freq = 0;
}


void IteratorColectie::urmator() {
	this->freq++;
	if (this->freq >= this->col.buf[this->index]) {
		this->index++;
		this->freq = 0;
		while (this->index <= this->col.hi - this->col.actual_lo && this->col.buf[this->index] == 0) {
			this->index++;
		}
	}
}


bool IteratorColectie::valid() const {
	if (this->col.num_dim == 0) return false;
	return this->index <= this->col.hi - this->col.actual_lo;
}



TElem IteratorColectie::element() const {
	return this->col.actual_lo + this->index;
}
