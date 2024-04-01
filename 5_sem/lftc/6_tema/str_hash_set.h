#ifndef __STR_HASH_SET_H
#define __STR_HASH_SET_H

#include "common.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define StrHashSet_Size 1024

typedef struct {
	int last_id;
	char *values[StrHashSet_Size];
} StrHashSet;

StrHashSet *StrHashSet_New();
void StrHashSet_Drop(StrHashSet *hash_set);

void StrHashSet_Add(
	StrHashSet *hash_set,
	char *value,
	int *index
);
void StrHashSet_Find(
	StrHashSet *hash_set,
	char *value,
	int *id,     // output
	char *found  // output
);

#endif
