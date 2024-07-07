#ifndef domain_hpp_INCLUDED
#define domain_hpp_INCLUDED

#include <string>

enum class Gen {
	POP, ROCK, FOLK, DISCO
};

// Returneaza un gen convertit dintr-un string.
// in: str -- stringul care va fi convertit in gen
// out: genul
Gen genFromString(const std::string &str);

// Returneaza numele unui gen ca string.
// in: gen -- genul pentru care se va returna numele
// out: numele genului
std::string stringFromGen(Gen gen);

class Melodie {
private:
	int m_id;
	std::string m_titlu;
	std::string m_artist;
	Gen m_gen;
public:
	// Constructor default pentru melodie.
	Melodie() = default;
	
	// Constructor pentru melodie.
	// in: id -- id-ul melodiei
	//     titlu -- titlul melodiei
	//     artist -- artistul melodiei
	//     gen -- genul melodiei
	Melodie(
		int id,
		const std::string &titlu,
		const std::string &artist,
		Gen gen
	);
	
	// Getter pentru id-ul melodiei.
	// out: id-ul melodiei
	int getId() const;
	
	// Getter pentru titlul melodiei.
	// out: titlul melodiei
	const std::string &getTitlu() const;
	
	// Getter pentru artistul melodiei.
	// out: artistul melodiei
	const std::string &getArtist() const;
	
	// Getter pentru genul melodiei.
	// out: genul melodiei
	Gen getGen() const;
	
	// Setter pentru titlul melodiei.
	// in: titlu -- titlul melodiei
	void setTitlu(const std::string &titlu);
	
	// Setter pentru artistul melodiei.
	// in: artist -- artistul melodiei
	void setArtist(const std::string &artist);
	
	// Setter pentru genul melodiei.
	// in: gen -- genul melodiei
	void setGen(Gen gen);
	
	// Compara doua melodii pentru egalitate.
	// in: other -- celalte melodie care va fi comparata
	// out: true daca sunt egale, false altfel
	bool operator==(const Melodie &other) const;
};

void testDomain();

#endif // domain_hpp_INCLUDED

