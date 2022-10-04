#include "IteratorMDO.h"
#include "MDO.h"

IteratorMDO::IteratorMDO(const MDO& d) : m_dict(d){
	Nod *nod = m_dict.m_rad;
	while (nod != nullptr) {
		m_stiva.push_back(nod);
		nod = nod->m_lt;
	}
}

void IteratorMDO::prim(){
	m_stiva.clear();
	
	Nod *nod = m_dict.m_rad;
	while (nod != nullptr) {
		m_stiva.push_back(nod);
		nod = nod->m_lt;
	}
}

void IteratorMDO::urmator(){
	if (!m_stiva.empty()) {
		Nod *nod = m_stiva.back();
		m_stiva.pop_back();
		if (nod->m_rt != nullptr) {
			nod = nod->m_rt;
			while (nod != nullptr) {
				m_stiva.push_back(nod);
				nod = nod->m_lt;
			}
		}
	}
}

bool IteratorMDO::valid() const{
	return !m_stiva.empty();
}

TElem IteratorMDO::element() const{
	return m_stiva.front()->m_elem;
}


