#include "str_hash_set.h"
#include <stdio.h>
#include <stdlib.h>

StrHashSet *StrHashSet_New() {
	StrHashSet *hash_set = (StrHashSet *) malloc(sizeof(StrHashSet));
	for (int i = 0; i < StrHashSet_Size; ++i) {
		hash_set->values[i] = NULL;
	}
	return hash_set;
}

void StrHashSet_Drop(StrHashSet *hash_set) {
	for (int i = 0; i < StrHashSet_Size; ++i) {
		if (hash_set->values[i] != NULL) {
			free(hash_set->values[i]);
		}
	}
  free(hash_set);
}

void StrHashSet_Add(
	StrHashSet *hash_set,
	char *value,
	int *index
) {
	int hash = Common_Hash(value) % StrHashSet_Size;
	int j = hash;
	for (int i = 0; i < StrHashSet_Size; ++i) {
    char found_slot = 0;
		if (hash_set->values[j] == NULL) {
			// found empty slot
			int value_len = strlen(value);
			char *value_copy = malloc(sizeof(char) * (value_len+1));
			strcpy(value_copy, value);
			value_copy[value_len] = '\0';
			hash_set->values[j] = value_copy;

      found_slot = 1;
		} else if(strcmp(hash_set->values[j], value) == 0) {
			// slot has same key
			
      found_slot = 1;
		}

    if (found_slot) {
			if (index != NULL) {
	      *index = j;
			}
			return;
    }
		// gotta keep on lookin...
		
		j++;
		if (j >= StrHashSet_Size) {
			j = 0;
		}
	}
	
	// oh no its full
	assert(0);
}

void StrHashSet_Find(
	StrHashSet *hash_set,
	char *value,
	int *id,     // output
	char *found  // output
) {
	*found = 0;
	
	int hash = Common_Hash(value) % StrHashSet_Size;
	int j = hash;
	for (int i = 0; i < StrHashSet_Size; ++i) {
		if (hash_set->values[j] != NULL) {
			if (strcmp(hash_set->values[j], value) == 0) {
				*found = 1;
        if (id != NULL) {
          *id = j;
        }
				return;
			}
		} else {
			return;
		}
		// gotta keep on lookin...
		
		j++;
		if (j >= StrHashSet_Size) {
			j = 0;
		}
	}
}
