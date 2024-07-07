#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Meniu {
protected:
	int pret;
public:
	virtual ~Meniu() = default;
	virtual string descriere() = 0;
	virtual int getPret() {
		return pret;
	}
};

class CuCafea : public Meniu {
private:
	Meniu *meniu;
public:
	CuCafea(Meniu *meniu) : meniu(meniu) { }
	~CuCafea() {
		delete meniu;
	}
	string descriere() override {
		return meniu->descriere() + " cu cafea";
	}
	int getPret() override {
		return meniu->getPret() + 5;
	}
};

class CuRacoritoare : public Meniu {
private:
	Meniu *meniu;
public:
	CuRacoritoare(Meniu *meniu) : meniu(meniu) { }
	~CuRacoritoare() {
		delete meniu;
	}
	string descriere() override {
		return meniu->descriere() + " cu racoritoare";
	}
	int getPret() override {
		return meniu->getPret() + 4;
	}
};

class MicDejun : public Meniu {
private:
	string denumire;
public:
	MicDejun(string denumire, int pret) : denumire(denumire) { this->pret = pret; }
	string descriere() override {
		return denumire;
	}
};

vector<Meniu*> f() {
	vector<Meniu*> meniuri;
	
	meniuri.push_back(
		new CuRacoritoare { new CuCafea { new MicDejun { "Omleta", 15 } } }
	);
	meniuri.push_back(
		new CuCafea { new MicDejun { "Ochiuri", 10 } }
	);
	meniuri.push_back(
		new MicDejun { "Omleta", 15 }
	);
	
	return meniuri;
}

int main() {
	vector<Meniu*> comanda = f();
	sort(
		comanda.begin(), comanda.end(),
		[](Meniu *lhs, Meniu *rhs) { return lhs->getPret() > rhs->getPret(); }
	);
	for (const auto meniu : comanda) {
		cout << meniu->descriere() << endl;
	}
	
	return 0;
}
