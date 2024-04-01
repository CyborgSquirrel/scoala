#include "common.h"

// djb2 hash taken from here[0]
// [0] http://www.cse.yorku.ca/~oz/hash.html
uint32_t Common_Hash(char *str) {
  uint32_t hash = 5381;
  for (int i = 0; str[i] != '\0'; ++i) {
    uint32_t c = str[i];
    hash = ((hash << 5) + hash) + c;
  }

  return hash;
}
