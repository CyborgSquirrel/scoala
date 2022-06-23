#ifndef srv_hpp_INCLUDED
#define srv_hpp_INCLUDED

#include "./repo.hpp"

#include <functional>
#include <map>
#include <vector>

class SrvGame {
private:
	RepoGame &m_repo;
	
	int m_nextCallbackId;
	std::map<int, std::function<void()>> m_callbacks;
	void publish();
public:
	// Creeaza un nou srv de jocuri, cu repo-ul furnizat.
	// in: repo -- repo-ul cu care va fi creat srv-ul de jocuri
	SrvGame(RepoGame &repo);
	
	// Returneaza toate jocurile.
	// out: vector cu toate jocurile
	const std::vector<Game> &getGames() const;
	
	// Returneaza toate jocurile sortate dupa stare.
	// out: vector cu toate jocurile sortate dupa stare
	std::vector<Game> getGamesSortedByState() const;
	
	// Adauga un nou joc.
	// in: dim -- dimensiunea jocului
	//     board -- tabla jocului
	//     next -- urmatorul jucator al jocului
	void addGame(
		int dim, 
		const std::string &board, 
		char next
	);
	
	// Actualizeaza un joc.
	// in: id -- id-ul jocului
	//     dim -- dimensiunea jocului
	//     board -- tabla jocului
	//     next -- urmatorul jucator al jocului
	//     state -- starea jocului
	void updateGame(
		int id,
		int dim, 
		const std::string &board, 
		char next,
		GameState state
	);
	
	// Cauta un joc dupa id.
	// in: id-ul jocului cautat
	// out: jocul cautat
	Game getGame(
		int id
	);
	
	// Face o miscare pe pozitia specificata de row si column, in jocul cu id-ul furnizat
	// in: id -- id-ul jocului in care se va face miscarea
	//     row -- linia pe care se va face miscare
	//     column -- coloana pe care se va face miscare
	void makeMove(
		int id,
		int row, int column
	);
	
	int subscribeToUpdate(
		std::function<void()> callback
	);
	
	void unsubscribeFromUpdate(
		int callbackId
	);
};

void testSrv();

#endif // srv_hpp_INCLUDED

