#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "./domain.h"
#include "./srv.h"
#include "./valid.h"

struct ConsoleUi {
	struct SrvCheltuieli srv_cheltuieli;
};

struct ConsoleUi console_ui_new(struct SrvCheltuieli srv_cheltuieli) {
	struct ConsoleUi console_ui;
	console_ui.srv_cheltuieli = srv_cheltuieli;
	return console_ui;
}

void console_ui_drop(struct ConsoleUi *console_ui) {
	srv_cheltuieli_drop(&console_ui->srv_cheltuieli);
}

struct Data read_data() {
	struct Data data;
	
	printf("data (dd/mm/yyyy) = ");
	scanf("%d/%d/%d", &data.zi, &data.luna, &data.an);
	if (!validate_data(&data)) exit(1);
	
	return data;
}

float read_suma() {
	float suma;
	
	printf("suma = ");
	scanf("%f", &suma);
	if (!validate_suma(suma)) exit(1);
	
	return suma;
}

enum Tip read_tip() {
	enum Tip tip;
	char tip_str[128];
	
	printf("tip (mancare/transport/telefon&internet/imbracaminte/altele) = ");
	scanf("%s", tip_str);
	
	for (char *p = tip_str; *p != '\0'; ++p) *p = tolower(*p);
	
	     if (strcmp(tip_str, "mancare"         ) == 0) tip = MANCARE;
	else if (strcmp(tip_str, "transport"       ) == 0) tip = TRANSPORT;
	else if (strcmp(tip_str, "telefon&internet") == 0) tip = TELEFON_INTERNET;
	else if (strcmp(tip_str, "imbracaminte"    ) == 0) tip = IMBRACAMINTE;
	else if (strcmp(tip_str, "altele"          ) == 0) tip = ALTELE;
	else exit(1);
	
	return tip;
}

int read_id() {
	int id;
	printf("id = ");
	scanf("%d", &id);
	return id;
}

void console_ui_print_cheltuieli(struct ConsoleUi *console_ui) {
	struct Vec *vec = &console_ui->srv_cheltuieli.repo.vec;
	
	for (int i = 0; i < vec->len; ++i) {
		struct Cheltuiala cheltuiala = vec_get(vec, i);
		cheltuiala_print(&cheltuiala);
		printf("\n");
	}
}

void console_ui_add_cheltuiala(struct ConsoleUi *console_ui) {
	struct Data data = read_data();
	float suma = read_suma();
	enum Tip tip = read_tip();
	
	srv_cheltuieli_add(
		&console_ui->srv_cheltuieli,
		data, suma, tip
	);
}

void console_ui_update_cheltuiala(struct ConsoleUi *console_ui) {
	int id = read_id();
	struct Data data = read_data();
	float suma = read_suma();
	enum Tip tip = read_tip();
	
	srv_cheltuieli_update(
		&console_ui->srv_cheltuieli,
		id, data, suma, tip
	);
}

void console_ui_erase_cheltuiala(struct ConsoleUi *console_ui) {
	int id = read_id();
	
	srv_cheltuieli_erase(
		&console_ui->srv_cheltuieli,
		id
	);
}

#define COMMANDS 4
void (*console_ui_commands[COMMANDS]) (struct ConsoleUi*) = {
	console_ui_print_cheltuieli,
	console_ui_add_cheltuiala,
	console_ui_update_cheltuiala,
	console_ui_erase_cheltuiala
};
char *console_ui_command_names[COMMANDS] = {
	"Afiseaza toate cheltuielile",
	"Adauga cheltuiala",
	"Modifica cheltuiala",
	"Sterge cheltuiala"
};

void console_ui_run(struct ConsoleUi *console_ui) {
	while (1) {
		for (int i = 0; i < COMMANDS; ++i) {
			printf("%d. %s\n", i+1, console_ui_command_names[i]);
		}
		
		int choice;
		printf("> ");
		scanf("%d", &choice);
		choice--;
		if (choice >= 0 && choice < COMMANDS) {
			console_ui_commands[choice](console_ui);
		}
		printf("\n");
	}
}

int main(int argc, char **argv) {
	test_vec();
	
	struct ConsoleUi console_ui = console_ui_new(srv_cheltuieli_new());
	console_ui_run(&console_ui);
	console_ui_drop(&console_ui);
	
	return 0;
}
