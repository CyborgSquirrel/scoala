#ifndef repo_hpp_INCLUDED
#define repo_hpp_INCLUDED

#include <vector>

#include "./domain.hpp"

class RepoCartiException {
private:
	std::string msg;
public:
	RepoCartiException(const std::string &msg);
};

class RepoCarti {
private:
	std::vector<Carte> carti;
	
	// Functie interna care cauta o carte in vector dupa id.
	// in: id -- id-ul dupa care se cauta cartea
	// out: indicele cartii in vectorul de carti, sau -1 daca cartea nu exista
	int get_id_index(int id) const;
public:
	// Creeaza un nou repo de carti.
	RepoCarti() = default;
	
	// Nu permitem sa se copieze un repo de carti.
	RepoCarti(const RepoCarti &repo_carti) = delete;
	
	// Adauga o carte in repo.
	// in: carte -- cartea care va fi adaugata
	// raise: RepoCartiException, daca cartea care se adauga este deja in repo
	void add(Carte carte);
	
	// Sterge o carte din repo.
	// in: id -- id-ul cartii care va fi stearsa
	// raise: RepoCartiException, daca cartea cu id-ul furnizat nu exista in repo
	void erase(int id);
	
	// Actualizeaza valoarea unei carti in repo.
	// in: carte -- cartea care va fi actualizata
	// raise: RepoCartiException, daca cartea nu exista in repo
	void update(Carte carte);
	
	// Cauta cartea cu id-ul furnizat in repo.
	// in: id -- id-ul cartii care este cautata
	// out: cartea cu id-ul furnizat
	// raise: RepoCartiException, daca cartea cu id-ul furnizat nu a putut fi gasita
	Carte find(int id) const;
	
	// Returneaza toate cartile din repo.
	const std::vector<Carte> &get_all() const;
};

void test_repo();

#endif // repo_hpp_INCLUDED

