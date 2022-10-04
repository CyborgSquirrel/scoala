#include <string>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Payable {
private:
	string ID;
public:
	Payable(const string &id)
	: ID(id)
	{ }
	virtual ~Payable() = default;
	const string &getID() { return ID; }
	virtual double monthlyIncome() = 0;
	string toString() {
		return ID + " " + to_string(monthlyIncome());
	}
};

class Student : public Payable {
private:
	double scholarship;
public:
	Student(const string &id, double scholarship)
	: Payable(id), scholarship(scholarship)
	{ }
	double monthlyIncome() override {
		return scholarship;
	}
};

class Teacher : public Payable {
private:
	double salary;
public:
	Teacher(const string &id, double salary)
	: Payable(id), salary(salary)
	{ }
	double monthlyIncome() override {
		return salary;
	}
};

class DuplicatedIDException {
private:
	string msg;
public:
	DuplicatedIDException(const string &msg)
	: msg(msg)
	{ }
	const string &getMessage() { return msg; }
};

class University {
private:
	string name;
	vector<Payable*> payables;
public:
	University(const string &name)
	: name(name)
	{ }
	Payable *findPayableByID(const string &id) {
		for (const auto payable : payables) {
			if (payable->getID() == id) {
				return payable;
			}
		}
		return nullptr;
	}
	void addPayable(Payable *p) {
		for (const auto payable : payables) {
			if (payable->getID() == p->getID()) {
				throw DuplicatedIDException {"a payable with the provided ID already exists"};
			}
		}
		payables.push_back(p);
	}
	vector<Payable*> getAllPayables() {
		return payables;
	}
	double totalAmountToPay() {
		double total = 0;
		for (const auto payable : payables) {
			total += payable->monthlyIncome();
		}
		return total;
	}
	~University() {
		while (!payables.empty()) {
			auto payable = payables.back();
			payables.pop_back();
			delete payable;
		}
	}
};

int main() {
	University u("UBB");
	u.addPayable(new Student { "Andrei", 100 });
	u.addPayable(new Student { "Ion", 120 });
	u.addPayable(new Student { "Mihai", 0 });
	u.addPayable(new Teacher { "David", 500 });
	u.addPayable(new Teacher { "Alexandru", 550 });
	auto payables = u.getAllPayables();
	for (const auto payable : payables) {
		cout << payable->toString() << endl;
	}
	cout << "total: " << u.totalAmountToPay() << endl;
	Payable *p = new Student { "Andrei", 200 };
	try {
		u.addPayable(p);
	} catch (const DuplicatedIDException &ex) {
		delete p;
	}
}
