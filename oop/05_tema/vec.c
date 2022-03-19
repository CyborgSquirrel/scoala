#include "./vec.h"

#include <string.h>
#include <stdlib.h>

const char *const ERR_INVALID_INDEX = "indicele este invalid";

struct Vec vec_new(
	int element_size,
	void (*element_clone)(void *, void *),
	void (*element_drop)(void *)
) {
	struct Vec vec;
	vec.allocated_len = 4;
	vec.len = 0;
	vec.element_size = element_size;
	vec.element_clone = element_clone;
	vec.element_drop = element_drop;
	vec.buf = malloc(vec.allocated_len * vec.element_size);
	assert(vec.buf);
	return vec;
}

void vec_drop(struct Vec *vec) {
	assert(vec && vec->buf);
	int elements_size = vec->len * vec->element_size;
	for (int i = 0; i < elements_size; i += vec->element_size) {
		vec->element_drop(vec->buf + i);
	}
	free(vec->buf);
	vec->buf = NULL;
}

void vec_drop_generic(void *vec) {
	vec_drop((struct Vec *) vec);
}

const char *const vec_get(
	struct Vec *vec,
	void *value,
	int index
) {
	assert(vec && vec->buf);
	if (index < 0 || index >= vec->len) return ERR_INVALID_INDEX;
	vec->element_clone(value, vec->buf + index * vec->element_size);
	return NULL;
}

void vec_push(
	struct Vec *vec,
	void *value
) {
	assert(vec && vec->buf && vec->len <= vec->allocated_len);
	if (vec->len == vec->allocated_len) {
		vec->allocated_len *= 2;
		vec->buf = realloc(vec->buf, vec->allocated_len * vec->element_size);
		assert(vec->buf);
	}
	vec->element_clone(vec->buf + vec->len * vec->element_size, value);
	vec->len++;
}

const char *const vec_set(
	struct Vec *vec,
	int index,
	void *value
) {
	assert(vec && vec->buf);
	if (index < 0 || index >= vec->len) return ERR_INVALID_INDEX;
	vec->element_drop(vec->buf + index * vec->element_size);
	vec->element_clone(vec->buf + index * vec->element_size, value);
	return NULL;
}

const char *const vec_erase(
	struct Vec *vec,
	int index
) {
	assert(vec && vec->buf);
	if (index < 0 || index >= vec->len) return ERR_INVALID_INDEX;
	vec->element_drop(vec->buf + index * vec->element_size);
	int elements_size = vec->len * vec->element_size;
	char *buf = (char *) vec->buf;
	for (int i = (index+1) * vec->element_size; i < elements_size; ++i) {
		buf[i-vec->element_size] = buf[i];
	}
	vec->len--;
	return NULL;
}

void vec_clone(
	struct Vec *dest,
	struct Vec *src
) {
	dest->allocated_len = src->allocated_len;
	dest->len = src->len;
	dest->element_size = src->element_size;
	dest->element_clone = src->element_clone;
	dest->element_drop = src->element_drop;
	dest->buf = malloc(dest->allocated_len * src->element_size);
	assert(dest->buf);
	
	int elements_size = src->len * src->element_size;
	for (int i = 0; i < elements_size; i += src->element_size) {
		src->element_clone(dest->buf + i, src->buf + i);
	}
}

void vec_clone_generic(void *dest, void *src) {
	vec_clone((struct Vec *) dest, (struct Vec *) src);
}


void __buf_mergesort(
	int element_size,
	void *buf,
	void *temp_buf,
	int (*lt)(void *, void *),
	int len
) {
	if (len <= 1) return;
	
	int mid = len / 2;
	int mid_offset = mid*element_size;
	__buf_mergesort(element_size, temp_buf           , buf           , lt, mid    );
	__buf_mergesort(element_size, temp_buf+mid_offset, buf+mid_offset, lt, len-mid);
	int i = 0, j = mid_offset;
	int len_offset = len*element_size;
	for (int k = 0; k < len_offset; k += element_size) {
		if (j >= len_offset) {
			memcpy(buf+k, temp_buf+i, element_size); i += element_size;
		} else if (i >= mid_offset) {
			memcpy(buf+k, temp_buf+j, element_size); j += element_size;
		} else {
			int lt_ij = lt(temp_buf+i, temp_buf+j);
			if (lt_ij) {
				memcpy(buf+k, temp_buf+i, element_size); i += element_size;
			} else {
				memcpy(buf+k, temp_buf+j, element_size); j += element_size;
			}
		}
	}
}

void vec_sort(
	struct Vec *vec,
	int (*lt)(void *, void *)
) {
	void *temp_buf = malloc(vec->len * vec->element_size);
	assert(temp_buf);
	memcpy(temp_buf, vec->buf, vec->len * vec->element_size);
	
	__buf_mergesort(vec->element_size, vec->buf, temp_buf, lt, vec->len);
	
	free(temp_buf);
}

/*
 *   TESTS
 */

#include "./domain.h"

void test_vec_cheltuiala_push(void) {
	struct Vec vec = vec_new(
		sizeof(struct Cheltuiala),
		cheltuiala_clone_generic,
		cheltuiala_drop_generic
	);
	struct Cheltuiala cheltuiala = 
		cheltuiala_new(
			0,
			data_new(23, 11, 2007),
			31.415, MANCARE
		);
	
	for (int i = 0; i < 100; ++i) {
		vec_push(&vec, (void *) &cheltuiala);
	}
	
	vec_drop(&vec);
}

void test_vec_cheltuiala_get(void) {
	struct Vec vec = vec_new(
		sizeof(struct Cheltuiala),
		cheltuiala_clone_generic,
		cheltuiala_drop_generic
	);
	struct Cheltuiala cheltuiala = 
		cheltuiala_new(
			0,
			data_new(26, 7, 1999),
			3.50, TELEFON_INTERNET
		);
	
	for (int i = 0; i < 100; ++i) {
		vec_push(&vec, (void *) &cheltuiala);
	}
	for (int i = 0; i < 100; ++i) {
		struct Cheltuiala get_cheltuiala;
		assert(vec_get(&vec, (void *) &get_cheltuiala, i) == NULL);
		assert(cheltuiala_eq(&get_cheltuiala, &cheltuiala));
	}
	for (int i = 0; i < 10; ++i) {
		struct Cheltuiala get_cheltuiala;
		assert(vec_get(&vec, (void *) &get_cheltuiala, i+100) == ERR_INVALID_INDEX);
	}
	
	vec_drop(&vec);
}

void test_vec_cheltuiala_set(void) {
	struct Vec vec = vec_new(
		sizeof(struct Cheltuiala),
		cheltuiala_clone_generic,
		cheltuiala_drop_generic
	);
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
	
	vec_push(&vec, (void *) &cheltuiala_1);
	assert(vec_set(&vec, 0, (void *) &cheltuiala_2) == NULL);
	struct Cheltuiala get_cheltuiala;
	assert(vec_get(&vec, (void *) &get_cheltuiala, 0) == NULL);
	assert(cheltuiala_eq(&get_cheltuiala, &cheltuiala_2));
	
	assert(vec_set(&vec, 1, (void *) &cheltuiala_2) == ERR_INVALID_INDEX);
	
	vec_drop(&vec);
}

void test_vec_cheltuiala_erase(void) {
	struct Vec vec = vec_new(
		sizeof(struct Cheltuiala),
		cheltuiala_clone_generic,
		cheltuiala_drop_generic
	);
	
	struct Cheltuiala cheltuiala = 
		cheltuiala_new(
			0,
			data_new(26, 7, 1999),
			3.50, TELEFON_INTERNET
		);
	
	for (int i = 0; i < 50; ++i) {
		vec_push(&vec, (void *) &cheltuiala);
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

void test_vec_cheltuiala_clone(void) {
	struct Vec vec = vec_new(
		sizeof(struct Cheltuiala),
		cheltuiala_clone_generic,
		cheltuiala_drop_generic
	);
	
	struct Cheltuiala cheltuiala = 
		cheltuiala_new(
			0,
			data_new(26, 7, 1999),
			3.50, TELEFON_INTERNET
		);
	
	for (int i = 0; i < 50; ++i) {
		vec_push(&vec, (void *) &cheltuiala);
	}
	
	struct Vec clone;
	vec_clone(&clone, &vec);
	
	for (int i = 0; i < 50; ++i) {
		struct Cheltuiala get_cheltuiala;
		vec_get(&clone, (void *) &get_cheltuiala, i);
		assert(cheltuiala_eq(&get_cheltuiala, &cheltuiala));
	}
	
	vec_drop(&clone);
	vec_drop(&vec);
}

int lt_suma(void *lhs, void *rhs) {
	return ((struct Cheltuiala *) lhs)->suma < ((struct Cheltuiala *) rhs)->suma;
}

void test_vec_cheltuiala_sort(void) {
	struct Vec vec = vec_new(
		sizeof(struct Cheltuiala),
		cheltuiala_clone_generic,
		cheltuiala_drop_generic
	);
	
	struct Cheltuiala cheltuiala = 
		cheltuiala_new(
			0,
			data_new(26, 7, 1999),
			0, TELEFON_INTERNET
		);
	
	float sume[] = { 1.5, 12.12, 14, 41.41, 700, 1337 };
	
	cheltuiala.suma = sume[3]; vec_push(&vec, (void *) &cheltuiala);
	cheltuiala.suma = sume[1]; vec_push(&vec, (void *) &cheltuiala);
	cheltuiala.suma = sume[2]; vec_push(&vec, (void *) &cheltuiala);
	cheltuiala.suma = sume[5]; vec_push(&vec, (void *) &cheltuiala);
	cheltuiala.suma = sume[0]; vec_push(&vec, (void *) &cheltuiala);
	cheltuiala.suma = sume[4]; vec_push(&vec, (void *) &cheltuiala);
	
	vec_sort(&vec, lt_suma);
	for (int i = 0; i < vec.len; ++i) {
		struct Cheltuiala get_cheltuiala;
		vec_get(&vec, (void *) &get_cheltuiala, i);
		assert(get_cheltuiala.suma == sume[i]);
	}
	
	vec_drop(&vec);
}

void test_vec_vec_cheltuiala() {
	struct Cheltuiala cheltuiala = 
		cheltuiala_new(
			0,
			data_new(26, 7, 1999),
			3.50, TELEFON_INTERNET
		);
	
	struct Vec vec = vec_new(
		sizeof(struct Cheltuiala),
		cheltuiala_clone_generic,
		cheltuiala_drop_generic
	);
	
	struct Vec vec_vec = vec_new(
		sizeof(struct Vec),
		vec_clone_generic,
		vec_drop_generic
	);
	
	for (int i = 0; i < 100; ++i) {
		vec_push(&vec, (void *) &cheltuiala);
		if (i % 10 == 0) {
			vec_push(&vec_vec, (void *) &vec);
		}
	}
	
	assert(vec_set(&vec_vec, 4, (void *) &vec) == NULL);
	assert(vec_set(&vec_vec, 17, (void *) &vec) == ERR_INVALID_INDEX);
	
	assert(vec_erase(&vec_vec, 2) == NULL);
	assert(vec_erase(&vec_vec, 17) == ERR_INVALID_INDEX);
	
	struct Vec vec_vec_clone;
	vec_clone(&vec_vec_clone, &vec_vec);
	for (int i = 0; i < vec_vec_clone.len; ++i) {
		struct Vec vec_clone;
		vec_get(&vec_vec_clone, (void *) &vec_clone, i);
		for (int j = 0; j < vec_clone.len; ++j) {
			struct Cheltuiala cheltuiala, cheltuiala_clone;
			assert(vec_get(&vec      , (void *) &cheltuiala      , j) == NULL);
			assert(vec_get(&vec_clone, (void *) &cheltuiala_clone, j) == NULL);
			assert(cheltuiala_eq(&cheltuiala, &cheltuiala_clone));
		}
		vec_drop(&vec_clone);
	}
	vec_drop(&vec_vec_clone);
	
	vec_drop(&vec_vec);
	vec_drop(&vec);
}

void test_vec(void) {
	test_vec_cheltuiala_push();
	test_vec_cheltuiala_get();
	test_vec_cheltuiala_set();
	test_vec_cheltuiala_erase();
	test_vec_cheltuiala_clone();
	test_vec_cheltuiala_sort();
	
	test_vec_vec_cheltuiala();
}
