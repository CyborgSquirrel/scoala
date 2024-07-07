#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>

using namespace std;

class Sesiune {
private:
	shared_ptr<vector<string>> attendants;
public:
	Sesiune() : attendants(new vector<string>) { }
	Sesiune(Sesiune &other) {
		attendants = other.attendants;
	}
	~Sesiune() = default;
	vector<string>::iterator begin() {
		return attendants->begin();
	}
	vector<string>::iterator end() {
		return attendants->end();
	}
	Sesiune operator+(const string &a) {
		attendants->push_back(a);
		return *this;
	}
	vector<string> select(const string &f) {
		vector<string> v;
		for (const auto &a : *attendants) {
			if (a.find(f) != string::npos) {
				v.push_back(a);
			}
		}
		return v;
	}
};

class Conferinta {
private:
	map<string, Sesiune> m;
public:
	Sesiune track(string s) {
		if (m.count(s) == 0) {
			m[s] = Sesiune();
		}
		return m[s];
	}
};

int main() {
	Conferinta conf;
	// add 2 attendats to "Artificial Intelligence" track
	conf.track("Artificial Intelligence") + "Ion Ion" + "Vasile Aron";
	// add 2 attendants to "Software" track
	Sesiune& s = conf.track("Software");
	s + "Anar Lior" + "Aurora Bran";
	// print all attendants from group "Artificial Intelligence" track
	for (auto name : conf.track("Artificial Intelligence")) {
		cout << name << ",";
	}
	// find and print all names from Software track that contain "ar"
	vector<string> v = conf.track("Software").select("ar");
	for (auto name : v) { cout << name << ","; }
}
