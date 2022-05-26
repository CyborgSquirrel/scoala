#include <algorithm>
#include <array>
#include <gsl/gsl_util>
#include <iomanip>

#include "./console_ui.hpp"
#include "./exception.hpp"

UiException::UiException(const std::string &msg)
	: AppException(msg) { }

std::string UiException::get_type() const {
	return "UiException";
}

const std::array<ConsoleUiAction, 18> ui_actions {{
	{"afiseaza carti", &ConsoleUi::afiseaza_carti},
	{"adauga carte", &ConsoleUi::adauga_carte},
	{"sterge carte", &ConsoleUi::sterge_carte},
	{"modifica carte", &ConsoleUi::modifica_carte},
	{"cauta carte", &ConsoleUi::cauta_carte},
	{"undo", &ConsoleUi::undo},
	{"filtreaza dupa titlu", &ConsoleUi::filtreaza_dupa_titlu},
	{"filtreaza dupa an", &ConsoleUi::filtreaza_dupa_an},
	{"sorteaza dupa titlu", &ConsoleUi::sorteaza_dupa_titlu},
	{"sorteaza dupa autor", &ConsoleUi::sorteaza_dupa_autor},
	{"sorteaza dupa an gen", &ConsoleUi::sorteaza_dupa_an_gen},
	{"raport carti pe an", &ConsoleUi::raport_carti_pe_an},
	{"afiseaza cos", &ConsoleUi::afiseaza_cos},
	{"adauga in cos", &ConsoleUi::adauga_in_cos},
	{"goleste cos", &ConsoleUi::goleste_cos},
	{"genereaza cos", &ConsoleUi::genereaza_cos},
	{"export cos", &ConsoleUi::export_cos},
	{"exit", &ConsoleUi::exit},
}};

ConsoleUiAction::ConsoleUiAction(std::string name, void (ConsoleUi::*method)()) : name(name), method(method) { }

std::string ConsoleUiAction::get_name() const { return this->name; }

void ConsoleUiAction::execute(ConsoleUi &ui) const {
	(ui.*this->method)();
}

ConsoleUi::ConsoleUi(SrvCarti &srv_carti, SrvInchirieriCarte &srv_inchirieri_carte)
	: running(true), srv_carti(srv_carti), srv_inchirieri_carte(srv_inchirieri_carte) { }

void ConsoleUi::print_carti(const std::vector<Carte> &carti) const {
	for (const auto &carte : carti) {
		std::cout << carte << std::endl;
	}
}

void ConsoleUi::run() {
	while (this->running) {
		std::cout << "=== biblioteca ===" << std::endl;

		gsl::index half = ui_actions.size()/2+1;
		size_t max_size = 0;
		for (gsl::index i = 0; i < half; ++i) {
			max_size = std::max(max_size, gsl::at(ui_actions, i).get_name().size());
		}
		
		for (gsl::index i = 0; i < half; ++i) {
			std::cout
				<< std::setw(2) << std::right << i+1 << ". "
				<< std::setw(max_size+3) << std::left << gsl::at(ui_actions, i).get_name();
			if (i+half < (gsl::index) ui_actions.size()) {
			std::cout
				<< std::setw(2) << std::right << i+half+1 << ". "
				<< gsl::at(ui_actions, i+half).get_name();
			}
			std::cout << std::endl;
		}
		
		gsl::index choice = 0;
		std::cout << "> ";
		try {
			this->read(choice);
			choice--;
			if (choice >= 0 && choice < (gsl::index) ui_actions.size()) {
				gsl::at(ui_actions, choice).execute(*this);
			} else {
				throw UiException("comanda invalida");
			}
		} catch (const AppException &ex) {
			std::cout << ex << std::endl;
		}
		std::cout << "Apasati enter ca sa continuati..." << std::endl;
		std::string str;
		this->read(str);
	}
}

void ConsoleUi::afiseaza_carti() {
	auto carti = this->srv_carti.get_carti();
	this->print_carti(carti);
}

// CRUD
void ConsoleUi::adauga_carte() {
	std::string titlu, autor, gen;
	int an = 0;
	
	this->read_prompt("titlu", titlu);
	this->read_prompt("autor", autor);
	this->read_prompt("gen", gen);
	this->read_prompt("an", an);
	
	this->srv_carti.add_carte(titlu, autor, gen, an);
}
void ConsoleUi::sterge_carte() {
	int id = 0;
	
	this->read_prompt("id", id);
	
	this->srv_carti.erase_carte(id);
}
void ConsoleUi::modifica_carte() {
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
void ConsoleUi::cauta_carte() {
	int id = 0;
	
	this->read_prompt("id", id);
	
	Carte carte = this->srv_carti.find_carte(id);
	std::cout << carte << std::endl;
}
void ConsoleUi::undo() {
	this->srv_carti.undo();
	std::cout << "Ultima operatie a fost refacuta." << std::endl;
}

// FILTER
void ConsoleUi::filtreaza_dupa_titlu() {
	std::string titlu;
	this->read_prompt("titlu", titlu);
	auto filtered = this->srv_carti.filter_by_titlu(titlu);
	this->print_carti(filtered);
}
void ConsoleUi::filtreaza_dupa_an() {
	int an = 0;
	this->read_prompt("an", an);
	auto filtered = this->srv_carti.filter_by_an(an);
	this->print_carti(filtered);
}

// SORT
void ConsoleUi::sorteaza_dupa_titlu() {
	auto sorted = this->srv_carti.sort_by_titlu();
	this->print_carti(sorted);
}
void ConsoleUi::sorteaza_dupa_autor() {
	auto sorted = this->srv_carti.sort_by_autor();
	this->print_carti(sorted);
}
void ConsoleUi::sorteaza_dupa_an_gen() {
	auto sorted = this->srv_carti.sort_by_an_gen();
	this->print_carti(sorted);
}

// RAPORT
void ConsoleUi::raport_carti_pe_an() {
	auto report = this->srv_carti.generate_report_carti_by_an();
	for (const auto &elem : report) {
		std::cout << elem.first << " " << elem.second << std::endl;
	}
}


// COS
void ConsoleUi::afiseaza_numar_carti_cos() {
	size_t carti = this->srv_inchirieri_carte.getCarti().size();
	std::cout << "Numarul cartilor din cos: " << carti << std::endl;
}
void ConsoleUi::afiseaza_cos() {
	const auto &carti = this->srv_inchirieri_carte.getCarti();
	this->print_carti(carti);
}
void ConsoleUi::adauga_in_cos() {
	std::string titlu;
	this->read_prompt("titlu", titlu);
	this->srv_inchirieri_carte.addInchiriere(titlu);
	this->afiseaza_numar_carti_cos();
}
void ConsoleUi::goleste_cos() {
	this->srv_inchirieri_carte.emptyInchirieri();
	this->afiseaza_numar_carti_cos();
}
void ConsoleUi::genereaza_cos() {
	int carti = 0;
	this->read_prompt("carti", carti);
	this->srv_inchirieri_carte.genereazaInchirieri(carti);
	this->afiseaza_numar_carti_cos();
}
void ConsoleUi::export_cos() {
	std::string file_path;
	this->read_prompt("file_path", file_path);
	this->srv_inchirieri_carte.csvExport(file_path);
}

void ConsoleUi::exit() { this->running = false; }
