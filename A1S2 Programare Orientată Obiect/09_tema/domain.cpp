#include <gsl/gsl_assert>

#include "./domain.hpp"

Carte::Carte(
	int id,
	const std::string &titlu,
	const std::string &autor,
	const std::string &gen,
	int an
) : id(id), titlu(titlu), autor(autor), gen(gen), an(an) { }

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

InchiriereCarte::InchiriereCarte(int carte_id) : carte_id(carte_id) { }
int InchiriereCarte::get_carte_id() const { return this->carte_id; }
bool operator==(const InchiriereCarte &lhs, const InchiriereCarte &rhs) {
	return lhs.carte_id == rhs.carte_id;
}

#include <sstream>
void test_inchiriere_carte() {
	// constructor
	const int carte_id = 0;
	InchiriereCarte a { carte_id };
	
	// get
	Ensures(a.get_carte_id() == carte_id);
}

void test_carte() {
	// constructor
	const int a_id = 0;
	const int a_an = 1850;
	Carte a { a_id, "The Picture of Dorian Grey", "Oscar Wilde", "classic", a_an };
	
	// get
	Ensures(a.get_id() == a_id);
	Ensures(a.get_titlu() == "The Picture of Dorian Grey");
	Ensures(a.get_autor() == "Oscar Wilde");
	Ensures(a.get_gen() == "classic");
	Ensures(a.get_an() == a_an);
	
	// set
	const int a_new_an = 2077;
	a.set_titlu("The Picture of Gorian Drey");
	a.set_autor("Wscar Oilde");
	a.set_gen("bussin");
	a.set_an(a_new_an);
	
	Ensures(a.get_titlu() == "The Picture of Gorian Drey");
	Ensures(a.get_autor() == "Wscar Oilde");
	Ensures(a.get_gen() == "bussin");
	Ensures(a.get_an() == a_new_an);
	
	// operator==
	const int b_id = 1;
	const int b_an = 1948;
	Carte b { b_id, "1984", "George Orwell", "dystopia", b_an };
	Ensures(a == a);
	Ensures(!(a == b));
	
	// operator<<
	std::stringstream sstream;
	sstream << a;
	Ensures(sstream.str() == "[0][anul 2077](The Picture of Gorian Drey-Wscar Oilde){bussin}");
}

void test_domain() {
	test_inchiriere_carte();
	test_carte();
}
