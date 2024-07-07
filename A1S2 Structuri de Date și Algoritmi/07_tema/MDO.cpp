#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

const TElem NULL_TELEM = { -100000000, -100000000 };

Nod::Nod(Relatie r) {
	m_r = r;
	m_elem = NULL_TELEM;
	m_lt = nullptr;
	m_rt = nullptr;
}
void Nod::adauga(Nod **nod, TCheie c, TValoare v, Relatie r) {
	if (*nod == nullptr) {
		*nod = new Nod(r);
		(*nod)->m_elem = { c, v };
	} else {
		if (r(c, (*nod)->m_elem.first)) {
			Nod::adauga(&(*nod)->m_lt, c, v, r);
		} else {
			Nod::adauga(&(*nod)->m_rt, c, v, r);
		}
	}
}
void Nod::cauta(Nod *nod, TCheie c, vector<TValoare> &v) {
	if (nod != nullptr) {
		if (c == nod->m_elem.first) {
			v.push_back(nod->m_elem.second);
		}
		if (nod->m_r(c, nod->m_elem.first)) {
			Nod::cauta(nod->m_lt, c, v);
		} else {
			Nod::cauta(nod->m_rt, c, v);
		}
	}
}
Nod **Nod::minim(Nod **nod) {
	if ((*nod)->m_lt == nullptr) {
		return nod;
	} else {
		return Nod::minim(&(*nod)->m_lt);
	}
}
bool Nod::sterge(Nod **nod, TCheie c, TValoare v) {
	if (*nod != nullptr) {
		if (c == (*nod)->m_elem.first && v == (*nod)->m_elem.second) {
			bool has_lt = (*nod)->m_lt != nullptr;
			bool has_rt = (*nod)->m_rt != nullptr;
			
			if (has_lt && has_rt) {
				Nod **minim = Nod::minim(&(*nod)->m_rt);
				(*nod)->m_elem = (*minim)->m_elem;
				Nod::sterge(minim, (*minim)->m_elem.first, (*minim)->m_elem.second);
			} else {
				Nod *temp = *nod;
				if (!has_lt && !has_rt) {
					*nod = nullptr;
				} else if (has_lt && !has_rt) {
					*nod = (*nod)->m_lt;
				} else if (!has_lt && has_rt) {
					*nod = (*nod)->m_rt;
				}
				temp->m_lt = temp->m_rt = nullptr;
				delete temp;
			}
			
			return true;
		} else {
			if ((*nod)->m_r(c, (*nod)->m_elem.first)) {
				return Nod::sterge(&(*nod)->m_lt, c, v);
			} else {
				return Nod::sterge(&(*nod)->m_rt, c, v);
			}
		}
	}
	return false;
}
void Nod::valori(Nod *nod, vector<TValoare> &v) {
	if (nod != nullptr) {
		Nod::valori(nod->m_lt, v);
		v.push_back(nod->m_elem.second);
		Nod::valori(nod->m_rt, v);
	}
}
Nod::~Nod() {
	if (m_lt != nullptr) {
		delete m_lt;
	}
	if (m_rt != nullptr) {
		delete m_rt;
	}
}
void Nod::dbg(Nod *nod, std::string indent, std::string prefix) {
	if (nod != nullptr) {
		cout << indent << prefix << ": " << nod->m_elem.first << ":" << nod->m_elem.second << endl;
		Nod::dbg(nod->m_lt, indent+"   ", "lt");
		Nod::dbg(nod->m_rt, indent+"   ", "rt");
	}
}

void MDO::dbg() {
	Nod::dbg(this->m_rad);
	cout << endl;
}

MDO::MDO(Relatie r) {
	m_r = r;
	m_rad = nullptr;
	m_dim = 0;
}


void MDO::adauga(TCheie c, TValoare v) {
	Nod::adauga(&m_rad, c, v, m_r);
	m_dim++;
}

vector<TValoare> MDO::cauta(TCheie c) const {
	vector<TValoare> v;
	Nod::cauta(m_rad, c, v);
	return v;
}

bool MDO::sterge(TCheie c, TValoare v) {
	bool sters = Nod::sterge(&m_rad, c, v);
	if (sters) {
		m_dim--;
	}
	return sters;
}

int MDO::dim() const {
	return m_dim;
}

bool MDO::vid() const {
	return m_dim == 0;
}

IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}

MDO::~MDO() {
	if (m_rad != nullptr) {
		delete m_rad;
	}
}

vector<TValoare> MDO::colectiaValorilor() const {
	std::vector<TValoare> v;
	Nod::valori(m_rad, v);
	return v;
}
