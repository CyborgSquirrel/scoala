#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>

using namespace std;

const TCheie NIL = -1000000000;
const TCheie ERASED = -1000000001;

int MD::h(TCheie c) const {
	if (c < 0) {
		TCheie a = -c;
		c += ((a / this->m) + 1) * this->m;
	}
	return c % this->m;
}

int MD::d(TCheie c, int i) const {
	// c1 = c2 = 0.5
	
	long long v1 = i;
	long long v2 = i+1;
	
	     if (v1 % 2 == 0) v1 /= 2;
	else if (v2 % 2 == 0) v2 /= 2;
	
	v1 %= this->m;
	v2 %= this->m;
	
	int x = ((long long) this->h(c) + v1*v2) % this->m;
	return x;
}

void MD::dbg() const {
	for (int i = 0; i < this->m; ++i) {
		if (this->buf[i].first != NIL && this->buf[i].first != ERASED) {
			cout << this->buf[i].first << " " << this->buf[i].second << endl;
		}
	}
	cout << endl;
}


MD::MD() {
	this->m = 16;
	this->_dim = 0;
	this->buf = new TElem[this->m];
	for (int i = 0; i < this->m; ++i) this->buf[i].first = NIL;
}


void MD::adauga(TCheie c, TValoare v) {
	this->_dim++;
	if (this->_dim > this->m) {
		int old_m = this->m;
		TElem *old_buf = this->buf;
		
		this->m *= 2;
		this->buf = new TElem[this->m];
		for (int i = 0; i < this->m; ++i) this->buf[i].first = NIL;
		
		for (int j = 0; j < old_m; ++j) {
			bool added = false;
			int i = 0;
			while (!added) {
				int p = this->d(old_buf[j].first, i);
				if (this->buf[p].first == NIL) {
					this->buf[p] = old_buf[j];
					added = true;
				} else {
					i++;
				}
			}
		}
		
		delete[] old_buf;
	}
	
	bool added = false;
	int i = 0;
	while (!added) {
		int p = this->d(c, i);
		if (this->buf[p].first == NIL || this->buf[p].first == ERASED) {
			this->buf[p] = { c, v };
			added = true;
		} else {
			i++;
		}
	}
}


bool MD::sterge(TCheie c, TValoare v) {
	bool erased = false;
	bool finished = false;
	int i = 0;
	while (!finished && i < this->m && !erased) {
		int p = this->d(c, i);
		if (this->buf[p].first == c && this->buf[p].second == v) {
			this->buf[p].first = ERASED;
			this->_dim--;
			erased = true;
		} else if (this->buf[p].first == NIL) {
			finished = true;
		} else {
			i++;
		}
	}
	return erased;
}


vector<TValoare> MD::cauta(TCheie c) const {
	vector<TValoare> v;
	bool finished = false;
	int i = 0;
	while (!finished && i < this->m) {
		int p = this->d(c, i);
		if (this->buf[p].first == c) {
			v.push_back(this->buf[p].second);
		} else if (this->buf[p].first == NIL) {
			finished = true;
		}
		i++;
	}
	return v;
}


int MD::dim() const {
	return this->_dim;
}


bool MD::vid() const {
	return this->_dim == 0;
}

IteratorMD MD::iterator() const {
	return IteratorMD(*this);
}


MD::~MD() {
	delete[] this->buf;
}

