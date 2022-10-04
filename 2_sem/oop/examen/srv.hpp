#ifndef srv_hpp_INCLUDED
#define srv_hpp_INCLUDED

#include "./repo.hpp"

#include <functional>
#include <map>

class SrvMelodie {
private:
	RepoMelodie &m_repo;
	
	// Returneaza urmatorul id care poate fi folosit pentru o melodie.
	// out: urmatorul id care poate fi folosit pentru o melodie
	int getNextId() const;
public:
	// Constructor pentru service de melodii.
	// in: repo -- repo-ul care va fi folosit in service
	SrvMelodie(RepoMelodie &repo);
	
	// Returneaza numarul de melodii.
	// out: numarul de melodii
	int getLength() const;
	
	// Returneaza toate melodiile sortate dupa autor.
	// out: vector cu toate melodiile sortate dupa autor
	std::vector<Melodie> getMelodiiSortedByAutor() const;
	
	// Returneaza numarul de melodii care au ca autor autorul furnizat.
	// in: autor -- autorul pentru care se va cauta numarul de melodii cu acel autor
	// out: numarul de melodii cu autorul autor
	int getMelodiiCountWithAutor(const std::string &autor) const;
	
	// Returneaza numarul de melodii care au ca gen genul furnizat.
	// in: gen -- genul pentru care se va cauta numarul de melodii cu acel gen
	// out: numarul de melodii cu genul gen
	int getMelodiiCountWithGen(Gen gen) const;
	
	// Adauga o melodie.
	// in: titlu -- titlul melodiei
	//     artist -- artistul melodiei
	//     gen -- genul melodiei
	void addMelodie(
		std::string titlu,
		std::string artist,
		Gen gen
	);
	
	// Sterge melodia cu id-ul furnizat.
	// in: id -- id-ul melodiei care va fi stearsa
	void eraseMelodie(
		int id
	);
	
private:
	std::map<int, std::function<void()>> m_callbacks;
	int m_nextCallbackId;
	
	// Apeleaza toate callback-urile.
	void publish();
public:
	// Adauga o functie care va fi apelata oricand apare o schimbare in service.
	// in: callback -- functia care va fi apelata
	// out: id-ul callback-ului
	int connect(std::function<void()> callback);
	
	// Scoate functia cu id-ul furnizat din lista de functii care sunt apelate atunci cand apare o schimbare in service.
	// in: id -- id-ul functiei care va fi scoasa
	void disconnect(int id);
};

void testSrv();

#endif // srv_hpp_INCLUDED

