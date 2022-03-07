#include <assert.h>
#include <string.h>
#include "./domain.h"

char *tip_as_str(enum Tip tip) {
	switch (tip) {
		case MANCARE          : return "mancare";
		case TRANSPORT        : return "transport";
		case TELEFON_INTERNET : return "telefon&internet";
		case IMBRACAMINTE     : return "imbracaminte";
		case ALTELE           : return "altele";
		default : exit(1);
	}
}

struct Data data_new(int zi, int luna, int an) {
	struct Data data;
	data.zi = zi;
	data.luna = luna;
	data.an = an;
	return data;
}

int data_eq(struct Data *lhs, struct Data *rhs) {
	return lhs->zi == rhs->zi
		&& lhs->luna == rhs->luna
		&& lhs->an == rhs->an;
}

void data_print(struct Data *data) {
	printf("%d/%d/%d", data->zi, data->luna, data->an);
}

struct Cheltuiala cheltuiala_new(
	int id, struct Data data, float suma, enum Tip tip
) {
	struct Cheltuiala cheltuiala;
	cheltuiala.id = id;
	cheltuiala.data = data;
	cheltuiala.suma = suma;
	cheltuiala.tip = tip;
	return cheltuiala;
}

int cheltuiala_eq(struct Cheltuiala *lhs, struct Cheltuiala *rhs) {
	return data_eq(&lhs->data, &rhs->data)
		&& lhs->suma == rhs->suma
		&& lhs->tip == rhs->tip;
}

void cheltuiala_print(struct Cheltuiala *cheltuiala) {
	printf("#%d ", cheltuiala->id);
	data_print(&cheltuiala->data);
	printf(" %f lei (%s)", cheltuiala->suma, tip_as_str(cheltuiala->tip));
}

void test_tip_as_str() {
	assert(strcmp(tip_as_str(MANCARE), "mancare") == 0);
	assert(strcmp(tip_as_str(TRANSPORT), "transport") == 0);
	assert(strcmp(tip_as_str(TELEFON_INTERNET), "telefon&internet") == 0);
	assert(strcmp(tip_as_str(IMBRACAMINTE), "imbracaminte") == 0);
	assert(strcmp(tip_as_str(ALTELE), "altele") == 0);
}
void test_data_eq() {
	struct Data data_1 = data_new(12, 7, 2003);
	struct Data data_2 = data_new(11, 7, 2003);
	assert(data_eq(&data_1, &data_1));
	assert(!data_eq(&data_1, &data_2));
}
void test_cheltuiala_eq() {
	struct Cheltuiala cheltuiala_1 = cheltuiala_new(0, data_new(12, 7, 2003), 12.12, MANCARE);
	struct Cheltuiala cheltuiala_2 = cheltuiala_new(0, data_new(12, 7, 2003), 12.12, TRANSPORT);
	assert(cheltuiala_eq(&cheltuiala_1, &cheltuiala_1));
	assert(!cheltuiala_eq(&cheltuiala_1, &cheltuiala_2));
}

void test_domain() {
	test_tip_as_str();
	test_data_eq();
	test_cheltuiala_eq();
}
