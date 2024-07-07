#ifndef repo_hpp_INCLUDED
#define repo_hpp_INCLUDED

#include "./domain.hpp"

#include <vector>

class RepoException {
private:
	std::string m_msg;
public:
	RepoException(const std::string &msg);
	const std::string &getMsg() const;
};

class RepoMelodie {
private:
	std::vector<Melodie> m_melodii;
	std::string m_filePath;
	
	// Citeste melodiile din fisier.
	void readAllFromFile();
	
	// Scrie melodiile in fisier.
	void writeAllToFile() const;
public:
	// Constructor pentru repo de melodii.
	// in: filePath -- numele fisierului din care va fi folosit
	RepoMelodie(const std::string &filePath);
	
	// Returneaza lungimea repo-ului.
	// out: lungimea repo-ului
	int getLength() const;
	
	// Salveaza o melodie in repo.
	// in: melodie -- melodia care va fi salvata
	void store(const Melodie &melodie);
	
	// Sterge o melodie din repo dupa id.
	// in: id -- id-ul dupa care se va sterge melodia
	void erase(int id);
	
	// Returneaza toate melodiile din repo.
	// out: vector cu toate melodiile din repo
	const std::vector<Melodie> &getAll() const;
};

void testRepo();

#endif // repo_hpp_INCLUDED

