#ifndef console_ui_h_INCLUDED
#define console_ui_h_INCLUDED

#include <assert.h>

#include "./domain.h"
#include "./srv.h"
#include "./valid.h"

struct ConsoleUi {
	int running;
	char *line;
	long unsigned int len;
	struct SrvCheltuieli srv_cheltuieli;
};

struct ConsoleUi console_ui_new(struct SrvCheltuieli srv_cheltuieli) {
	struct ConsoleUi console_ui;
	console_ui.running = 1;
	console_ui.line = NULL;
	console_ui.len = 0;
	console_ui.srv_cheltuieli = srv_cheltuieli;
	return console_ui;
}

void console_ui_drop(struct ConsoleUi *console_ui) {
	srv_cheltuieli_drop(&console_ui->srv_cheltuieli);
}

const char *const ERR_INVALID_COMMAND_INDEX = "comanda invalida";
const char *const ERR_INVALID_DATA = "data invalida";
const char *const ERR_INVALID_SUMA = "suma invalida";
const char *const ERR_INVALID_TIP = "tip invalid";
const char *const ERR_INVALID_ID = "id invalid";
const char *const ERR_INVALID_SORTING_FUNC_INDEX = "criteriu de ordonare invalid";
const char *const ERR_INVALID_FILTERING_FUNC_INDEX = "criteriu de filtrare invalid";

void console_ui_get_line(struct ConsoleUi *console_ui) {
	getline(&console_ui->line, &console_ui->len, stdin);
}

void console_ui_pause(struct ConsoleUi *console_ui) {
	printf("Apasati enter ca sa continuati...");
	console_ui_get_line(console_ui);
}

const char *const console_ui_read_choice(struct ConsoleUi *console_ui, int *choice, int choices, const char *const err) {
	printf("> ");
	console_ui_get_line(console_ui);
	if (sscanf(console_ui->line, "%d", choice) != 1) return err;
	(*choice)--;
	if (*choice < 0 || *choice >= choices) return err;
	return NULL;
}

const char *const console_ui_read_data(struct ConsoleUi *console_ui, struct Data *data) {
	printf("data (dd/mm/yyyy) = ");
	console_ui_get_line(console_ui);
	if (sscanf(console_ui->line, "%d/%d/%d", &data->zi, &data->luna, &data->an) != 3) return ERR_INVALID_DATA;
	if (!validate_data(data)) return ERR_INVALID_DATA;
	return NULL;
}

const char *const console_ui_read_suma(struct ConsoleUi *console_ui, float *suma) {
	printf("suma = ");
	console_ui_get_line(console_ui);
	if (sscanf(console_ui->line, "%f", suma) != 1) return ERR_INVALID_SUMA;
	if (!validate_suma(*suma)) return ERR_INVALID_SUMA;
	return NULL;
}

const char *const console_ui_read_tip(struct ConsoleUi *console_ui, enum Tip *tip) {
	printf("tip (mancare/transport/telefon&internet/imbracaminte/altele) = ");
	console_ui_get_line(console_ui);
	
	for (char *p = console_ui->line; *p != '\0'; ++p) *p = tolower(*p);
	
	     if (strncmp(console_ui->line, "mancare"         , 7 ) == 0) *tip = MANCARE;
	else if (strncmp(console_ui->line, "transport"       , 9 ) == 0) *tip = TRANSPORT;
	else if (strncmp(console_ui->line, "telefon&internet", 16) == 0) *tip = TELEFON_INTERNET;
	else if (strncmp(console_ui->line, "imbracaminte"    , 12) == 0) *tip = IMBRACAMINTE;
	else if (strncmp(console_ui->line, "altele"          , 6 ) == 0) *tip = ALTELE;
	else return ERR_INVALID_TIP;
	
	return NULL;
}

const char *const console_ui_read_id(struct ConsoleUi *console_ui, int *id) {
	printf("id = ");
	console_ui_get_line(console_ui);
	if (sscanf(console_ui->line, "%d", id) != 1) return ERR_INVALID_ID;
	return NULL;
}

void print_vec(struct Vec *vec) {
	for (int i = 0; i < vec->len; ++i) {
		struct Cheltuiala cheltuiala;
		assert(vec_get(vec, &cheltuiala, i) == NULL);
		cheltuiala_print(stdout, &cheltuiala);
		printf("\n");
	}
}

const char *const console_ui_print_cheltuieli(struct ConsoleUi *console_ui) {
	struct Vec vec = srv_cheltuieli_get_all(&console_ui->srv_cheltuieli);
	print_vec(&vec);
	vec_drop(&vec);
	
	return NULL;
}

int cmp_ascending_suma(void *lhs, void *rhs)
	{ return ((struct Cheltuiala *) lhs)->suma < ((struct Cheltuiala *) rhs)->suma; }
int cmp_descending_suma(void *lhs, void *rhs)
	{ return ((struct Cheltuiala *) lhs)->suma > ((struct Cheltuiala *) rhs)->suma; }
int cmp_ascending_tip(void *lhs, void *rhs)
	{ return ((struct Cheltuiala *) lhs)->tip < ((struct Cheltuiala *) rhs)->tip; }
int cmp_descending_tip(void *lhs, void *rhs)
	{ return ((struct Cheltuiala *) lhs)->tip > ((struct Cheltuiala *) rhs)->tip; }

#define SORTING_FUNCS 4
int (*sorting_funcs[SORTING_FUNCS])(void *, void *) = {
	cmp_descending_suma, cmp_ascending_suma,
	cmp_descending_tip, cmp_ascending_tip
};
const char *const sorting_func_names[SORTING_FUNCS] = {
	"descrescator dupa suma", "crescator dupa suma",
	"descrescator dupa tip", "crescator dupa tip"
};

const char *const console_ui_print_sorted_cheltuieli(struct ConsoleUi *console_ui) {
	const char *err = NULL;
	
	printf("Alegeti criteriul de ordonare.\n");
	for (int i = 0; i < SORTING_FUNCS; ++i) {
		printf("%d. %s\n", i+1, sorting_func_names[i]);
	}
	
	int sorting_func_index;
	if ((err = console_ui_read_choice(console_ui, &sorting_func_index, SORTING_FUNCS, ERR_INVALID_SORTING_FUNC_INDEX)) != NULL) return err;
	
	struct Vec vec = srv_cheltuieli_get_all(&console_ui->srv_cheltuieli);
	vec_sort(&vec, sorting_funcs[sorting_func_index]);
	print_vec(&vec);
	vec_drop(&vec);
	
	return NULL;
}

int filter_suma_eq(struct Cheltuiala *val, struct Cheltuiala *filter)
	{ return (val->suma - filter->suma) <= 0.001; }
int filter_suma_lt(struct Cheltuiala *val, struct Cheltuiala *filter)
	{ return val->suma < filter->suma; }
int filter_suma_gt(struct Cheltuiala *val, struct Cheltuiala *filter)
	{ return val->suma > filter->suma; }
int filter_data_eq(struct Cheltuiala *val, struct Cheltuiala *filter)
	{ return data_eq(&val->data, &filter->data); }
int filter_data_before(struct Cheltuiala *val, struct Cheltuiala *filter)
	{ return data_before(&val->data, &filter->data); }
int filter_data_after(struct Cheltuiala *val, struct Cheltuiala *filter)
	{ return data_after(&val->data, &filter->data); }
int filter_tip_eq(struct Cheltuiala *val, struct Cheltuiala *filter)
	{ return val->tip == filter->tip; }
#define FILTERING_FUNCS 7
int (*filtering_funcs[FILTERING_FUNCS])(struct Cheltuiala *, struct Cheltuiala *) = {
	filter_suma_eq, filter_suma_lt, filter_suma_gt,
	filter_data_eq, filter_data_before, filter_data_after,
	filter_tip_eq
};
const char *const filtering_func_names[FILTERING_FUNCS] = {
	"dupa suma egala", "dupa suma mai mica", "dupa suma mai mare",
	"cheltuieli efectuate pe o data", "cheltuieli efectuate inainte de o data", "cheltuieli efectuate dupa o data",
	"dupa tip"
};

const char *const console_ui_print_filtered_cheltuieli(struct ConsoleUi *console_ui) {
	const char *err = NULL;
	
	printf("Alegeti criteriul de filtrare.\n");
	for (int i = 0; i < FILTERING_FUNCS; ++i) {
		printf("%d. %s\n", i+1, filtering_func_names[i]);
	}
	
	int filtering_func_index;
	if ((err = console_ui_read_choice(console_ui, &filtering_func_index, FILTERING_FUNCS, ERR_INVALID_FILTERING_FUNC_INDEX)) != NULL) return err;
	
	struct Cheltuiala filter;
	if        (filtering_func_index >= 0 && filtering_func_index <= 2) {
		if ((err = console_ui_read_suma(console_ui, &filter.suma)) != NULL) return err;
	} else if (filtering_func_index >= 3 && filtering_func_index <= 5) {
		if ((err = console_ui_read_data(console_ui, &filter.data)) != NULL) return err;
	} else if (filtering_func_index >= 6 && filtering_func_index <= 6) {
		if ((err = console_ui_read_tip(console_ui, &filter.tip)) != NULL) return err;
	}
	
	struct Vec vec = srv_cheltuieli_get_all(&console_ui->srv_cheltuieli);
	int (*func) (struct Cheltuiala *, struct Cheltuiala *) = filtering_funcs[filtering_func_index];
	for (int i = 0; i < vec.len; ++i) {
		struct Cheltuiala cheltuiala;
		assert(vec_get(&vec, &cheltuiala, i) == NULL);
		if (func(&cheltuiala, &filter)) {
			cheltuiala_print(stdout, &cheltuiala);
			printf("\n");
		}
	}
	vec_drop(&vec);
	
	return NULL;
}

const char *const console_ui_add_cheltuiala(struct ConsoleUi *console_ui) {
	const char *err = NULL;
	
	struct Data data;
	float suma;
	enum Tip tip;
	
	if ((err = console_ui_read_data(console_ui, &data)) != NULL) return err;
	if ((err = console_ui_read_suma (console_ui, &suma)) != NULL) return err;
	if ((err = console_ui_read_tip(console_ui, &tip)) != NULL) return err;
	
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
	
	if ((err = console_ui_read_id(console_ui, &id)) != NULL) return err;
	if ((err = console_ui_read_data(console_ui, &data)) != NULL) return err;
	if ((err = console_ui_read_suma (console_ui, &suma)) != NULL) return err;
	if ((err = console_ui_read_tip(console_ui, &tip)) != NULL) return err;
	
	return srv_cheltuieli_update(
		&console_ui->srv_cheltuieli,
		id, data, suma, tip
	);
}

const char *const console_ui_erase_cheltuiala(struct ConsoleUi *console_ui) {
	const char *err = NULL;
	
	int id;
	if ((err = console_ui_read_id(console_ui, &id)) != NULL) return err;
	
	return srv_cheltuieli_erase(
		&console_ui->srv_cheltuieli,
		id
	);
}

const char *const console_ui_exit(struct ConsoleUi *console_ui) {
	console_ui->running = 0;
	return NULL;
}

#define COMMANDS 7
const char *const (*console_ui_commands[COMMANDS]) (struct ConsoleUi*) = {
	console_ui_print_cheltuieli,
	console_ui_print_sorted_cheltuieli,
	console_ui_print_filtered_cheltuieli,
	console_ui_add_cheltuiala,
	console_ui_update_cheltuiala,
	console_ui_erase_cheltuiala,
	console_ui_exit
};
char *console_ui_command_names[COMMANDS] = {
	"Afiseaza toate cheltuielile",
	"Afiseaza cheltuieli ordonate",
	"Afiseaza cheltuieli filtrate",
	"Adauga cheltuiala",
	"Modifica cheltuiala",
	"Sterge cheltuiala",
	"Exit"
};

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
		
		int choice;
		if ((err = console_ui_read_choice(console_ui, &choice, COMMANDS, ERR_INVALID_COMMAND_INDEX)) == NULL) {
			err = console_ui_commands[choice](console_ui);
		}
		
		if (err != NULL) console_ui_print_error(err);
		console_ui_pause(console_ui);
		printf("\n");
	}
	if (console_ui->line != NULL) {
		free(console_ui->line);
		console_ui->line = NULL;
	}
}

#endif // console_ui_h_INCLUDED

