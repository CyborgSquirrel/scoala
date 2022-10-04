#include <iostream>

#include <algorithm>
#include <chrono>
#include <fstream>
#include <gsl/gsl_assert>
#include <random>
#include <sstream>

#include "./srv.hpp"

// UNDO
SrvCartiUndoAdd::SrvCartiUndoAdd(int id)
	: id(id) { }
void SrvCartiUndoAdd::undo(SrvCarti &srv_carti) {
	srv_carti.repo.erase(this->id);
}

SrvCartiUndoErase::SrvCartiUndoErase(const Carte &carte)
	: carte(carte) { }
void SrvCartiUndoErase::undo(SrvCarti &srv_carti) {
	srv_carti.repo.add(this->carte);
}

SrvCartiUndoUpdate::SrvCartiUndoUpdate(const Carte &carte)
	: carte(carte) { }
void SrvCartiUndoUpdate::undo(SrvCarti &srv_carti) {
	srv_carti.repo.update(this->carte);
}

// SRV CARTI
SrvCartiException::SrvCartiException(const std::string &msg)
	: AppException(msg) { }

std::string SrvCartiException::get_type() const {
	return "SrvCartiException";
}

SrvCarti::SrvCarti(RepoCarti &repo_carti)
	: last_id(0), repo(repo_carti), undo_stack() { }

void SrvCarti::add_carte(
	const std::string &titlu,
	const std::string &autor,
	const std::string &gen,
	int an
) {
	this->repo.add({ this->last_id, titlu, autor, gen, an });
	this->undo_stack.push(std::make_unique<SrvCartiUndoAdd>(this->last_id));
	this->last_id++;
}

void SrvCarti::erase_carte(int id) {
	Carte carte = this->repo.find(id);
	this->repo.erase(id);
	this->undo_stack.push(std::make_unique<SrvCartiUndoErase>(carte));
}

void SrvCarti::update_carte(
	size_t id,
	const std::string &titlu,
	const std::string &autor,
	const std::string &gen,
	int an
) {
	Carte carte = this->repo.find(id);
	this->repo.update({ id, titlu, autor, gen, an });
	this->undo_stack.push(std::make_unique<SrvCartiUndoUpdate>(carte));
}

void SrvCarti::undo() {
	if (this->undo_stack.empty()) {
		throw SrvCartiException("nu mai exista operatii care pot fi refacute");
	} else {
		auto top = std::move(this->undo_stack.top());
		this->undo_stack.pop();
		top->undo(*this);
	}
}

const Carte &SrvCarti::find_carte(size_t id) const {
	return this->repo.find(id);
}

const std::vector<Carte> &SrvCarti::get_carti() const {
	return this->repo.get_all();
}

std::vector<Carte> SrvCarti::filter_by_titlu(const std::string &filter) const {
	auto carti = this->repo.get_all();
	std::vector<Carte> filtered;
	std::copy_if(
		carti.begin(), carti.end(),
		std::back_inserter(filtered),
		[&](const Carte &carte) { return carte.get_titlu().find(filter) != std::string::npos; }
	);
	return filtered;
}
std::vector<Carte> SrvCarti::filter_by_an(int an) const {
	auto carti = this->repo.get_all();
	std::vector<Carte> filtered;
	std::copy_if(
		carti.begin(), carti.end(),
		std::back_inserter(filtered),
		[an](const Carte &carte) { return carte.get_an() == an; }
	);
	return filtered;
}

std::vector<Carte> SrvCarti::sort_by_titlu() const {
	auto carti = this->repo.get_all();
	std::sort(
		carti.begin(), carti.end(),
		[](Carte &lhs, Carte &rhs){ return lhs.get_titlu() < rhs.get_titlu(); }
	);
	return carti;
}
std::vector<Carte> SrvCarti::sort_by_autor() const {
	auto carti = this->repo.get_all();
	std::sort(
		carti.begin(), carti.end(),
		[](Carte &lhs, Carte &rhs){ return lhs.get_autor() < rhs.get_autor(); }
	);
	return carti;
}
std::vector<Carte> SrvCarti::sort_by_an_gen() const {
	auto carti = this->repo.get_all();
	std::sort(
		carti.begin(), carti.end(),
		[](Carte &lhs, Carte &rhs){ return lhs.get_an() < rhs.get_an() || (lhs.get_an() == rhs.get_an() && lhs.get_gen() < rhs.get_gen()); }
	);
	return carti;
}

std::map<int, int> SrvCarti::generate_report_carti_by_an() const {
	std::map<int, int> report;
	auto carti = this->repo.get_all();
	for (const auto &carte : carti) {
		if (report.count(carte.get_an()) == 0) {
			report[carte.get_an()] = 0;
		}
		report[carte.get_an()]++;
	}
	return report;
}

std::map<std::string, int> SrvCarti::generate_report_gen_amount() const {
	std::map<std::string, int> report;
	auto carti = this->repo.get_all();
	for (const auto &carte : carti) {
		if (report.count(carte.get_gen()) == 0) {
			report[carte.get_gen()] = 0;
		}
		report[carte.get_gen()]++;
	}
	return report;
}


// SRV INCHIRIERI CARTE
SrvInchirieriCarteException::SrvInchirieriCarteException(const std::string &msg)
	: AppException(msg) { }

std::string SrvInchirieriCarteException::get_type() const {
	return "SrvInchirieriCarteException";
}

SrvInchirieriCarte::SrvInchirieriCarte(
	const RepoCarti &repo_carti,
	RepoInchirieriCarte &repo_inchirieri_carte
) : repo_carti(repo_carti), repo_inchirieri_carte(repo_inchirieri_carte) { }

void SrvInchirieriCarte::addInchiriere(
	const std::string &titlu
) {
	const auto &carti = this->repo_carti.get_all();
	auto it = std::find_if(
		carti.begin(), carti.end(),
		[&](const Carte &carte){ return carte.get_titlu() == titlu; }
	);
	if (it == carti.end()) {
		throw SrvInchirieriCarteException("nu exista carte cu titlul furnizat");
	} else {
		this->repo_inchirieri_carte.add({ it->get_id() });
		this->addedInchiriere();
	}
}

void SrvInchirieriCarte::genereazaInchirieri(int amount) {
	auto carti = this->repo_carti.get_all();
	
	auto seed = std::chrono::system_clock::now().time_since_epoch().count(); 
	std::shuffle(carti.begin(), carti.end(), std::default_random_engine(seed));
	
	for (size_t i = 0; i < carti.size() && amount > 0; ++i) {
		try {
			this->repo_inchirieri_carte.add(InchiriereCarte { carti[i].get_id() });
			this->addedInchiriere();
			amount--;
		} catch (const RepoInchirieriCarteException &ex) { }
	}
}

void SrvInchirieriCarte::emptyInchirieri() {
	auto inchirieri_carte = this->repo_inchirieri_carte.get_all();
	for (const auto &inchiriere_carte : inchirieri_carte) {
		this->repo_inchirieri_carte.erase(inchiriere_carte.get_carte_id());
	}
	this->emptiedInchirieri();
}

std::vector<Carte> SrvInchirieriCarte::getCarti() const {
	const auto &inchirieri_carte = this->repo_inchirieri_carte.get_all();
	std::vector<Carte> carti;
	for (const auto &inchiriere_carte : inchirieri_carte) {
		carti.push_back(this->repo_carti.find(inchiriere_carte.get_carte_id()));
	}
	return carti;
}

void SrvInchirieriCarte::csvExport(const std::string &file_path) const {
	std::ofstream fout(file_path);
	const auto &inchirieri_carte = this->repo_inchirieri_carte.get_all();
	for (const auto &inchiriere_carte : inchirieri_carte) {
		auto carte = this->repo_carti.find(inchiriere_carte.get_carte_id());
		fout << carte.get_titlu() << "," << carte.get_autor() << "," << carte.get_gen() << "," << carte.get_an() << "\n";
	}
}

void SrvInchirieriCarte::addedInchiriere() {
	for (const auto &id_signal : m_addedInchiriereSignals) {
		id_signal.second();
	}
}
size_t SrvInchirieriCarte::connectAddedInchiriere(std::function<void ()> signal) {
	size_t id = m_lastAddedInchiriereSignalId;
	m_addedInchiriereSignals[id] = signal;
	m_lastAddedInchiriereSignalId++;
	return id;
}
void SrvInchirieriCarte::disconnectAddedInchiriere(size_t id) {
	m_addedInchiriereSignals.erase(id);
}

void SrvInchirieriCarte::emptiedInchirieri() {
	for (const auto &id_signal : m_emptiedInchirieriSignals) {
		id_signal.second();
	}
}
size_t SrvInchirieriCarte::connectEmptiedInchirieri(std::function<void ()> signal) {
	size_t id = m_lastEmptiedInchirieriSignalId;
	m_emptiedInchirieriSignals[id] = signal;
	m_lastEmptiedInchirieriSignalId++;
	return id;
}
void SrvInchirieriCarte::disconnectEmptiedInchirieri(size_t id) {
	m_emptiedInchirieriSignals.erase(id);
}

void test_srv_carti_crud() {
	RepoCarti repo;
	SrvCarti srv { repo };
	
	std::string a_titlu = "The Picture of Dorian Grey";
	std::string a_autor = "Oscar Wilde";
	std::string a_gen = "classic";
	const int a_an = 1850;
	
	std::string b_titlu = "1984";
	std::string b_autor = "George Orwell";
	std::string b_gen = "dystopia";
	const int b_an = 1948;
	
	std::string c_titlu = "Harry Potter";
	std::string c_autor = "J.K. Rowling";
	std::string c_gen = "fiction";
	const int c_an = 1990;
	
	// add_carte
	srv.add_carte(a_titlu, a_autor, a_gen, a_an);
	srv.add_carte(b_titlu, b_autor, b_gen, b_an);
	srv.add_carte(c_titlu, c_autor, c_gen, c_an);
	
	// find_carte
	Carte a = srv.find_carte(0);
	Ensures(a.get_titlu() == a_titlu);
	Ensures(a.get_autor() == a_autor);
	Ensures(a.get_gen() == a_gen);
	Ensures(a.get_an() == a_an);
	
	Carte b = srv.find_carte(1);
	Ensures(b.get_titlu() == b_titlu);
	Ensures(b.get_autor() == b_autor);
	Ensures(b.get_gen() == b_gen);
	Ensures(b.get_an() == b_an);
	
	Carte c = srv.find_carte(2);
	Ensures(c.get_titlu() == c_titlu);
	Ensures(c.get_autor() == c_autor);
	Ensures(c.get_gen() == c_gen);
	Ensures(c.get_an() == c_an);
	
	// get_carti
	std::vector<Carte> carti = {a, b, c};
	Ensures(srv.get_carti() == carti);
	
	// update_carte
	std::string d_titlu = "Brave New World";
	std::string d_autor = "Aldous Huxley";
	std::string d_gen = "dystopia";
	const int d_an = 1931;
	
	srv.update_carte(1, d_titlu, d_autor, d_gen, d_an);
	Carte d = srv.find_carte(1);
	Ensures(d.get_titlu() == d_titlu);
	Ensures(d.get_autor() == d_autor);
	Ensures(d.get_gen() == d_gen);
	Ensures(d.get_an() == d_an);
	
	// erase_carte
	srv.erase_carte(2);
	srv.erase_carte(0);
	srv.erase_carte(1);
	
	// undo
	srv.undo();
	Ensures(srv.get_carti().size() == 1);
	Carte nd = srv.find_carte(1);
	Ensures(nd.get_titlu() == d_titlu);
	Ensures(nd.get_autor() == d_autor);
	Ensures(nd.get_gen() == d_gen);
	Ensures(nd.get_an() == d_an);
	
	srv.undo();
	Ensures(srv.get_carti().size() == 2);
	Carte na = srv.find_carte(0);
	Ensures(na.get_titlu() == a_titlu);
	Ensures(na.get_autor() == a_autor);
	Ensures(na.get_gen() == a_gen);
	Ensures(na.get_an() == a_an);
	
	srv.undo();
	Ensures(srv.get_carti().size() == 3);
	Carte nc = srv.find_carte(2);
	Ensures(nc.get_titlu() == c_titlu);
	Ensures(nc.get_autor() == c_autor);
	Ensures(nc.get_gen() == c_gen);
	Ensures(nc.get_an() == c_an);
	
	srv.undo();
	Ensures(srv.get_carti().size() == 3);
	Carte nb = srv.find_carte(1);
	Ensures(nb.get_titlu() == b_titlu);
	Ensures(nb.get_autor() == b_autor);
	Ensures(nb.get_gen() == b_gen);
	Ensures(nb.get_an() == b_an);
	
	srv.undo();
	Ensures(srv.get_carti().size() == 2);
	srv.undo();
	Ensures(srv.get_carti().size() == 1);
	srv.undo();
	Ensures(srv.get_carti().size() == 0);
	
	try { srv.undo(); Ensures(false); }
	catch (const SrvCartiException &ex) { Ensures(ex.as_string() == "SrvCartiException: nu mai exista operatii care pot fi refacute"); }
}

void test_srv_carti_filter_and_sort() {
	RepoCarti repo;
	SrvCarti srv { repo };
	
	std::string a_titlu = "The Picture of Dorian Grey";
	std::string a_autor = "Oscar Wilde";
	std::string a_gen = "classic";
	const int a_an = 1850;
	
	std::string b_titlu = "1984";
	std::string b_autor = "George Orwell";
	std::string b_gen = "dystopia";
	const int b_an = 1948;
	
	std::string c_titlu = "Harry Potter";
	std::string c_autor = "J.K. Rowling";
	std::string c_gen = "fiction";
	const int c_an = 1990;
	
	std::string d_titlu = "Brave New World";
	std::string d_autor = "Aldous Huxley";
	std::string d_gen = "dystopia";
	const int d_an = 1931;
	
	srv.add_carte(a_titlu, a_autor, a_gen, a_an);
	srv.add_carte(b_titlu, b_autor, b_gen, b_an);
	srv.add_carte(c_titlu, c_autor, c_gen, c_an);
	srv.add_carte(d_titlu, d_autor, d_gen, d_an);
	
	Carte a = srv.find_carte(0);
	Carte b = srv.find_carte(1);
	Carte c = srv.find_carte(2);
	Carte d = srv.find_carte(3);
	
	// FILTER
	auto filter_titlu = srv.filter_by_titlu("Har");
	std::vector<Carte> filter_titlu_res = { c };
	Ensures(filter_titlu == filter_titlu_res);
	
	const int filter_an_val = 1948;
	auto filter_an = srv.filter_by_an(filter_an_val);
	std::vector<Carte> filter_an_res = { b };
	Ensures(filter_an == filter_an_res);
	
	// SORT
	auto sort_titlu = srv.sort_by_titlu();
	std::vector<Carte> sort_titlu_res = { b, d, c, a };
	Ensures(sort_titlu == sort_titlu_res);
	
	auto sort_autor = srv.sort_by_autor();
	std::vector<Carte> sort_autor_res = { d, b, c, a };
	Ensures(sort_autor == sort_autor_res);
	
	auto sort_an_gen = srv.sort_by_an_gen();
	std::vector<Carte> sort_an_gen_res = { a, d, b, c };
	Ensures(sort_an_gen == sort_an_gen_res);
	
	// REPORT
	srv.add_carte(a_titlu, a_autor, a_gen, a_an);
	srv.add_carte(a_titlu, a_autor, a_gen, a_an);
	srv.add_carte(a_titlu, a_autor, a_gen, a_an);
	srv.add_carte(b_titlu, b_autor, b_gen, b_an);
	srv.add_carte(b_titlu, b_autor, b_gen, b_an);
	
	auto report_an = srv.generate_report_carti_by_an();
	Ensures(report_an.size() == 4);
	Ensures(report_an[1850] == 4);
	Ensures(report_an[1931] == 1);
	Ensures(report_an[1948] == 3);
	Ensures(report_an[1990] == 1);
	
	auto report_gen = srv.generate_report_gen_amount();
	Ensures(report_gen.size() == 3);
	
	Ensures(report_gen["classic"] == 4);
	Ensures(report_gen["dystopia"] == 4);
	Ensures(report_gen["fiction"] == 1);
}

void test_srv_inchirieri_carte() {
	RepoCarti repo_carti;
	RepoInchirieriCarte repo_inchirieri_carte;
	SrvCarti srvCarti { repo_carti };
	SrvInchirieriCarte srvInchirieriCarte { repo_carti, repo_inchirieri_carte };
	
	std::string a_titlu = "The Picture of Dorian Grey";
	std::string a_autor = "Oscar Wilde";
	std::string a_gen = "classic";
	const int a_an = 1850;
	
	std::string b_titlu = "1984";
	std::string b_autor = "George Orwell";
	std::string b_gen = "dystopia";
	const int b_an = 1948;
	
	std::string c_titlu = "Harry Potter";
	std::string c_autor = "J.K. Rowling";
	std::string c_gen = "fiction";
	const int c_an = 1990;
	
	srvCarti.add_carte(a_titlu, a_autor, a_gen, a_an);
	srvCarti.add_carte(b_titlu, b_autor, b_gen, b_an);
	srvCarti.add_carte(c_titlu, c_autor, c_gen, c_an);
	
	// addInchiriere
	try { srvInchirieriCarte.addInchiriere("Getting Things Done"); }
	catch (const SrvInchirieriCarteException &ex) {
		Ensures(ex.as_string() == "SrvInchirieriCarteException: nu exista carte cu titlul furnizat");
	}
	
	srvInchirieriCarte.addInchiriere(b_titlu);
	srvInchirieriCarte.addInchiriere(a_titlu);
	srvInchirieriCarte.addInchiriere(c_titlu);
	
	// emptyInchirieri
	srvInchirieriCarte.emptyInchirieri();
	srvInchirieriCarte.emptyInchirieri();
	srvInchirieriCarte.emptyInchirieri();
	
	// get_carti
	srvInchirieriCarte.addInchiriere(b_titlu);
	srvInchirieriCarte.addInchiriere(c_titlu);
	auto carti = srvInchirieriCarte.getCarti();
	
	Ensures(carti.size() == 2);
	
	Ensures(carti[0].get_titlu() == b_titlu);
	Ensures(carti[0].get_autor() == b_autor);
	Ensures(carti[0].get_gen() == b_gen);
	Ensures(carti[0].get_an() == b_an);
	
	Ensures(carti[1].get_titlu() == c_titlu);
	Ensures(carti[1].get_autor() == c_autor);
	Ensures(carti[1].get_gen() == c_gen);
	Ensures(carti[1].get_an() == c_an);
	
	// genereazaInchirieri
	const int two = 2;
	const int fifteen = 15;
	const int one_thousand = 1000;
	srvInchirieriCarte.genereazaInchirieri(two);
	srvInchirieriCarte.genereazaInchirieri(fifteen);
	srvInchirieriCarte.emptyInchirieri();
	srvInchirieriCarte.genereazaInchirieri(one_thousand);
	
	// export
	srvInchirieriCarte.emptyInchirieri();
	srvInchirieriCarte.addInchiriere(b_titlu);
	srvInchirieriCarte.addInchiriere(a_titlu);
	srvInchirieriCarte.addInchiriere(c_titlu);
	srvInchirieriCarte.csvExport("./test/export.csv");
	
	std::ifstream fin("./test/export.csv");
	std::stringstream ss;
	ss << fin.rdbuf();
	
	std::string exported {
		"1984,George Orwell,dystopia,1948\n"
		"The Picture of Dorian Grey,Oscar Wilde,classic,1850\n"
		"Harry Potter,J.K. Rowling,fiction,1990\n"
	};
	
	Ensures(ss.str() == exported);
}

void test_srv() {
	test_srv_carti_crud();
	test_srv_carti_filter_and_sort();
	test_srv_inchirieri_carte();
}

