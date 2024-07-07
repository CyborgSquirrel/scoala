#ifndef repo_hpp_INCLUDED
#define repo_hpp_INCLUDED

#include "./domain.hpp"

#include <vector>
#include <string>

class RepoGame {
private:
	std::vector<Game> m_games;
	std::string m_filePath;
	
	// Citeste toate jocurile din fisier in repo.
	void readAllFromFile();
	// Scrie toate jocurile din repo in fisier.
	void writeAllToFile() const;
public:
	// Creeaza un nou repo, cu numele fisierului furnizat.
	// in: filePath -- numele fisierului din care va citi / scrie repo-ul
	RepoGame(const std::string &filePath);
	
	// Returneaza toate jocurile din repo.
	// out: vector cu toate jocurile din repo
	const std::vector<Game> &getAll() const;
	
	// Salveaza un joc in repo.
	// in: game -- jocul care va fi salvat
	void store(const Game &game);
	
	// Actualizeaza un joc in repo.
	// in: game -- jocul care va fi actualizat
	void update(const Game &game);
	
	// Cauta un joc in repo, dupa id.
	// in: id -- id-ul dupa care va fi cautat jocul
	// out: jocul cu id-ul id
	Game find(int id) const;
	
	// Returneaza urmatorul id care are putea fi atribuit unui joc.
	// out: urmatorul id care are putea fi atribuit unui joc
	int getNextId() const;
};

void testRepo();

#endif // repo_hpp_INCLUDED

