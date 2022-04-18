#include <gsl/gsl_assert>
#include <algorithm>

#include "./repo.hpp"

// REPO CARTI
RepoCartiException::RepoCartiException(const std::string &msg)
	: AppException(msg) { }

std::string RepoCartiException::get_type() const {
	return "RepoCartiException";
}

size_t RepoCarti::get_id_index(size_t id) const {
	auto it = std::find_if(
		this->carti.begin(), this->carti.end(),
		[id](const Carte &carte){ return carte.get_id() == id; }
	);
	if (it != carti.end()) {
		return it - carti.begin();
	} else {
		return -1;
	}
}

void RepoCarti::add(const Carte &carte) {
	size_t index = this->get_id_index(carte.get_id());
	if (index != -1) { throw RepoCartiException("cartea furnizata este deja in repo"); }
	this->carti.push_back(carte);
}

void RepoCarti::erase(size_t id) {
	size_t index = this->get_id_index(id);
	if (index == -1) { throw RepoCartiException("nu exista carte cu id-ul furnizat in repo"); }
	this->carti.erase(this->carti.begin() + (long) index);
}

void RepoCarti::update(const Carte &carte) {
	size_t index = this->get_id_index(carte.get_id());
	if (index == -1) { throw RepoCartiException("nu exista carte cu id-ul furnizat in repo"); }
	this->carti.erase(this->carti.begin() + (long) index);
	this->carti.push_back(carte);
}

const Carte &RepoCarti::find(size_t id) const {
	size_t index = this->get_id_index(id);
	if (index == -1) throw RepoCartiException("nu exista carte cu id-ul furnizat in repo");
	return this->carti[index];
}

const std::vector<Carte> &RepoCarti::get_all() const {
	return this->carti;
}

// REPO INCHIRIERI CARTE
RepoInchirieriCarteException::RepoInchirieriCarteException(const std::string &msg)
	: AppException(msg) { }

std::string RepoInchirieriCarteException::get_type() const {
	return "RepoInchirieriCarteException";
}

size_t RepoInchirieriCarte::get_id_index(size_t id) const {
	auto it = std::find_if(
		this->inchirieri_carte.begin(), this->inchirieri_carte.end(),
		[id](const InchiriereCarte &inchiriere_carte){ return inchiriere_carte.get_carte_id() == id; }
	);
	if (it != inchirieri_carte.end()) {
		return it - inchirieri_carte.begin();
	} else {
		return -1;
	}
}

void RepoInchirieriCarte::add(const InchiriereCarte &inchiriere_carte) {
	size_t index = this->get_id_index(inchiriere_carte.get_carte_id());
	if (index != -1) { throw RepoInchirieriCarteException("inchirierea furnizata este deja in repo"); }
	this->inchirieri_carte.push_back(inchiriere_carte);
}

void RepoInchirieriCarte::erase(size_t id) {
	size_t index = this->get_id_index(id);
	if (index == -1) { throw RepoInchirieriCarteException("nu exista inchiriere cu id-ul furnizat in repo"); }
	this->inchirieri_carte.erase(this->inchirieri_carte.begin() + (long) index);
}

const std::vector<InchiriereCarte> &RepoInchirieriCarte::get_all() const {
	return this->inchirieri_carte;
}

void test_repo_carti() {
	RepoCarti repo;
	const size_t a_id = 0; const int a_an = 1850;
	const size_t b_id = 1; const int b_an = 1948;
	const size_t c_id = 2; const int c_an = 1990;
	
	Carte a { a_id, "The Picture of Dorian Grey", "Oscar Wilde"  , "classic" , a_an };
	Carte b { b_id, "1984"                      , "George Orwell", "dystopia", b_an };
	Carte c { c_id, "Harry Potter"              , "J.K. Rowling" , "fiction" , c_an };
	
	// add
	repo.add(a);
	repo.add(b);
	repo.add(c);
	try { repo.add(a); Ensures(false); }
	catch (const RepoCartiException &ex) {
		Ensures(ex.as_string() == "RepoCartiException: cartea furnizata este deja in repo");
	}
	
	// find
	Carte fa = repo.find(0);
	Ensures(fa.get_id() == a.get_id());
	Ensures(fa.get_titlu() == a.get_titlu());
	Ensures(fa.get_autor() == a.get_autor());
	Ensures(fa.get_gen() == a.get_gen());
	Ensures(fa.get_an() == a.get_an());
	
	Carte fb = repo.find(1);
	Ensures(fb.get_id() == b.get_id());
	Ensures(fb.get_titlu() == b.get_titlu());
	Ensures(fb.get_autor() == b.get_autor());
	Ensures(fb.get_gen() == b.get_gen());
	Ensures(fb.get_an() == b.get_an());
	
	Carte fc = repo.find(2);
	Ensures(fc.get_id() == c.get_id());
	Ensures(fc.get_titlu() == c.get_titlu());
	Ensures(fc.get_autor() == c.get_autor());
	Ensures(fc.get_gen() == c.get_gen());
	Ensures(fc.get_an() == c.get_an());
	
	const int magic_number = 100;
	try { repo.find(magic_number); Ensures(false); }
	catch (const RepoCartiException &ex) {
		Ensures(ex.as_string() == "RepoCartiException: nu exista carte cu id-ul furnizat in repo");
	}
	
	// get_all
	std::vector<Carte> carti = {a, b, c};
	Ensures(repo.get_all() == carti);
	
	// update
	const size_t d_id = 1; const int d_an = 1931;
	Carte d { d_id, "Brave New World", "Aldous Huxley", "dystopia", d_an };
	
	repo.update(d);
	Carte fd = repo.find(1);
	Ensures(fd.get_titlu() == d.get_titlu());
	Ensures(fd.get_autor() == d.get_autor());
	Ensures(fd.get_gen() == d.get_gen());
	Ensures(fd.get_an() == d.get_an());
	
	const size_t e_id = 100; const int e_an = 1931;
	Carte e { e_id, "Brave New World", "Aldous Huxley", "dystopia", e_an };
	try { repo.update(e); Ensures(false); }
	catch (const RepoCartiException &ex) {
		Ensures(ex.as_string() == "RepoCartiException: nu exista carte cu id-ul furnizat in repo");
	}
	
	// erase
	repo.erase(c_id);
	repo.erase(a_id);
	repo.erase(b_id);
	try { repo.erase(magic_number); Ensures(false); }
	catch (const RepoCartiException &ex) {
		Ensures(ex.as_string() == "RepoCartiException: nu exista carte cu id-ul furnizat in repo");
	}
}

void test_repo_inchirieri_carte() {
	RepoInchirieriCarte repo;
	
	int a_id = 0; InchiriereCarte a {a_id};
	int b_id = 1; InchiriereCarte b {b_id};
	int c_id = 2; InchiriereCarte c {c_id};
	
	// add
	repo.add(a);
	repo.add(b);
	repo.add(c);
	try { repo.add(a); Ensures(false); }
	catch (const RepoInchirieriCarteException &ex) {
		Ensures(ex.as_string() == "RepoInchirieriCarteException: inchirierea furnizata este deja in repo");
	}
	
	// get_all
	std::vector<InchiriereCarte> v {a, b, c};
	Ensures(repo.get_all() == v);
	
	// erase
	repo.erase(a_id);
	repo.erase(b_id);
	repo.erase(c_id);
	try { repo.erase(0); Ensures(false); }
	catch (const RepoInchirieriCarteException &ex) {
		Ensures(ex.as_string() == "RepoInchirieriCarteException: nu exista inchiriere cu id-ul furnizat in repo");
	}
}

void test_repo() {
	test_repo_carti();
	test_repo_inchirieri_carte();
}
