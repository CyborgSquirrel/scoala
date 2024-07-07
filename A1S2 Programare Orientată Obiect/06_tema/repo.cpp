#include <cassert>

#include "./repo.hpp"

RepoCartiException::RepoCartiException(const std::string &msg) {
	this->msg = msg;
}

int RepoCarti::get_id_index(int id) const {
	for (size_t i = 0; i < this->carti.size(); ++i) {
		if (carti[i].get_id() == id) {
			return i;
		}
	}
	return -1;
}

void RepoCarti::add(Carte carte) {
	int index = this->get_id_index(carte.get_id());
	if (index != -1) { throw RepoCartiException("cartea furnizata este deja in repo"); }
	this->carti.push_back(carte);
}

void RepoCarti::erase(int id) {
	int index = this->get_id_index(id);
	if (index == -1) { throw RepoCartiException("nu exista carte cu id-ul furnizat in repo"); }
	this->carti.erase(this->carti.begin() + index);
}

void RepoCarti::update(Carte carte) {
	int index = this->get_id_index(carte.get_id());
	if (index == -1) { throw RepoCartiException("nu exista carte cu id-ul furnizat in repo"); }
	this->carti.erase(this->carti.begin() + index);
	this->carti.push_back(carte);
}

Carte RepoCarti::find(int id) const {
	int index = this->get_id_index(id);
	if (index == -1) throw RepoCartiException("nu exista carte cu id-ul furnizat in repo");
	return this->carti[index];
}

const std::vector<Carte> &RepoCarti::get_all() const {
	return this->carti;
}

void test_repo_crud() {
	RepoCarti repo {};
	
	Carte a { 0, "The Picture of Dorian Grey", "Oscar Wilde"  , "classic" , 1850 };
	Carte b { 1, "1984"                      , "George Orwell", "dystopia", 1948 };
	Carte c { 2, "Harry Potter"              , "J.K. Rowling" , "fiction" , 1990 };
	
	// add
	repo.add(a);
	repo.add(b);
	repo.add(c);
	try { repo.add(a); } catch (const RepoCartiException &ex) { }
	
	// find
	Carte fa = repo.find(0);
	assert(fa.get_id() == a.get_id());
	assert(fa.get_titlu() == a.get_titlu());
	assert(fa.get_autor() == a.get_autor());
	assert(fa.get_gen() == a.get_gen());
	assert(fa.get_an() == a.get_an());
	
	Carte fb = repo.find(1);
	assert(fb.get_id() == b.get_id());
	assert(fb.get_titlu() == b.get_titlu());
	assert(fb.get_autor() == b.get_autor());
	assert(fb.get_gen() == b.get_gen());
	assert(fb.get_an() == b.get_an());
	
	Carte fc = repo.find(2);
	assert(fc.get_id() == c.get_id());
	assert(fc.get_titlu() == c.get_titlu());
	assert(fc.get_autor() == c.get_autor());
	assert(fc.get_gen() == c.get_gen());
	assert(fc.get_an() == c.get_an());
	
	try { repo.find(100); } catch (const RepoCartiException &ex) { }
	
	// get_all
	std::vector<Carte> carti = {a, b, c};
	assert(repo.get_all() == carti);
	
	// update
	Carte d { 1, "Brave New World", "Aldous Huxley", "dystopia", 1931 };
	
	repo.update(d);
	Carte fd = repo.find(1);
	assert(fd.get_titlu() == d.get_titlu());
	assert(fd.get_autor() == d.get_autor());
	assert(fd.get_gen() == d.get_gen());
	assert(fd.get_an() == d.get_an());
	
	Carte e { 100, "Brave New World", "Aldous Huxley", "dystopia", 1931 };
	try { repo.update(e); } catch (const RepoCartiException &ex) { }
	
	// erase
	repo.erase(2);
	repo.erase(0);
	repo.erase(1);
	try { repo.erase(100); } catch (const RepoCartiException &ex) { }
}

void test_repo() {
	test_repo_crud();
}
