#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Smoothy {
protected:
	int pret;
public:
	virtual ~Smoothy() = default;
	virtual int getPret() {
		return pret;
	}
	virtual string descriere() = 0;
};

class DecoratorSmoothy : public Smoothy {
protected:
	Smoothy *smooty;
public:
	DecoratorSmoothy(Smoothy *smooty)
	: smooty(smooty)
	{ }
	~DecoratorSmoothy() {
		delete smooty;
	}
	int getPret() override {
		return smooty->getPret();
	}
	string descriere() override {
		return smooty->descriere();
	}
};

class SmoothyCuFrisca : public DecoratorSmoothy {
public:
	SmoothyCuFrisca(Smoothy *smooty)
	: DecoratorSmoothy(smooty)
	{ }
	string descriere() override {
		return smooty->descriere() + " cu frisca";
	}
	int getPret() override {
		return smooty->getPret() + 2;
	}
};

class SmoothyCuUmbreluta : public DecoratorSmoothy {
public:
	SmoothyCuUmbreluta(Smoothy *smooty)
	: DecoratorSmoothy(smooty)
	{ }
	string descriere() override {
		return smooty->descriere() + " cu umbreluta";
	}
	int getPret() override {
		return smooty->getPret() + 3;
	}
};

class BasicSmoothy : public Smoothy {
private:
	string nume;
public:
	BasicSmoothy(int pret, string nume)
	: nume(nume)
	{
		this->pret = pret;
	}
	string descriere() override {
		return nume;
	}
};

vector<Smoothy*> getSmoothies() {
	vector<Smoothy*> v;
	v.push_back(new SmoothyCuUmbreluta { new SmoothyCuFrisca { new BasicSmoothy {5, "de kivi"} } });
	v.push_back(new SmoothyCuFrisca { new BasicSmoothy {10, "de capsuni"} });
	v.push_back(new BasicSmoothy {5, "de kivi"});
	return v;
}

int main() {
	vector<Smoothy*> smoothies = getSmoothies();
	for (const auto smoothy : smoothies) {
		cout << smoothy->descriere() << " " << smoothy->getPret() << endl;
	}
	while (!smoothies.empty()) {
		delete smoothies.back();
		smoothies.pop_back();
	}
	
	return 0;
}
