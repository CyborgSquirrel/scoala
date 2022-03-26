#ifndef srv_hpp_INCLUDED
#define srv_hpp_INCLUDED

#include "./repo.hpp"

class SrvCarti {
private:
	int last_id;
	RepoCarti &repo;
public:
	// Creeaza un nou srv de carti, cu repo-ul furnizat.
	// in: repo_carti -- repo-ul de carti furnizat
	SrvCarti(RepoCarti &repo_carti);
	
	// Nu permitem sa se copieze un srv de carti.
	SrvCarti(const SrvCarti &srv_carti) = delete;
	
	// Adauga cartea cu titlul, autorul, genul, si anul furnizate in srv.
	// in: titlu -- titlul cartii care va fi adaugata
	//     autor -- autorul cartii care va fi adaugata
	//     gen -- genul cartii care va fi adaugata
	//     an -- anul in care a fost publicata cartea care va fi adaugata
	void add_carte(
		std::string titlu,
		std::string autor,
		std::string gen,
		int an
	);
	
	// Sterge cartea cu id-ul furnizat din srv.
	// in: id -- id-ul cartii care va fi stearsa
	void erase_carte(int id);
	
	// Actualizeaza valoarea cartii cu id-ul furnizat.
	// in: id -- id-ul cartii care va fi actualizata
	//     titlu -- titlul nou
	//     autor -- autorul nou
	//     gen -- genul nou
	//     an -- anul nou
	void update_carte(
		int id,
		std::string titlu,
		std::string autor,
		std::string gen,
		int an
	);
	
	// Cauta cu id-ul furnizat.
	// in: id -- id-ul cartii care va fi cautata
	Carte find_carte(int id) const;
	
	// Returneaza toate cartile.
	std::vector<Carte> get_carti() const;
	
	// Returneaza toate cartile filtrate dupa titlu.
	// in: filter -- vor fi returnate doar cartile care contin acest string in titlu
	// out: vector cu cartile filtrate
	std::vector<Carte> filter_by_titlu(const std::string &filter) const;
	
	// Returneaza toate cartile filtrate dupa an.
	// in: an -- vor fi returnate doar cartile care au fost publicate in acest an
	// out: vector cu cartile filtrate
	std::vector<Carte> filter_by_an(int an) const;
	
	// Returneaza toate cartile sortate dupa titlu.
	// out: vector cu cartile sortate
	std::vector<Carte> sort_by_titlu() const;
	
	// Returneaza toate cartile sortate dupa autor.
	// out: vector cu cartile sortate
	std::vector<Carte> sort_by_autor() const;
	
	// Returneaza toate cartile sortate dupa an si gen.
	// out: vector cu cartile sortate
	std::vector<Carte> sort_by_an_gen() const;
};

void test_srv();

#endif // srv_hpp_INCLUDED

