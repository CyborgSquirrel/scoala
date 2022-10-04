#include <assert.h>

#include "MDO.h"
#include "IteratorMDO.h"

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

void testAll(){
	MDO dictOrd = MDO(relatie1);
	assert(dictOrd.dim() == 0);
	assert(dictOrd.vid());
    dictOrd.adauga(1,2);
    dictOrd.adauga(1,3);
    assert(dictOrd.dim() == 2);
    assert(!dictOrd.vid());
    vector<TValoare> v= dictOrd.cauta(1);
    assert(v.size()==2);
    v= dictOrd.cauta(3);
    assert(v.size()==0);
    IteratorMDO it = dictOrd.iterator();
    it.prim();
    while (it.valid()){
    	TElem e = it.element();
    	it.urmator();
    }
    assert(dictOrd.sterge(1, 2) == true);
    assert(dictOrd.sterge(1, 3) == true);
    assert(dictOrd.sterge(2, 1) == false);
    assert(dictOrd.vid());
    
    MDO dict = MDO(relatie1);
	dict.adauga(4, 4);
	dict.adauga(5, 5);
	dict.adauga(3, 3);
	dict.adauga(1, 1);
	dict.adauga(9, 9);
	dict.adauga(10, 10);
	dict.adauga(5, 5);
	dict.adauga(6, 6);
	dict.adauga(2, 2);
	dict.adauga(5, 5);
	dict.adauga(8, 8);
	dict.adauga(7, 7);
	
	vector<TValoare> c = dict.colectiaValorilor();
	vector<TValoare> cc = { 1, 2, 3, 4, 5, 5, 5, 6, 7, 8, 9, 10 };
	assert(c == cc);
}

