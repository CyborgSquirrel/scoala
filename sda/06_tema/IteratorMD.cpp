#include "IteratorMD.h"
#include "MD.h"
#include <iostream>

using namespace std;

void IteratorMD::skip() {
	while (
		this->index < this->md.m
		&& (this->md.buf[this->index].first == NIL
		|| this->md.buf[this->index].first == ERASED)
	) {
		this->index++;
	}
}

IteratorMD::IteratorMD(const MD& _md): md(_md) {
	this->index = 0;
	this->skip();
}

TElem IteratorMD::element() const{
	return this->md.buf[this->index];
}

bool IteratorMD::valid() const {
	return this->index < this->md.m;
}

void IteratorMD::urmator() {
	this->index++;
	this->skip();
}

void IteratorMD::prim() {
	this->index = 0;
	this->skip();
}

