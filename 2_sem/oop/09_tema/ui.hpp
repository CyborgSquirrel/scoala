#ifndef ui_hpp_INCLUDED
#define ui_hpp_INCLUDED

#include <sstream>
#include <iostream>

#include "./srv.hpp"

class UiException : public AppException {
private:
	std::string get_type() const override;
public:
	UiException(const std::string &msg);
	~UiException() override = default;
};

class Ui {
private:
	bool running;
	SrvCarti &srv_carti;
	SrvInchirieriCarte &srv_inchirieri_carte;
	
	template <typename T>
	void read(T &val) const {
		std::string buf;
		std::getline(std::cin, buf);
		
		std::stringstream sstream {buf};
		sstream >> val;
		if (sstream.fail()) throw UiException("valoare invalida");
		
		char c = 0;
		sstream >> c;
		if (!sstream.fail()) throw UiException("valoare invalida");
	}
	void read(std::string &val) const {
		std::getline(std::cin, val);
	}
	
	template <typename T>
	void read_prompt(std::string name, T &val) const {
		std::cout << name << " = ";
		try {
			read(val);
		} catch (const UiException &ex) {
			throw UiException("valoare invalida pentru " + name);
		}
	}
	
	void print_carti(const std::vector<Carte> &carti) const;
	
public:
	Ui(SrvCarti &srv_carti, SrvInchirieriCarte &srv_inchirieri_carte);
	
	void run();
	
	void afiseaza_carti();
	void adauga_carte();
	void sterge_carte();
	void modifica_carte();
	void cauta_carte();
	
	void undo();
	
	void filtreaza_dupa_titlu();
	void filtreaza_dupa_an();
	
	void sorteaza_dupa_titlu();
	void sorteaza_dupa_autor();
	void sorteaza_dupa_an_gen();
	
	void raport_carti_pe_an();
	
	void afiseaza_numar_carti_cos();
	void afiseaza_cos();
	void adauga_in_cos();
	void goleste_cos();
	void genereaza_cos();
	
	void export_cos();
	
	void exit();
};

class UiAction {
private:
	std::string name;
	void (Ui::*method)();
public:
	UiAction(std::string name, void (Ui::*method)());
	std::string get_name() const;
	void execute(Ui &ui) const;
};

#endif // ui_hpp_INCLUDED

