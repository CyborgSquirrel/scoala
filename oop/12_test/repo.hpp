#ifndef repo_hpp_INCLUDED
#define repo_hpp_INCLUDED

#include "./domain.hpp"

#include <vector>
#include <string>

class RepoOrder {
private:
	std::string m_filePath;
	std::vector<Order> m_orders;
	
	void readAllFromFile();
public:
	// Creeaza un nou repo cu path-ul furnizat.
	// in: filePath -- path-ul din care vor fi citite comenzil
	RepoOrder(std::string filePath);
	
	// Gaseste o comanda cu id-ul furnizat in repo.
	// in: id -- id-ul comenzii cautate
	// out: Order, comanda cautata
	Order find(int id) const;
	
	// Actualizeaza o comanda din repo.
	// in: order -- comanda care sa fie actualizata
	void update(const Order &order);
	
	// Returneaza toate comenzile din repo.
	// out: std::vector<Order>, vectoru cu toate comenzile din repo
	const std::vector<Order> &getAll() const;
};

void testRepoOrder();

#endif // repo_hpp_INCLUDED

