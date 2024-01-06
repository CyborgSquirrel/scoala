#ifndef __STRING_BUILDER_H
#define __STRING_BUILDER_H

#include <stddef.h>

#define STRING_BUILDER_BUF_SIZE 1024

typedef struct StringBuilderNode {
  char buf[STRING_BUILDER_BUF_SIZE];
  size_t len;
  struct StringBuilderNode *next;
} StringBuilderNode;

typedef struct {
  StringBuilderNode *start;
  StringBuilderNode *last;
} StringBuilder;

StringBuilder StringBuilder_New();

void StringBuilder_Drop(StringBuilder string_builder);

void StringBuilder_Append(
  StringBuilder *string_builder,
  char *str
);

void StringBuilder_AppendInt(
  StringBuilder *string_builder,
  int val
);

void StringBuilder_Build(
  StringBuilder *string_builder,
  char **str_out // output
);

#endif
