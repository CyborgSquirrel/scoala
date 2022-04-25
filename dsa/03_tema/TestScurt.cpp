#include <assert.h>
#include <iostream>

#include "DO.h"
#include "Iterator.h"

#include <exception>

#include <vector>

using namespace std;

bool relatie1(TCheie cheie1, TCheie cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

bool cond1(TCheie cheie) {
	return cheie % 2 == 0;
}

bool cond2(TCheie cheie) {
	return cheie < 11;
}

void testAll(){
	DO dictOrd = DO(relatie1);
	assert(dictOrd.dim() == 0);
	assert(dictOrd.vid());
    dictOrd.adauga(1,2);
    assert(dictOrd.dim() == 1);
    assert(!dictOrd.vid());
    assert(dictOrd.cauta(1)!=NULL_TVALOARE);
    TValoare v =dictOrd.adauga(1,3);
    assert(v == 2);
    assert(dictOrd.cauta(1) == 3);
    Iterator it = dictOrd.iterator();
    it.prim();
    while (it.valid()){
    	TElem e = it.element();
    	assert(e.second != NULL_TVALOARE);
    	it.urmator();
    }
    assert(dictOrd.sterge(1) == 3);
    assert(dictOrd.vid());
    
    DO dictOrd2 = DO(relatie1);
    vector<TValoare> vec { 1, 2, 123, 123, 3, 1, 9, 1, 123, 5, 3, 6, 123, 7, 123, 43, 5425, 234, 54, 34 };
    for (size_t i = 0; i < vec.size(); ++i) {
    	dictOrd2.adauga((TCheie) i, vec[i]);
    }
    
    dictOrd2.filtreaza(cond1);
    Iterator it2 = dictOrd2.iterator();
    while (it2.valid()) {
    	assert(it2.element().first % 2 == 0);
    	it2.urmator();
    }
    
    it2.prim();
    dictOrd2.filtreaza(cond2);
    while (it2.valid()) {
    	assert(it2.element().first % 2 == 0 && it2.element().first < 11);
    	it2.urmator();
    }
}

