#ifndef repo_hpp_INCLUDED
#define repo_hpp_INCLUDED

#include <vector>

#include "./domain.hpp"
#include "./exception.hpp"

class RepoCartiException : public AppException {
private:
	std::string get_type() const override;
public:
	RepoCartiException(const std::string &msg);
};

class RepoCarti {
private:
	std::vector<Carte> carti;
	
	// Functie interna care cauta o carte in vector dupa id.
	// in: id -- id-ul dupa care se cauta cartea
	// out: indicele cartii in vectorul de carti, sau -1 daca cartea nu exista
	size_t get_id_index(size_t id) const;
public:
	// Creeaza un nou repo de carti.
	RepoCarti() = default;
	RepoCarti(RepoCarti &&repo_carti) = default;
	RepoCarti &operator=(RepoCarti &&repo_carti) = default;
	~RepoCarti() = default;
	
	// Nu permitem sa se copieze un repo de carti.
	RepoCarti(const RepoCarti &repo_carti) = delete;
	RepoCarti &operator=(const RepoCarti &repo_carti) = delete;
	
	// Adauga o carte in repo.
	// in: carte -- cartea care va fi adaugata
	// throw: RepoCartiException, daca cartea care se adauga este deja in repo
	void add(const Carte &carte);
	
	// Sterge o carte din repo.
	// in: id -- id-ul cartii care va fi stearsa
	// throw: RepoCartiException, daca cartea cu id-ul furnizat nu exista in repo
	void erase(size_t id);
	
	// Actualizeaza valoarea unei carti in repo.
	// in: carte -- cartea care va fi actualizata
	// throw: RepoCartiException, daca cartea nu exista in repo
	void update(const Carte &carte);
	
	// Cauta cartea cu id-ul furnizat in repo.
	// in: id -- id-ul cartii care este cautata
	// out: cartea cu id-ul furnizat
	// throw: RepoCartiException, daca cartea cu id-ul furnizat nu a putut fi gasita
	const Carte &find(size_t id) const;
	
	// Returneaza toate cartile din repo.
	const std::vector<Carte> &get_all() const;
};

class RepoInchirieriCarteException : public AppException {
private:
	std::string get_type() const override;
public:
	RepoInchirieriCarteException(const std::string &msg);
};

class RepoInchirieriCarte {
private:
	std::vector<InchiriereCarte> inchirieri_carte;
	
	// Functie interna care cauta o inchiriere in vector dupa id.
	// in: id -- id-ul dupa care se cauta inchirierea
	// out: indicele inchirierii in vectorul de inchirieri, sau -1 daca inchirierea nu exista
	size_t get_id_index(size_t id) const;
public:
	// Creeaza un nou repo de inchirieri.
	RepoInchirieriCarte() = default;
	RepoInchirieriCarte(RepoInchirieriCarte &&repo_inchirieri_carte) = default;
	RepoInchirieriCarte &operator=(RepoInchirieriCarte &&repo_inchirieri_carte) = default;
	~RepoInchirieriCarte() = default;
	
	// Nu permitem sa se copieze un repo de inchirieri.
	RepoInchirieriCarte(const RepoInchirieriCarte &repo_inchirieri_carte) = delete;
	RepoInchirieriCarte &operator=(const RepoInchirieriCarte &repo_inchirieri_carte) = delete;
	
	// Adauga o inchiriere in repo.
	// in: inchiriere_carte -- inchirierea care va fi adaugata
	// throw: RepoInchirieriCarteException, daca inchirierea care se adauga este deja in repo
	void add(const InchiriereCarte &inchiriere_carte);
	
	// Sterge o inchiriere din repo.
	// in: id -- id-ul cartii care corespunde inchirierii care va fi stearsa
	// throw: RepoInchirieriCarteException, daca inchirierea cu id-ul furnizat nu exista in repo
	void erase(size_t id);
	
	// Returneaza toate inchirierile din repo.
	const std::vector<InchiriereCarte> &get_all() const;
};

void test_repo();

#endif // repo_hpp_INCLUDED

