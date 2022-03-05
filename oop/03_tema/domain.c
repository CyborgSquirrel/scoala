#include "domain.h"

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
