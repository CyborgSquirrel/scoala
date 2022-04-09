#include <algorithm>
#include <array>
#include <gsl/gsl_util>
#include <iomanip>

#include "./ui.hpp"
#include "./exception.hpp"

UiException::UiException(const std::string &msg)
	: AppException(msg) { }

std::string UiException::get_type() const {
	return "UiException";
}

const std::array<UiAction, 15> ui_actions {{
	{"afiseaza carti", &Ui::afiseaza_carti},
	{"adauga carte", &Ui::adauga_carte},
	{"sterge carte", &Ui::sterge_carte},
	{"modifica carte", &Ui::modifica_carte},
	{"cauta carte", &Ui::cauta_carte},
	{"filtreaza dupa titlu", &Ui::filtreaza_dupa_titlu},
	{"filtreaza dupa an", &Ui::filtreaza_dupa_an},
	{"sorteaza dupa titlu", &Ui::sorteaza_dupa_titlu},
	{"sorteaza dupa autor", &Ui::sorteaza_dupa_autor},
	{"sorteaza dupa an gen", &Ui::sorteaza_dupa_an_gen},
	{"afiseaza cos", &Ui::afiseaza_cos},
	{"adauga in cos", &Ui::adauga_in_cos},
	{"goleste cos", &Ui::goleste_cos},
	{"genereaza cos", &Ui::genereaza_cos},
	{"exit", &Ui::exit},
}};

UiAction::UiAction(std::string name, void (Ui::*method)()) : name(name), method(method) { }

std::string UiAction::get_name() const { return this->name; }

void UiAction::execute(Ui &ui) const {
	(ui.*this->method)();
}

Ui::Ui(SrvCarti &srv_carti, SrvInchirieriCarte &srv_inchirieri_carte)
	: running(true), srv_carti(srv_carti), srv_inchirieri_carte(srv_inchirieri_carte)
{}

void Ui::print_carti(const std::vector<Carte> &carti) const {
	for (const auto &carte : carti) {
		std::cout << carte << std::endl;
	}
}

void Ui::run() {
	while (this->running) {
		std::cout << "=== biblioteca ===" << std::endl;
		for (gsl::index i = 0; i < ui_actions.size(); ++i) {
			std::cout << std::setw(2) << i+1 << ". " << gsl::at(ui_actions, i).get_name() << std::endl;
		}
		
		gsl::index choice = 0;
		std::cout << "> ";
		try {
			this->read(choice);
			choice--;
			if (choice >= 0 && choice < ui_actions.size()) {
				gsl::at(ui_actions, choice).execute(*this);
			} else {
				throw UiException("comanda invalida");
			}
		} catch (const AppException &ex) {
			std::cout << ex << std::endl;
		}
		std::cout << "Apasati enter ca sa continuati...";
		std::string str;
		this->read(str);
	}
}

void Ui::afiseaza_carti() {
	auto carti = this->srv_carti.get_carti();
	this->print_carti(carti);
}

// CRUD
void Ui::adauga_carte() {
	std::string titlu, autor, gen;
	int an = 0;
	
	this->read_prompt("titlu", titlu);
	this->read_prompt("autor", autor);
	this->read_prompt("gen", gen);
	this->read_prompt("an", an);
	
	this->srv_carti.add_carte(titlu, autor, gen, an);
}
void Ui::sterge_carte() {
	int id = 0;
	
	this->read_prompt("id", id);
	
	this->srv_carti.erase_carte(id);
}
void Ui::modifica_carte() {
	int id = 0;
	std::string titlu, autor, gen;
	int an = 0;
	
	this->read_prompt("id", id);
	this->read_prompt("titlu", titlu);
	this->read_prompt("autor", autor);
	this->read_prompt("gen", gen);
	this->read_prompt("an", an);
	
	this->srv_carti.update_carte(id, titlu, autor, gen, an);
}
void Ui::cauta_carte() {
	int id = 0;
	
	this->read_prompt("id", id);
	
	Carte carte = this->srv_carti.find_carte(id);
	std::cout << carte << std::endl;
}

// FILTER
void Ui::filtreaza_dupa_titlu() {
	std::string titlu;
	this->read_prompt("titlu", titlu);
	auto filtered = this->srv_carti.filter_by_titlu(titlu);
	this->print_carti(filtered);
}
void Ui::filtreaza_dupa_an() {
	int an = 0;
	this->read_prompt("an", an);
	auto filtered = this->srv_carti.filter_by_an(an);
	this->print_carti(filtered);
}

// SORT
void Ui::sorteaza_dupa_titlu() {
	auto sorted = this->srv_carti.sort_by_titlu();
	this->print_carti(sorted);
}
void Ui::sorteaza_dupa_autor() {
	auto sorted = this->srv_carti.sort_by_autor();
	this->print_carti(sorted);
}
void Ui::sorteaza_dupa_an_gen() {
	auto sorted = this->srv_carti.sort_by_an_gen();
	this->print_carti(sorted);
}

// COS
void Ui::afiseaza_numar_carti_cos() {
	int carti = this->srv_inchirieri_carte.get_carti().size();
	std::cout << "Numarul cartilor din cos: " << carti << std::endl;
}
void Ui::afiseaza_cos() {
	const auto &carti = this->srv_inchirieri_carte.get_carti();
	this->print_carti(carti);
}
void Ui::adauga_in_cos() {
	std::string titlu;
	this->read_prompt("titlu", titlu);
	this->srv_inchirieri_carte.add_inchiriere(titlu);
	this->afiseaza_numar_carti_cos();
}
void Ui::goleste_cos() {
	this->srv_inchirieri_carte.empty_inchirieri();
	this->afiseaza_numar_carti_cos();
}
void Ui::genereaza_cos() {
	int carti = 0;
	this->read_prompt("carti", carti);
	this->srv_inchirieri_carte.genereaza_inchirieri(carti);
	this->afiseaza_numar_carti_cos();
}

void Ui::exit() { this->running = false; }
