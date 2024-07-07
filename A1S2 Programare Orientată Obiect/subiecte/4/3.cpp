#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

class Channel {
private:
public:
	virtual ~Channel() = default;
	virtual void send(const string &msg) = 0;
};

class Failover : public Channel {
private:
	Channel *c1, *c2;
public:
	Failover(Channel *c1, Channel *c2)
	: c1(c1), c2(c2)
	{ }
	~Failover() {
		delete c1;
		delete c2;
	}
	void send(const string &msg) override {
		try {
			c1->send(msg);
		} catch (const exception &ex) {
			c2->send(msg);
		}
	}
};

class Telefon : public Channel {
private:
	int nrTel;
public:
	Telefon(int nrTel) : nrTel(nrTel) { }
	void send(const string &msg) {
		if (rand() % 3 == 0) throw exception {};
		cout << "sent: " << msg << endl;
	}
};

class Fax : public Telefon {
public:
	Fax(int nrTel) : Telefon(nrTel) { }
	void send(const string &msg) override {
		Telefon::send(msg);
		cout << "sending fax" << endl;
	}
};

class SMS : public Telefon {
public:
	SMS(int nrTel) : Telefon(nrTel) { }
	void send(const string &msg) override {
		Telefon::send(msg);
		cout << "sending sms" << endl;
	}
};

class Contact {
private:
	Channel *c1, *c2, *c3;
public:
	Contact(Channel *c1, Channel *c2, Channel *c3)
	: c1(c1), c2(c2), c3(c3)
	{ }
	~Contact() {
		delete c1;
		delete c2;
		delete c3;
	}
	void sendAlarm(const string &msg) {
		try {
			c1->send(msg);
		} catch(const exception &ex1) {
			try {
				c2->send(msg);
			} catch(const exception &ex2) {
				c3->send(msg);
			}
		}
	}
};

Contact *f() {
	return new Contact {
		new Telefon {12345},
		new Failover {
			new Fax {12346},
			new SMS {12347}
		},
		new Failover {
			new Telefon {12348},
			new Failover {
				new Fax {12349},
				new SMS {12340}
			}
		}
	};
}

int main() {
	srandom(time(0));
	
	Contact *c = f();
	c->sendAlarm("poop");
	c->sendAlarm("scoop");
	c->sendAlarm("kayne");
	delete c;
	return 0;
}
