#include "TestScurt.h"
#include "MD.h"
#include "IteratorMD.h"
#include <assert.h>
#include <vector>
#include <iostream>

void testAll() {
	MD m;
	m.adauga(1, 100);
	m.adauga(2, 200);
	m.adauga(3, 300);
	m.adauga(1, 500);
	m.adauga(2, 600);
	m.adauga(4, 800);

	assert(m.dim() == 6);

	assert(m.sterge(5, 600) == false);
	assert(m.sterge(1, 500) == true);

	assert(m.dim() == 5);

    vector<TValoare> v;
	v=m.cauta(6);
	assert(v.size()==0);

	v=m.cauta(1);
	assert(v.size()==1);

	assert(m.vid() == false);

	IteratorMD im = m.iterator();
	assert(im.valid() == true);
	while (im.valid()) {
		im.element();
		im.urmator();
	}
	assert(im.valid() == false);
	im.prim();
	assert(im.valid() == true);
	
	MD m2;
	m2.adauga(1, 100);
	m2.adauga(1, 200);
	m2.adauga(2, 300);
	m2.adauga(7, 100);
	m2.adauga(1, 999);
	m2.adauga(1, 200);
	m2.adauga(7, 10);
	m2.adauga(1, 23);
	
	IteratorValori iv = m2.iterator(1);
	assert(iv.valid());
	assert(iv.element() == 100); iv.urmator();
	assert(iv.element() == 200); iv.urmator();
	assert(iv.element() == 999); iv.urmator();
	assert(iv.element() == 200); iv.urmator();
	assert(iv.element() == 23); iv.urmator();
	assert(!iv.valid());
	
	IteratorValori iv2 = m2.iterator(6);
	assert(!iv2.valid());
	
	IteratorValori iv3 = m2.iterator(7);
	assert(iv3.element() == 100); iv3.urmator();
	assert(iv3.element() == 10); iv3.urmator();
	assert(!iv3.valid());
}
