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

void IteratorValori::skip() {
	while (
		this->i < this->md._dim
		&& this->md.buf[this->md.d(this->k, this->i)].first != this->k
	) {
		this->i++;
	}
}

IteratorValori::IteratorValori(const MD& c, TCheie k) : md(c) {
	this->k = k;
	this->i = 0;
	this->skip();
}

void IteratorValori::prim() {
	this->i = 0;
}

void IteratorValori::urmator() {
	this->i++;
	this->skip();
}

bool IteratorValori::valid() const {
	return this->i < this->md._dim
		&& this->md.buf[this->md.d(this->k, this->i)].first != NIL;
}

TValoare IteratorValori::element() const {
	return this->md.buf[this->md.d(this->k, this->i)].second;
}

