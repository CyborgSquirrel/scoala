#ifndef domain_h_INCLUDED
#define domain_h_INCLUDED

#include <ostream>
#include <string>

class Carte {
private:
	int id;
	std::string titlu, autor, gen;
	int an;
public:
	// Constructor pentru carte.
	// in: id -- id-ul cartii construite
	//     titlu -- titlul cartii construite
	//     autor -- autorul cartii construite
	//     gen -- genul cartii construite
	//     an -- anul in care a fost publicata cartea construita
	Carte(
		int id,
		const std::string &titlu,
		const std::string &autor,
		const std::string &gen,
		int an
	);
	
	// Destructor pentru carte.
	~Carte();
	
	// Operator de asignare pentru carte.
	// in: carte -- cartea care va fi asignata
	Carte &operator=(const Carte &carte);
	
	// Constructor de copiere pentru carte.
	// in: carte -- cartea care este copiata
	Carte(const Carte &carte);
	
	// Getter pentru id-ul cartii.
	// out: titlul id-ul
	int get_id() const;
	
	// Getter pentru titlul cartii.
	// out: titlul cartii
	const std::string &get_titlu() const;
	
	// Getter pentru autorul cartii.
	// out: autorul cartii
	const std::string &get_autor() const;
	
	// Getter pentru genul cartii.
	// out: genul cartii
	const std::string &get_gen() const;
	
	// Getter pentru anul cartii.
	// out: anul cartii
	int get_an() const;
	
	// Setter pentru titlul cartii.
	// in: titlu -- titlul nou
	void set_titlu(const std::string &titlu);
	
	// Setter pentru autorul cartii.
	// in: autor -- autorul nou
	void set_autor(const std::string &autor);
	
	// Setter pentru genul cartii.
	// in: gen -- genul nou
	void set_gen(const std::string &gen);
	
	// Setter pentru anul cartii.
	// in: an -- anul nou
	void set_an(int an);
	
	friend bool operator==(const Carte &lhs, const Carte &rhs);
	
	friend std::ostream &operator<<(std::ostream &out, const Carte &carte);
};

bool operator==(const Carte &lhs, const Carte &rhs);
std::ostream &operator<<(std::ostream &out, const Carte &carte);

void test_domain();

#endif // domain_hpp_INCLUDED

