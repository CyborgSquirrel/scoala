#ifndef domain_hpp_INCLUDED
#define domain_hpp_INCLUDED

#include <string>

enum Status { PENDING, CONFIRMED, CANCELLED, DELIVERED };

class Order {
private:
	int m_id;
	int m_number;
	std::string m_object;
	Status m_status;
public:
	// Creeaza o noua comanda cu datele furnizate.
	// in: id -- id-ul comenzii
	//     number -- numarul comenzii
	//     object -- obiectul comandat
	//     status -- statutul comenzii
	Order(int id, int number, const std::string &object, Status status);
	
	// Returneaza id-ul comenzii.
	// out: int, id-ul comenzii
	int getId() const;
	
	// Returneaza numarul comenzii.
	// out: int, numarul comenzii
	int getNumber() const;
	
	// Returneaza obiectul comandat.
	// out: std::string, obiectul comandat
	const std::string &getObject() const;
	
	// Returneaza statutul comenzii.
	// out: Status, statutul comenzii
	Status getStatus() const;
	
	// Actualizeaza numarul comenzii.
	// in: number -- numarul comenzii
	void setNumber(int number);
	
	// Actualizeaza obiectul comandat.
	// in: std::string -- obiectul comandat
	void setObject(const std::string &object);
	
	// Actualizeaza statutul comenzii.
	// in: status -- statutul comenzii
	void setStatus(Status status);
	
	// Compara doua comenzi.
	// in: other -- cealalta comanda
	// out: bool, true daca sunt la fel, false altfel
	bool operator==(const Order &other) const;
};

void testOrder();

#endif // domain_hpp_INCLUDED

