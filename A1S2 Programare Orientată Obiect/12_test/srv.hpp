#ifndef srv_hpp_INCLUDED
#define srv_hpp_INCLUDED

#include "./repo.hpp"

class SrvOrder {
private:
	RepoOrder &m_repo;
public:
	// Creeaza un nou service de comenzi, cu repo-ul furnizat.
	// in: repo -- repo de comenzi
	SrvOrder(RepoOrder &repo);
	
	// Gaseste o comanda dupa id, si o returneaza.
	// in: id -- id-ul comenzii cautate
	// out: Order, comanda cautata
	Order findOrder(int id);
	
	// Actualizeaza o comanda, cu parametrii furnizati.
	// in: id -- id-ul comenzii
	//     number -- numarul comenzii
	//     object -- obiectul comandat
	//     status -- statutul comenzii
	void updateOrder(int id, int number, const std::string &object, Status status);
	
	// Returneaza toate comenzile.
	// out: std::vector<Order>, vector cu toate comenzile
	const std::vector<Order> &getOrders() const;
	
	// Returneaza comenzile filtrate dupa statutul furnizat.
	// in: filterStatus -- statutul dupa care se face filtrarea
	// out: std::vector<Order>, vector cu comenzile filtrate
	std::vector<Order> getOrdersFilteredByStatus(Status filterStatus) const;
};

void testSrvOrder();

#endif // srv_hpp_INCLUDED

