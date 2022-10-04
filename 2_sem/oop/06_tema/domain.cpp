#include <cassert>

#include "./domain.hpp"

Carte::Carte(
	int id,
	const std::string &titlu,
	const std::string &autor,
	const std::string &gen,
	int an
) {
	this->id = id;
	this->titlu = titlu;
	this->autor = autor;
	this->gen = gen;
	this->an = an;
}

int Carte::get_id() const { return this->id; }
const std::string &Carte::get_titlu() const { return this->titlu; }
const std::string &Carte::get_autor() const { return this->autor; }
const std::string &Carte::get_gen() const { return this->gen; }
int Carte::get_an() const { return this->an; }

void Carte::set_titlu(const std::string &titlu) { this->titlu = titlu; }
void Carte::set_autor(const std::string &autor) { this->autor = autor; }
void Carte::set_gen(const std::string &gen) { this->gen = gen; }
void Carte::set_an(int an) { this->an = an; }

bool operator==(const Carte &lhs, const Carte &rhs) {
	return lhs.id    == rhs.id
		&& lhs.titlu == rhs.titlu
		&& lhs.autor == rhs.autor
		&& lhs.gen   == rhs.gen
		&& lhs.an    == rhs.an
	;
}

std::ostream &operator<<(std::ostream &out, const Carte &carte) {
	out << "[" << carte.id << "][anul " << carte.an << "](" << carte.titlu << "-" << carte.autor << "){" << carte.gen << "}";
	return out;
}

#include <sstream>
void test_domain() {
	// constructor
	Carte a { 0, "The Picture of Dorian Grey", "Oscar Wilde", "classic", 1850 };
	
	// get
	assert(a.get_id() == 0);
	assert(a.get_titlu() == "The Picture of Dorian Grey");
	assert(a.get_autor() == "Oscar Wilde");
	assert(a.get_gen() == "classic");
	assert(a.get_an() == 1850);
	
	// set
	a.set_titlu("The Picture of Gorian Drey");
	a.set_autor("Wscar Oilde");
	a.set_gen("bussin");
	a.set_an(2077);
	
	assert(a.get_titlu() == "The Picture of Gorian Drey");
	assert(a.get_autor() == "Wscar Oilde");
	assert(a.get_gen() == "bussin");
	assert(a.get_an() == 2077);
	
	// operator==
	Carte b { 1, "1984", "George Orwell", "dystopia", 1948 };
	assert(a == a);
	assert(!(a == b));
	
	// operator<<
	std::stringstream sstream;
	sstream << a;
	assert(sstream.str() == "[0][anul 2077](The Picture of Gorian Drey-Wscar Oilde){bussin}");
}
