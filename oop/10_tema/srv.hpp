#ifndef srv_hpp_INCLUDED
#define srv_hpp_INCLUDED

#include <map>
#include <memory>
#include <stack>
#include <vector>

#include "./exception.hpp"
#include "./repo.hpp"

class SrvCarti;

class SrvCartiUndo {
public:
	virtual void undo(SrvCarti &srv_carti) = 0;
	virtual ~SrvCartiUndo() = default;
};

class SrvCartiException : public AppException {
private:
	std::string get_type() const override;
public:
	SrvCartiException(const std::string &msg);
};

class SrvCartiUndoAdd : public SrvCartiUndo {
private:
	int id;
public:
	SrvCartiUndoAdd(int id);
	void undo(SrvCarti &srv_carti) override;
};

class SrvCartiUndoErase : public SrvCartiUndo {
private:
	Carte carte;
public:
	SrvCartiUndoErase(const Carte &carte);
	void undo(SrvCarti &srv_carti) override;
};

class SrvCartiUndoUpdate : public SrvCartiUndo {
private:
	Carte carte;
public:
	SrvCartiUndoUpdate(const Carte &carte);
	void undo(SrvCarti &srv_carti) override;
};

class SrvCarti {
private:
	size_t last_id;
	RepoCarti &repo;
	std::stack<std::unique_ptr<SrvCartiUndo>> undo_stack;
public:
	friend SrvCartiUndoAdd;
	friend SrvCartiUndoErase;
	friend SrvCartiUndoUpdate;
	
	// Creeaza un nou srv de carti, cu repo-ul furnizat.
	// in: repo_carti -- repo-ul de carti furnizat
	SrvCarti(RepoCarti &repo_carti);
	SrvCarti(SrvCarti &&srv_carti) = default;
	SrvCarti &operator=(SrvCarti &&srv_carti) = delete;
	~SrvCarti() = default;
	
	// Nu permitem sa se copieze un srv de carti.
	SrvCarti(const SrvCarti &srv_carti) = delete;
	SrvCarti &operator=(const SrvCarti &srv_carti) = delete;
	
	// Adauga cartea cu titlul, autorul, genul, si anul furnizate in srv.
	// in: titlu -- titlul cartii care va fi adaugata
	//     autor -- autorul cartii care va fi adaugata
	//     gen -- genul cartii care va fi adaugata
	//     an -- anul in care a fost publicata cartea care va fi adaugata
	void add_carte(
		const std::string &titlu,
		const std::string &autor,
		const std::string &gen,
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
		size_t id,
		const std::string &titlu,
		const std::string &autor,
		const std::string &gen,
		int an
	);
	
	// Reface ultima operatie de adaugare, stergere, sau modificare.
	void undo();
	
	// Cauta cartea cu id-ul furnizat.
	// in: id -- id-ul cartii care va fi cautata
	const Carte &find_carte(size_t id) const;
	
	// Returneaza toate cartile.
	const std::vector<Carte> &get_carti() const;
	
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
	
	// Returneaza un map, in care cheia reprezinta anul, iar valoarea numarul de carti publicate in acel an.
	// out: map in care cheia reprezinta anul, iar valoarea numarul de carti publicate in acel an
	std::map<int, int> generate_report_carti_by_an() const;
	
	// Returneaza un map, in care cheia reprezinta genul, iar valoarea numarul de carti cu acel gen.
	// out: map in care cheia reprezinta genul, iar valoarea numarul de carti cu acel gen
	std::map<std::string, int> generate_report_gen_amount() const;
};

class SrvInchirieriCarteException : public AppException {
private:
	std::string get_type() const override;
public:
	SrvInchirieriCarteException(const std::string &msg);
};

class SrvInchirieriCarte {
private:
	const RepoCarti &repo_carti;
	RepoInchirieriCarte &repo_inchirieri_carte;
public:
	// Creeaza un nou srv de inchirieri de carti, cu repo-ul furnizat.
	// in: repo_carti -- repo-ul de carti furnizat
	SrvInchirieriCarte(
		const RepoCarti &repo_carti,
		RepoInchirieriCarte &repo_inchirieri_carte
	);
	SrvInchirieriCarte(SrvInchirieriCarte &&srv_inchirieri_carte) = default;
	SrvInchirieriCarte &operator=(SrvInchirieriCarte &&srv_inchirieri_carte) = delete;
	~SrvInchirieriCarte() = default;
	
	// Nu permitem sa se copieze un srv de inchirieri de carti.
	SrvInchirieriCarte(const SrvInchirieriCarte &srv_inchirieri_carte) = delete;
	SrvInchirieriCarte &operator=(const SrvInchirieriCarte &srv_inchirieri_carte) = delete;
	
	// Adauga o inchiriere a cartii cu titlul furnizat.
	// in: titlu -- titlul cartii care va fi adaugata
	// throw: SrvInchirieriCarteException, daca nu exista o carte cu titlul furnizat
	void add_inchiriere(const std::string &titlu);
	
	// Genereaza amount inchirieri, si le adauga.
	// in: amount -- numarul de inchirieri care vor fi generate si adaugate
	void genereaza_inchirieri(int amount);
	
	// Sterge toate inchirierile.
	void empty_inchirieri();
	
	// Returneaza toate cartile care sunt inchiriate.
	std::vector<Carte> get_carti() const;
	
	// Exporta cartile din cos in fisierul dat prin file_path.
	// in: file_path -- path-ul fisierul in care vor fi salvate cartile
	void csv_export(const std::string &file_path) const;
};

void test_srv();

#endif // srv_hpp_INCLUDED

