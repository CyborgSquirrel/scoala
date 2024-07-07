#ifndef console_ui_h_INCLUDED
#define console_ui_h_INCLUDED

#include <assert.h>

#include "./domain.h"
#include "./srv.h"
#include "./valid.h"

struct ConsoleUi {
	int running;
	struct SrvCheltuieli srv_cheltuieli;
};

struct ConsoleUi console_ui_new(struct SrvCheltuieli srv_cheltuieli) {
	struct ConsoleUi console_ui;
	console_ui.running = 1;
	console_ui.srv_cheltuieli = srv_cheltuieli;
	return console_ui;
}

void console_ui_drop(struct ConsoleUi *console_ui) {
	srv_cheltuieli_drop(&console_ui->srv_cheltuieli);
}

const char *const ERR_INVALID_CHOICE = "comanda invalida";
const char *const ERR_INVALID_DATA = "data invalida";
const char *const ERR_INVALID_SUMA = "suma invalida";
const char *const ERR_INVALID_TIP = "tip invalid";
const char *const ERR_INVALID_ID = "id invalid";

char *line = NULL; long unsigned int len = 0;
const char *const read_data(struct Data *data) {
	printf("data (dd/mm/yyyy) = ");
	getline(&line, &len, stdin);
	if (sscanf(line, "%d/%d/%d", &data->zi, &data->luna, &data->an) != 3) return ERR_INVALID_DATA;
	if (!validate_data(data)) return ERR_INVALID_DATA;
	return NULL;
}

const char *const read_suma(float *suma) {
	printf("suma = ");
	getline(&line, &len, stdin);
	if (sscanf(line, "%f", suma) != 1) return ERR_INVALID_SUMA;
	if (!validate_suma(*suma)) return ERR_INVALID_SUMA;
	return NULL;
}

const char *const read_tip(enum Tip *tip) {
	printf("tip (mancare/transport/telefon&internet/imbracaminte/altele) = ");
	getline(&line, &len, stdin);
	
	for (char *p = line; *p != '\0'; ++p) *p = tolower(*p);
	
	     if (strncmp(line, "mancare"         , 7 ) == 0) *tip = MANCARE;
	else if (strncmp(line, "transport"       , 9 ) == 0) *tip = TRANSPORT;
	else if (strncmp(line, "telefon&internet", 16) == 0) *tip = TELEFON_INTERNET;
	else if (strncmp(line, "imbracaminte"    , 12) == 0) *tip = IMBRACAMINTE;
	else if (strncmp(line, "altele"          , 6 ) == 0) *tip = ALTELE;
	else return ERR_INVALID_TIP;
	
	return NULL;
}

const char *const read_id(int *id) {
	printf("id = ");
	getline(&line, &len, stdin);
	if (sscanf(line, "%d", id) != 1) return ERR_INVALID_ID;
	return NULL;
}

const char *const console_ui_print_cheltuieli(struct ConsoleUi *console_ui) {
	struct Vec *vec = &console_ui->srv_cheltuieli.repo.vec;
	
	for (int i = 0; i < vec->len; ++i) {
		struct Cheltuiala cheltuiala;
		assert(vec_get(vec, &cheltuiala, i) == NULL);
		cheltuiala_print(&cheltuiala);
		printf("\n");
	}
	return NULL;
}

const char *const console_ui_add_cheltuiala(struct ConsoleUi *console_ui) {
	const char *err = NULL;
	
	struct Data data;
	float suma;
	enum Tip tip;
	
	if ((err = read_data(&data)) != NULL) return err;
	if ((err = read_suma (&suma)) != NULL) return err;
	if ((err = read_tip(&tip)) != NULL) return err;
	
	return srv_cheltuieli_add(
		&console_ui->srv_cheltuieli,
		data, suma, tip
	);
}

const char *const console_ui_update_cheltuiala(struct ConsoleUi *console_ui) {
	const char *err = NULL;
	
	int id;
	struct Data data;
	float suma;
	enum Tip tip;
	
	if ((err = read_id(&id)) != NULL) return err;
	if ((err = read_data(&data)) != NULL) return err;
	if ((err = read_suma (&suma)) != NULL) return err;
	if ((err = read_tip(&tip)) != NULL) return err;
	
	return srv_cheltuieli_update(
		&console_ui->srv_cheltuieli,
		id, data, suma, tip
	);
}

const char *const console_ui_erase_cheltuiala(struct ConsoleUi *console_ui) {
	const char *err = NULL;
	
	int id;
	if ((err = read_id(&id)) != NULL) return err;
	
	return srv_cheltuieli_erase(
		&console_ui->srv_cheltuieli,
		id
	);
}

const char *const console_ui_exit(struct ConsoleUi *console_ui) {
	console_ui->running = 0;
	return NULL;
}

#define COMMANDS 5
const char *const (*console_ui_commands[COMMANDS]) (struct ConsoleUi*) = {
	console_ui_print_cheltuieli,
	console_ui_add_cheltuiala,
	console_ui_update_cheltuiala,
	console_ui_erase_cheltuiala,
	console_ui_exit
};
char *console_ui_command_names[COMMANDS] = {
	"Afiseaza toate cheltuielile",
	"Adauga cheltuiala",
	"Modifica cheltuiala",
	"Sterge cheltuiala",
	"Exit"
};

const char *const read_choice(int *choice) {
	getline(&line, &len, stdin);
	if (sscanf(line, "%d", choice) != 1) return ERR_INVALID_CHOICE;
	(*choice)--;
	if (*choice < 0 || *choice >= COMMANDS) return ERR_INVALID_CHOICE;
	return NULL;
}

void console_ui_print_error(const char *const err) {
	printf("\e[1;31m");
	printf("Eroare: %s.\n", err);
	printf("\e[0m");
}

void console_ui_run(struct ConsoleUi *console_ui) {
	const char *err = NULL;
	while (console_ui->running) {
		for (int i = 0; i < COMMANDS; ++i) {
			printf("%d. %s\n", i+1, console_ui_command_names[i]);
		}
		
		printf("> ");
		int choice;
		if ((err = read_choice(&choice)) == NULL) {
			err = console_ui_commands[choice](console_ui);
		}
		
		if (err != NULL) console_ui_print_error(err);
		
		printf("\n");
	}
	if (line != NULL) {
		free(line);
		line = NULL;
	}
}

#endif // console_ui_h_INCLUDED

