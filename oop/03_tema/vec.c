#include "./vec.h"

struct Vec vec_new(void) {
	struct Vec vec;
	vec.size = 4;
	vec.len = 0;
	vec.buf = (struct Cheltuiala*) malloc(vec.size * sizeof(struct Cheltuiala));
	return vec;
}
