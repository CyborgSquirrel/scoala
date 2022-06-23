#ifndef domain_hpp_INCLUDED
#define domain_hpp_INCLUDED

#include <string>

enum class GameState {
	NEINCEPUT, IN_DERULARE, TERMINAT
};

// Converteste starea jocului furnizata in string.
// in: state -- starea jocului care va fi convertita
std::string gameStateToString(GameState state);

class Game {
private:
	int m_id;
	int m_dim;
	std::string m_board;
	char m_next;
	GameState m_state;
public:
	// Creeaza un joc nou, cu parametrii furnizati.
	// in: id -- id-ul jocului
	//     dim -- dimensiunea jocului
	//     board -- tabla jocului
	//     next -- urmatorul jucator al jocului
	//     state -- starea jocului
	Game(
		int id,
		int dim,
		const std::string &board,
		char next,
		GameState state
	);
	
	
	// Returneaza id-ul jocului.
	// out: id-ul jocului
	int getId() const;
	
	// Returneaza dimensiunea jocului.
	// out: dimensiunea jocului
	int getDim() const;
	
	// Returneaza tabla jocului.
	// out: tabla jocului
	const std::string &getBoard() const;
	
	// Returneaza urmatorul jucator al jocului.
	// out: urmatorul jucator al jocului
	char getNext() const;
	
	// Returneaza starea jocului.
	// out: starea jocului
	GameState getState() const;
	
	
	// Actualizeaza dimensiunea jocului.
	// in: dim -- noua dimensiunea a jocului
	void setDim(int dim);
	
	// Actualizeaza tabla jocului.
	// in: board -- noua tabla a jocului
	void setBoard(const std::string &board);
	
	// Actualizeaza urmatorul jucator al jocului.
	// in: next -- noul urmatorul jucator al jocului
	void setNext(char next);
	
	// Actualizeaza starea jocului.
	// in: state -- noua stare a jocului
	void setState(GameState state);
	
	// Verifica daca doua jocuri sunt egale.
	// in: other -- celalalt joc
	bool operator==(const Game &other);
};

void testDomain();

#endif // domain_hpp_INCLUDED

