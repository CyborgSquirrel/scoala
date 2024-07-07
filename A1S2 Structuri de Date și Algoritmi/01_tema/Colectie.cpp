#include "Colectie.h"
#include "IteratorColectie.h"
#include <algorithm>
#include <cstddef>
#include <exception>
#include <iostream>

using namespace std;

Colectie::Colectie() {
	// rezervam spatiu pentru 8 elemente la inceput
	this->size = 8;
	this->buf = new TElem[this->size];
	for (int i = 0; i < this->size; ++i){
		this->buf[i] = 0;
	}
	this->num_dim = 0;
}


void Colectie::dbg() {
	cout << this->actual_lo << " [ ";
	for (int i = 0; i < this->size; ++i) {
		cout << this->buf[i] << " ";
	}
	cout << " ] " << this->actual_lo+int(this->size)-1;
	cout << endl;
}

// O(n)
// θ(1)
void Colectie::adauga(TElem elem) {
	if (this->num_dim == 0) {
		this->lo = this->hi = elem;
		int leftover = this->size - (this->hi - this->lo + 1);
		this->actual_lo = this->lo - leftover/2 - leftover%2;
	} else {
		TElem norm = elem - this->actual_lo;
		if (norm < 0 || norm >= this->size) {
			size_t exact_new_size =
				  max(this->actual_lo+int(this->size)-1, elem)
				- min(this->actual_lo, elem) + 1;
			
			TElem *old_buf = this->buf;
			int old_actual_lo = this->actual_lo;
			size_t old_size = this->size;
			
			while (this->size <= exact_new_size) {
				this->size *= 2;
			}
			
			this->buf = new TElem[this->size];
			this->lo = min(this->lo, elem);
			this->hi = max(this->hi, elem);
			int leftover = this->size - (this->hi - this->lo + 1);
			this->actual_lo = this->lo - leftover/2 - leftover%2;
			
			int offset = old_actual_lo-this->actual_lo;
			for (int i = 0; i < this->size; ++i){
				if (i >= offset && i < offset+int(old_size)) {
					this->buf[i] = old_buf[i-offset];
				} else {
					this->buf[i] = 0;
				}
			}
			
			delete [] old_buf;
		}
	}
	this->lo = min(this->lo, elem);
	this->hi = max(this->hi, elem);
	this->buf[elem-this->actual_lo]++;
	this->num_dim++;
}

// O(n)
// θ(1)
bool Colectie::sterge(TElem elem) {
	if (this->num_dim == 0) return false;
	TElem norm = elem - this->actual_lo;
	if (norm >= 0 && norm < this->size) {
		if (this->buf[norm] > 0) {
			this->buf[norm]--;
			this->num_dim--;
			
			if (this->buf[norm] == 0 && this->num_dim != 0) {
				if (elem == this->lo) {
					while (norm+1 < this->size && this->buf[norm] == 0) {
						norm++;
					}
					this->lo = this->actual_lo + norm;
				} else if (elem == this->hi) {
					while (norm > 0 && this->buf[norm] == 0) {
						norm--;
					}
					this->hi = this->actual_lo + norm;
				}
			}
			
			return true;
		} else {
			return false;
		}
	}
	return false;
}

// O(1)
bool Colectie::cauta(TElem elem) const {
	if (this->num_dim == 0) return false;
	TElem norm = elem - this->actual_lo;
	if (norm >= 0 && norm < this->size) {
		return this->buf[norm] > 0;
	}
	return false;
}

// O(1)
int Colectie::nrAparitii(TElem elem) const {
	if (this->num_dim == 0) return 0;
	TElem norm = elem - this->actual_lo;
	if (norm >= 0 && norm < this->size) {
		return this->buf[norm];
	}
	return 0;
}

// O(1)
int Colectie::dim() const {
	return this->num_dim;
}

// O(1)
bool Colectie::vida() const {
	return this->num_dim == 0;
}

IteratorColectie Colectie::iterator() const {
	return IteratorColectie(*this);
}

Colectie::~Colectie() {
	delete [] this->buf;
}


