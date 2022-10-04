#include <array>
#include <iostream>
#include <iomanip>

#include "./ui.hpp"
#include "./exception.hpp"

UiException::UiException(const std::string &msg) {
	this->msg = msg;
}

std::ostream &operator<<(std::ostream &out, const UiException &ex) {
	return exception_write_msg(out, "Eroare de ui", ex.msg);
}

const std::array<UiAction, 11> ui_actions {{
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
	{"exit", &Ui::exit},
}};

UiAction::UiAction(std::string name, void (Ui::*method)()) {
	this->name = name;
	this->method = method;
}

std::string UiAction::get_name() const { return this->name; }

void UiAction::execute(Ui &ui) const {
	(ui.*this->method)();
}

Ui::Ui(SrvCarti &srv) : srv(srv) {
	this->running = true;
}

void Ui::print_carti(const std::vector<Carte> &carti) const {
	for (auto &carte : carti) {
		std::cout << carte << std::endl;
	}
}

void Ui::run() {
	while (this->running) {
		for (size_t i = 0; i < ui_actions.size(); ++i) {
			std::cout << std::setw(2) << i+1 << ". " << ui_actions[i].get_name() << std::endl;
		}
		
		size_t choice;
		std::cout << "> ";
		try {
			this->read(choice);
			choice--;
			if (choice >= 0 && choice < ui_actions.size()) {
				ui_actions[choice].execute(*this);
			} else {
				throw UiException("comanda invalida");
			}
		} catch (const UiException &ex) {
			std::cout << ex << std::endl;
		}
		std::cout << std::endl;
	}
}

void Ui::afiseaza_carti() {
	auto carti = this->srv.get_carti();
	this->print_carti(carti);
}

// CRUD
void Ui::adauga_carte() {
	std::string titlu, autor, gen;
	int an;
	
	this->read_prompt("titlu", titlu);
	this->read_prompt("autor", autor);
	this->read_prompt("gen", gen);
	this->read_prompt("an", an);
	
	this->srv.add_carte(titlu, autor, gen, an);
}
void Ui::sterge_carte() {
	int id;
	
	this->read_prompt("id", id);
	
	this->srv.erase_carte(id);
}
void Ui::modifica_carte() {
	int id;
	std::string titlu, autor, gen;
	int an;
	
	this->read_prompt("id", id);
	this->read_prompt("titlu", titlu);
	this->read_prompt("autor", autor);
	this->read_prompt("gen", gen);
	this->read_prompt("an", an);
	
	this->srv.update_carte(id, titlu, autor, gen, an);
}
void Ui::cauta_carte() {
	int id;
	
	this->read_prompt("id", id);
	
	Carte carte = this->srv.find_carte(id);
	std::cout << carte << std::endl;
}

// FILTER
void Ui::filtreaza_dupa_titlu() {
	std::string titlu;
	this->read_prompt("titlu", titlu);
	auto filtered = this->srv.filter_by_titlu(titlu);
	this->print_carti(filtered);
}
void Ui::filtreaza_dupa_an() {
	int an;
	this->read_prompt("an", an);
	auto filtered = this->srv.filter_by_an(an);
	this->print_carti(filtered);
}

// SORT
void Ui::sorteaza_dupa_titlu() {
	auto sorted = this->srv.sort_by_titlu();
	this->print_carti(sorted);
}
void Ui::sorteaza_dupa_autor() {
	auto sorted = this->srv.sort_by_autor();
	this->print_carti(sorted);
}
void Ui::sorteaza_dupa_an_gen() {
	auto sorted = this->srv.sort_by_an_gen();
	this->print_carti(sorted);
}

void Ui::exit() { this->running = false; }
