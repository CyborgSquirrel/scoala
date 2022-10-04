#include "./vec.h"
#include "./domain.h"

const char *const ERR_INVALID_INDEX = "indicele este invalid";

struct Vec vec_new(void) {
	struct Vec vec;
	vec.size = 4;
	vec.len = 0;
	vec.buf = (struct Cheltuiala*) malloc(vec.size * sizeof(struct Cheltuiala));
	return vec;
}

void vec_drop(struct Vec *vec) {
	assert(vec && vec->buf);
	free(vec->buf);
	vec->buf = NULL;
}

const char *const vec_get(
	struct Vec *vec,
	struct Cheltuiala *cheltuiala,
	int index
) {
	assert(vec && vec->buf);
	if (index < 0 || index >= vec->len) return ERR_INVALID_INDEX;
	*cheltuiala = vec->buf[index];
	return NULL;
}

void vec_push(
	struct Vec *vec,
	struct Cheltuiala cheltuiala
) {
	assert(vec && vec->buf && vec->len <= vec->size);
	if (vec->len == vec->size) {
		struct Cheltuiala *old_buf = vec->buf;
		int old_size = vec->size;
		
		vec->size *= 2;
		vec->buf = (struct Cheltuiala*) malloc(vec->size * sizeof(struct Cheltuiala));
		for (int i = 0; i < old_size; ++i) {
			vec->buf[i] = old_buf[i];
		}
		
		free(old_buf);
	}
	vec->buf[vec->len] = cheltuiala;
	vec->len++;
}

const char *const vec_set(
	struct Vec *vec,
	int index,
	struct Cheltuiala cheltuiala
) {
	assert(vec && vec->buf);
	if (index < 0 || index >= vec->len) return ERR_INVALID_INDEX;
	vec->buf[index] = cheltuiala;
	return NULL;
}

const char *const vec_erase(
	struct Vec *vec,
	int index
) {
	assert(vec && vec->buf);
	if (index < 0 || index >= vec->len) return ERR_INVALID_INDEX;
	for (int i = index+1; i < vec->len; ++i) {
		vec->buf[i-1] = vec->buf[i];
	}
	vec->len--;
	return NULL;
}

/*
 *   TESTS
 */

void test_vec_push(void) {
	struct Vec vec = vec_new();
	struct Cheltuiala cheltuiala = 
		cheltuiala_new(
			0,
			data_new(23, 11, 2007),
			31.415, MANCARE
		);
	
	for (int i = 0; i < 100; ++i) {
		vec_push(&vec, cheltuiala);
	}
	
	vec_drop(&vec);
}

void test_vec_get(void) {
	struct Vec vec = vec_new();
	struct Cheltuiala cheltuiala = 
		cheltuiala_new(
			0,
			data_new(26, 7, 1999),
			3.50, TELEFON_INTERNET
		);
	
	for (int i = 0; i < 100; ++i) {
		vec_push(&vec, cheltuiala);
	}
	for (int i = 0; i < 100; ++i) {
		struct Cheltuiala get_cheltuiala;
		assert(vec_get(&vec, &get_cheltuiala, i) == NULL);
		assert(cheltuiala_eq(&get_cheltuiala, &cheltuiala));
	}
	for (int i = 0; i < 10; ++i) {
		struct Cheltuiala get_cheltuiala;
		assert(vec_get(&vec, &get_cheltuiala, i+100) == ERR_INVALID_INDEX);
	}
	
	vec_drop(&vec);
}

void test_vec_set(void) {
	struct Vec vec = vec_new();
	struct Cheltuiala cheltuiala_1 = 
		cheltuiala_new(
			0,
			data_new(23, 11, 2007),
			31.415, ALTELE
		);
	struct Cheltuiala cheltuiala_2 = 
		cheltuiala_new(
			0,
			data_new(23, 11, 2007),
			99.999, ALTELE
		);
	
	vec_push(&vec, cheltuiala_1);
	assert(vec_set(&vec, 0, cheltuiala_2) == NULL);
	struct Cheltuiala get_cheltuiala;
	assert(vec_get(&vec, &get_cheltuiala, 0) == NULL);
	assert(cheltuiala_eq(&get_cheltuiala, &cheltuiala_2));
	
	assert(vec_set(&vec, 1, cheltuiala_2) == ERR_INVALID_INDEX);
	
	vec_drop(&vec);
}

void test_vec_erase(void) {
	struct Vec vec = vec_new();
	
	struct Cheltuiala cheltuiala = 
		cheltuiala_new(
			0,
			data_new(26, 7, 1999),
			3.50, TELEFON_INTERNET
		);
	
	for (int i = 0; i < 50; ++i) {
		vec_push(&vec, cheltuiala);
	}
	vec_erase(&vec, 5);
	vec_erase(&vec, 5);
	vec_erase(&vec, 5);
	vec_erase(&vec, 41);
	assert(vec_erase(&vec, 50) == ERR_INVALID_INDEX);
	for (int i = 0; i < 46; ++i) {
		vec_erase(&vec, 0);
	}
	assert(vec.len == 0);
	
	vec_drop(&vec);
}

void test_vec_clone(void) {}
void test_vec_sort(void) {}

void test_vec(void) {
	test_vec_push();
	test_vec_get();
	test_vec_set();
	test_vec_erase();
	test_vec_clone();
	test_vec_sort();
}
