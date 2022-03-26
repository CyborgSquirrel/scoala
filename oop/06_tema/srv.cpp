#include <algorithm>
#include <cassert>

#include "./srv.hpp"

SrvCarti::SrvCarti(RepoCarti &repo_carti) : repo(repo_carti) {
	this->last_id = 0;
}

void SrvCarti::add_carte(
	std::string titlu,
	std::string autor,
	std::string gen,
	int an
) {
	this->repo.add({this->last_id, titlu, autor, gen, an});
	this->last_id++;
}

void SrvCarti::erase_carte(int id) {
	this->repo.erase(id);
}

void SrvCarti::update_carte(
	int id,
	std::string titlu,
	std::string autor,
	std::string gen,
	int an
) {
	this->repo.update({id, titlu, autor, gen, an});
}

Carte SrvCarti::find_carte(int id) const {
	return this->repo.find(id);
}

std::vector<Carte> SrvCarti::get_carti() const {
	return this->repo.get_all();
}

std::vector<Carte> SrvCarti::filter_by_titlu(const std::string &filter) const {
	auto carti = this->repo.get_all();
	std::vector<Carte> filtered {};
	for (auto &carte : carti) {
		if (carte.get_titlu().find(filter) != std::string::npos) {
			filtered.push_back(carte);
		}
	}
	return filtered;
}
std::vector<Carte> SrvCarti::filter_by_an(int an) const {
	auto carti = this->repo.get_all();
	std::vector<Carte> filtered {};
	for (auto &carte : carti) {
		if (carte.get_an() == an) filtered.push_back(carte);
	}
	return filtered;
}

std::vector<Carte> SrvCarti::sort_by_titlu() const {
	auto carti = this->repo.get_all();
	std::sort(
		carti.begin(), carti.end(),
		[](Carte &lhs, Carte &rhs){ return lhs.get_titlu() < rhs.get_titlu(); }
	);
	return carti;
}
std::vector<Carte> SrvCarti::sort_by_autor() const {
	auto carti = this->repo.get_all();
	std::sort(
		carti.begin(), carti.end(),
		[](Carte &lhs, Carte &rhs){ return lhs.get_autor() < rhs.get_autor(); }
	);
	return carti;
}
std::vector<Carte> SrvCarti::sort_by_an_gen() const {
	auto carti = this->repo.get_all();
	std::sort(
		carti.begin(), carti.end(),
		[](Carte &lhs, Carte &rhs){ return lhs.get_an() < rhs.get_an() || (lhs.get_an() == rhs.get_an() && lhs.get_gen() < rhs.get_gen()); }
	);
	return carti;
}

void test_srv_crud() {
	RepoCarti repo {};
	SrvCarti srv {repo};
	
	std::string a_titlu = "The Picture of Dorian Grey";
	std::string a_autor = "Oscar Wilde";
	std::string a_gen = "classic";
	int a_an = 1850;
	
	std::string b_titlu = "1984";
	std::string b_autor = "George Orwell";
	std::string b_gen = "dystopia";
	int b_an = 1948;
	
	std::string c_titlu = "Harry Potter";
	std::string c_autor = "J.K. Rowling";
	std::string c_gen = "fiction";
	int c_an = 1990;
	
	// add_carte
	srv.add_carte(a_titlu, a_autor, a_gen, a_an);
	srv.add_carte(b_titlu, b_autor, b_gen, b_an);
	srv.add_carte(c_titlu, c_autor, c_gen, c_an);
	
	// find_carte
	Carte a = srv.find_carte(0);
	assert(a.get_titlu() == a_titlu);
	assert(a.get_autor() == a_autor);
	assert(a.get_gen() == a_gen);
	assert(a.get_an() == a_an);
	
	Carte b = srv.find_carte(1);
	assert(b.get_titlu() == b_titlu);
	assert(b.get_autor() == b_autor);
	assert(b.get_gen() == b_gen);
	assert(b.get_an() == b_an);
	
	Carte c = srv.find_carte(2);
	assert(c.get_titlu() == c_titlu);
	assert(c.get_autor() == c_autor);
	assert(c.get_gen() == c_gen);
	assert(c.get_an() == c_an);
	
	// get_carti
	std::vector<Carte> carti = {a, b, c};
	assert(srv.get_carti() == carti);
	
	// update_carte
	std::string d_titlu = "Brave New World";
	std::string d_autor = "Aldous Huxley";
	std::string d_gen = "dystopia";
	int d_an = 1931;
	
	srv.update_carte(1, d_titlu, d_autor, d_gen, d_an);
	Carte d = srv.find_carte(1);
	assert(d.get_titlu() == d_titlu);
	assert(d.get_autor() == d_autor);
	assert(d.get_gen() == d_gen);
	assert(d.get_an() == d_an);
	
	// erase_carte
	srv.erase_carte(2);
	srv.erase_carte(0);
	srv.erase_carte(1);
}

void test_srv_filter_and_sort() {
	RepoCarti repo {};
	SrvCarti srv {repo};
	
	std::string a_titlu = "The Picture of Dorian Grey";
	std::string a_autor = "Oscar Wilde";
	std::string a_gen = "classic";
	int a_an = 1850;
	
	std::string b_titlu = "1984";
	std::string b_autor = "George Orwell";
	std::string b_gen = "dystopia";
	int b_an = 1948;
	
	std::string c_titlu = "Harry Potter";
	std::string c_autor = "J.K. Rowling";
	std::string c_gen = "fiction";
	int c_an = 1990;
	
	std::string d_titlu = "Brave New World";
	std::string d_autor = "Aldous Huxley";
	std::string d_gen = "dystopia";
	int d_an = 1931;
	
	srv.add_carte(a_titlu, a_autor, a_gen, a_an);
	srv.add_carte(b_titlu, b_autor, b_gen, b_an);
	srv.add_carte(c_titlu, c_autor, c_gen, c_an);
	srv.add_carte(d_titlu, d_autor, d_gen, d_an);
	
	Carte a = srv.find_carte(0);
	Carte b = srv.find_carte(1);
	Carte c = srv.find_carte(2);
	Carte d = srv.find_carte(3);
	
	auto filter_titlu = srv.filter_by_titlu("Har");
	std::vector<Carte> filter_titlu_res = { c };
	assert(filter_titlu == filter_titlu_res);
	
	auto filter_an = srv.filter_by_an(1948);
	std::vector<Carte> filter_an_res = { b };
	assert(filter_an == filter_an_res);
	
	auto sort_titlu = srv.sort_by_titlu();
	std::vector<Carte> sort_titlu_res = { b, d, c, a };
	assert(sort_titlu == sort_titlu_res);
	
	auto sort_autor = srv.sort_by_autor();
	std::vector<Carte> sort_autor_res = { d, b, c, a };
	assert(sort_autor == sort_autor_res);
	
	auto sort_an_gen = srv.sort_by_an_gen();
	std::vector<Carte> sort_an_gen_res = { a, d, b, c };
	assert(sort_an_gen == sort_an_gen_res);
}

void test_srv() {
	test_srv_crud();
	test_srv_filter_and_sort();
}

