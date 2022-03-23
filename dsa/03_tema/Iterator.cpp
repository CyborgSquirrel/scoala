#include "Iterator.h"
#include "DO.h"

using namespace std;

Iterator::Iterator(const DO& d) : dict(d){
	this->p = this->dict.prim;
}

void Iterator::prim(){
	this->p = this->dict.prim;
}

void Iterator::urmator(){
	this->p = this->p->urmator();
}

bool Iterator::valid() const{
	return this->p != nullptr;
}

TElem Iterator::element() const{
	return this->p->element();
}


