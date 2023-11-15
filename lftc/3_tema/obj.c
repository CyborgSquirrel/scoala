#ifndef __OBJ_C
#define __OBJ_C

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

const size_t OBJ_DICT_BINS_NO = 64;
const size_t OBJ_LIST_STARTING_SIZE = 8;

enum ObjKind {
	OBJ_NULL = 0,
  OBJ_INT,
	OBJ_STR,
	OBJ_BYTES,
	OBJ_LIST,
  OBJ_DICT,
};

struct Obj;

struct ObjInt {
  int64_t value;
};

struct ObjStr {
  char *buf;
  size_t len;
};

struct ObjBytes {
  void *buf;
  size_t len;
};

struct ObjList {
	struct Obj **objs;
	size_t size;
	size_t len;
};

struct ObjDict {
  struct Obj **bins;
};

union ObjUnion {
	struct ObjInt int_;
	struct ObjStr str;
	struct ObjBytes bytes;
	struct ObjList list;
  struct ObjDict dict;
};

struct Obj {
	size_t count;
	enum ObjKind kind;
	union ObjUnion inner;
};

// djb2 hash taken from here[0]
// [0] http://www.cse.yorku.ca/~oz/hash.html
uint32_t obj_hash(struct Obj *obj) {
  if (obj->kind != OBJ_STR) assert(0);

  uint32_t hash = 5381;
  for (int i = 0; i < obj->inner.str.len; ++i) {
    uint32_t c = obj->inner.str.buf[i];
    hash = ((hash << 5) + hash) + c;
  }

  return hash;
}

struct Obj *obj_clone(struct Obj *obj) {
	obj->count += 1;
	return obj;
}

void obj_drop(struct Obj *obj) {
	assert(obj->count > 0);
	obj->count -= 1;
	if (obj->count == 0) {
		switch (obj->kind) {
      case OBJ_NULL: {
        assert(0);
        break;
      }
      case OBJ_INT: {
        break;
      }
			case OBJ_STR: {
        free(obj->inner.str.buf);
				break;
			}
      case OBJ_BYTES: {
        free(obj->inner.bytes.buf);
        break;
      }
			case OBJ_LIST: {
				for (int i = 0; i < obj->inner.list.len; ++i) {
					obj_drop(obj->inner.list.objs[i]);
				}
				free(obj->inner.list.objs);
				break;
			}
      case OBJ_DICT: {
        for (int i = 0; i < OBJ_DICT_BINS_NO; ++i) {
          obj_drop(obj->inner.dict.bins[i]);
        }
        free(obj->inner.dict.bins);
        break;
      }
		}
		free(obj);
	}
}

uint8_t obj_eq(struct Obj *lhs, struct Obj *rhs) {
  if (lhs->kind != rhs->kind) return 0;
  if (lhs->kind != OBJ_STR) assert(0);

  if (lhs->inner.str.len != rhs->inner.str.len) return 0;
  for (int i = 0; i < lhs->inner.str.len; ++i) {
    if (lhs->inner.str.buf[i] != rhs->inner.str.buf[i]) return 0;
  }
  return 1;
}

void obj_print(struct Obj *obj) {
  if (obj->kind != OBJ_STR) return;

  fwrite(obj->inner.str.buf, sizeof(char), obj->inner.str.len, stdout);
  fwrite("\n", sizeof(char), 1, stdout);
}

/* Int */

struct Obj *obj_int_new(int64_t value) {
	struct Obj *obj = (struct Obj*) malloc(sizeof(struct Obj));;
	obj->count = 1;
	obj->kind = OBJ_INT;
  obj->inner.int_.value = value;
  return obj;
}

struct ObjInt *obj_as_int(struct Obj *obj) {
  if (obj->kind != OBJ_INT) return NULL;
  return &obj->inner.int_;
}

/* Str */

struct Obj *obj_str_new(size_t buf_len, char *buf) {
	struct Obj *obj = (struct Obj*) malloc(sizeof(struct Obj));;
	obj->count = 1;
	obj->kind = OBJ_STR;
  obj->inner.str.buf = (char*) malloc(sizeof(char) * buf_len);
  memcpy(obj->inner.str.buf, buf, sizeof(char) * buf_len);
  obj->inner.str.len = buf_len;
  return obj;
}

struct Obj *obj_str_from_cstring(char *buf) {
  return obj_str_new(strlen(buf), buf);
}

struct ObjStr *obj_as_str(struct Obj *obj) {
  if (obj->kind != OBJ_STR) return NULL;
  return &obj->inner.str;
}

/* Bytes */

struct Obj *obj_bytes_new(size_t buf_len, void *buf) {
	struct Obj *obj = (struct Obj*) malloc(sizeof(struct Obj));;
	obj->count = 1;
	obj->kind = OBJ_BYTES;
  obj->inner.str.buf = malloc(buf_len);
  memcpy(obj->inner.str.buf, buf, buf_len);
  obj->inner.str.len = buf_len;
  return obj;
}

struct Obj *obj_bytes_from_cstring(char *buf) {
  return obj_bytes_new(strlen(buf), buf);
}

struct ObjBytes *obj_as_bytes(struct Obj *obj) {
  if (obj->kind != OBJ_BYTES) return NULL;
  return &obj->inner.bytes;
}

/* List */

struct Obj *obj_list_new() {
	struct Obj *obj = (struct Obj*) malloc(sizeof(struct Obj));;
	obj->count = 1;
	obj->kind = OBJ_LIST;
	obj->inner.list.size = OBJ_LIST_STARTING_SIZE;
	obj->inner.list.len = 0;
	obj->inner.list.objs = (struct Obj**) malloc(sizeof(struct Obj*) * obj->inner.list.size);
  return obj;
}

struct ObjList *obj_as_list(struct Obj *obj) {
  if (obj->kind != OBJ_LIST) return NULL;
  return &obj->inner.list;
}

void obj_list_push(struct ObjList *obj_list, struct Obj *value) {
  if (obj_list->len >= obj_list->size) {
    // size
    obj_list->size *= 2;

    // objs
    struct Obj **old_objs = obj_list->objs;
    obj_list->objs = (struct Obj**) malloc(sizeof(struct Obj*) * obj_list->size);

    for (int i = 0; i < obj_list->len; ++i) {
      obj_list->objs[i] = old_objs[i];
    }

    free(old_objs);
  }

  obj_list->objs[obj_list->len] = obj_clone(value);
  obj_list->len++;
}

struct Obj *obj_list_index(struct ObjList *obj_list, int index) {
  if (index < 0) return NULL;
  if (index >= obj_list->len) return NULL;

  return obj_clone(obj_list->objs[index]);
}

/* Dict */

struct Obj *obj_dict_new() {
	struct Obj *obj = (struct Obj*) malloc(sizeof(struct Obj));;
  obj->count = 1;
  obj->kind = OBJ_DICT;
  obj->inner.dict.bins = (struct Obj**) malloc(sizeof(struct Obj*) * OBJ_DICT_BINS_NO);
  for (int i = 0; i < OBJ_DICT_BINS_NO; ++i) {
    obj->inner.dict.bins[i] = obj_list_new();
  }
  return obj;
}

struct ObjDict *obj_as_dict(struct Obj *obj) {
  if (obj->kind != OBJ_DICT) return NULL;
  return &obj->inner.dict;
}

void obj_dict_assign(struct ObjDict *obj_dict, struct Obj *key, struct Obj *value) {
  uint32_t hash = obj_hash(key);

  // get the bin
  int bin_index = hash % OBJ_DICT_BINS_NO;
  // printf("bin index %d\n", bin_index);
  // obj_print(key);
  struct ObjList *bin_list = obj_as_list(obj_dict->bins[bin_index]);

  // look for the key in the bin
  struct ObjList *found_pair = NULL;
  for (int i = 0; i < bin_list->len; ++i) {
    struct Obj *bin_pair = bin_list->objs[i];
    struct ObjList *bin_pair_list = obj_as_list(bin_pair);
    struct Obj *bin_key = bin_pair_list->objs[0];
    if (obj_eq(bin_key, key)) {
      found_pair = bin_pair_list;
      break;
    }
  }

  if (found_pair != NULL) {
    struct Obj *old_value = found_pair->objs[1];
    found_pair->objs[1] = obj_clone(value);
    obj_drop(old_value);
  } else {
    struct Obj *new_pair = obj_list_new();
    struct ObjList *new_pair_list = obj_as_list(new_pair);
    obj_list_push(new_pair_list, key);
    obj_list_push(new_pair_list, value);

    obj_list_push(bin_list, new_pair);
    obj_drop(new_pair);
  }
}

struct Obj *obj_dict_index(struct ObjDict *obj_dict, struct Obj *key) {
  uint32_t hash = obj_hash(key);

  // get the bin
  int bin_index = hash % OBJ_DICT_BINS_NO;
  // printf("bin index %d\n", bin_index);
  // obj_print(key);
  struct ObjList *bin_list = obj_as_list(obj_dict->bins[bin_index]);

  // look for the key in the bin
  struct Obj *found_obj = NULL;
  for (int i = 0; i < bin_list->len; ++i) {
    struct Obj *bin_pair = bin_list->objs[i];
    struct ObjList *bin_pair_list = obj_as_list(bin_pair);
    struct Obj *bin_key = bin_pair_list->objs[0];
    if (obj_eq(bin_key, key)) {
      found_obj = bin_pair_list->objs[1];
      break;
    }
  }

  if (found_obj != NULL) {
    return obj_clone(found_obj);
  }
  return NULL;
}

uint8_t obj_dict_contains(struct ObjDict *obj_dict, struct Obj *key) {
  struct Obj *value = obj_dict_index(obj_dict, key);
  uint8_t contains = value != NULL;
  if (value != NULL) {
    obj_drop(value);
  }
  return contains;
}

struct Obj *obj_dict_to_list(struct ObjDict *obj_dict) {
  struct Obj *list = obj_list_new();
  struct ObjList *obj_list = obj_as_list(list);
  for (int bin_i = 0; bin_i < OBJ_DICT_BINS_NO; ++bin_i) {
    struct Obj *bin = obj_dict->bins[bin_i];
    struct ObjList *bin_list = obj_as_list(bin);
    for (int i = 0; i < bin_list->len; ++i) {
      obj_list_push(obj_list, bin_list->objs[i]);
    }
  }
  return list;
}

#endif
