#include "./vec.h"

#include <string.h>
#include <stdlib.h>

Vec* create_empty(
	int element_size,
	CopyFn element_copy,
	DestroyFn element_destroy
) {
	Vec* vec = malloc(sizeof(Vec));
	if (vec != NULL) {
		vec->cp = 10;
		vec->lg = 0;
		vec->element_size = element_size;
		vec->element_copy = element_copy;
		vec->element_destroy = element_destroy;
		vec->elems = malloc(vec->cp * vec->element_size);
	}
	return vec;
}

void destroy_vec(Vec* vec) {
	int elements_size = vec->lg * vec->element_size;
	for (int i = 0; i < elements_size; i += vec->element_size) {
		vec->element_destroy(vec->elems + i);
	}
	free(vec->elems);
	free(vec);
}

int vec_get(
	Vec* vec,
	ElemType value,
	int index
) {
	if (index < 0 || index >= vec->lg) return -3;
	memcpy(value, vec->elems + index * vec->element_size, vec->element_size);
	return 0;
}

void vec_push(
	Vec* vec,
	ElemType value
) {
	if (vec->lg == vec->cp) {
		vec->cp *= 2;
		vec->elems = realloc(vec->elems, vec->cp * vec->element_size);
	}
	memcpy(vec->elems + vec->lg * vec->element_size, &value, vec->element_size);
	vec->lg++;
}

int vec_set(
	Vec* vec,
	int index,
	ElemType value
) {
	if (index < 0 || index >= vec->lg) return -4;
	vec->element_destroy(vec->elems + index * vec->element_size);
	memcpy(vec->elems + index * vec->element_size, &value, vec->element_size);
	return 0;
}

int vec_erase(
	Vec* vec,
	int index
) {
	if (index < 0 || index >= vec->lg) return -5;
	vec->element_destroy(vec->elems + index * vec->element_size);
	int elements_size = vec->lg * vec->element_size;
	char* buf = (char*) vec->elems;
	for (int i = (index+1) * vec->element_size; i < elements_size; ++i) {
		buf[i-vec->element_size] = buf[i];
	}
	vec->lg--;
	return 0;
}

int vec_pop(
	Vec* vec,
	ElemType value
) {
	if (vec->lg < 1) return -5;
	memcpy(value, vec->elems + (vec->lg-1) * vec->element_size, vec->element_size);
	vec->lg--;
	return 0;
}

Vec* copy_vec(
	Vec *vec
) {
	Vec* vec_copy = malloc(sizeof(Vec));
	vec_copy->cp = vec->cp;
	vec_copy->lg = vec->lg;
	vec_copy->element_size = vec->element_size;
	vec_copy->element_copy = vec->element_copy;
	vec_copy->element_destroy = vec->element_destroy;
	vec_copy->elems = malloc(vec_copy->cp * vec->element_size);
	
	int elements_size = vec->lg * vec->element_size;
	for (int i = 0; i < elements_size; i += vec->element_size) {
		ElemType copy = vec->element_copy(vec->elems + i);
		memcpy(vec_copy->elems + i, &copy, vec->element_size);
	}
	return vec_copy;
}

