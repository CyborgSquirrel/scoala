#include <vector>

using namespace std;

class Transformer {
public:
	virtual void transform(vector<int> &nrs) = 0;
	Transformer() = default;
	virtual ~Transformer() = default;
};

class Composite : public Transformer {
private:
	Transformer *t1, *t2;
public:
	Composite(Transformer *t1, Transformer *t2)
	: t1(t1), t2(t2)
	{ }
	~Composite() {
		delete t1;
		delete t2;
	}
	void transform(vector<int> &nrs) override {
		t1->transform(nrs);
		t2->transform(nrs);
	}
};

class Adder : public Transformer {
private:
	int cat;
public:
	void transform(vector<int> &nrs) override {
		for (auto &nr : nrs) {
			nr += cat;
		}
	}
	Adder (int cat) : cat {cat} { }
};

class Nuller : public Adder {
public:
	void transform(vector<int> &nrs) override {
		Adder::transform(nrs);
		for (auto &nr : nrs) {
			if (nr > 10) {
				nr = 0;
			}
		}
	}
	Nuller (int cat) : Adder {cat} { }
};

class Swapper : public Transformer {
public:
	void transform(vector<int> &nrs) override {
		for (int i = 1; i < nrs.size(); ++i) {
			swap(nrs[i-1], nrs[i]);
		}
	}
};

class Numbers {
private:
	Transformer *t;
	vector<int> v;
public:
	Numbers(Transformer *t) : t(t) { }
	void addd(int a) { v.push_back(a); }
	vector<int> transform() {
		t->transform(v);
		return v;
	}
	~Numbers() {
		delete t;
	}
};

Numbers *f() {
	return new Numbers { new Composite { new Nuller {9}, new Composite { new Swapper, new Adder {3} } } };
}

int main() {
	Numbers *n1, *n2;
	n1 = f(); n2 = f();
	n1->addd(1);
	n1->addd(3);
	n1->addd(4);
	n1->addd(7);
	n1->addd(2);
	n2->addd(10);
	n2->addd(2);
	n2->addd(9);
	n2->addd(4);
	n2->addd(7);
	n1->transform();
	n2->transform();
	delete n1;
	delete n2;
	return 0;
}
