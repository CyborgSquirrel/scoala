#include "string_builder.h"

#include <stdio.h>
#include <stdlib.h>

StringBuilderNode *StringBuilderNode_New() {
  StringBuilderNode *node = (StringBuilderNode *) malloc(sizeof(StringBuilderNode));
  node->len = 0;
  node->next = NULL;
  return node;
}

StringBuilder StringBuilder_New() {
  StringBuilder string_builder;
  string_builder.start = NULL;
  string_builder.last = NULL;
  return string_builder;
}

void StringBuilder_Drop(StringBuilder string_builder) {
  StringBuilderNode *node = string_builder.start;
  while (node != NULL) {
    StringBuilderNode *node_next = node->next;
    free(node);
    node = node_next;
  }
}

void StringBuilder_Append(
  StringBuilder *string_builder,
  char *str
) {
  if (str[0] == '\0') {
    return;
  }

  int str_i = 0;
  
  StringBuilderNode **node = &string_builder->last;
  while (1) {
    if (*node == NULL) {
      *node = StringBuilderNode_New();
      if (string_builder->start == NULL) {
        string_builder->start = *node;
      }
    }

    for (int i = (*node)->len; i < STRING_BUILDER_BUF_SIZE; ++i) {
      if (str[str_i] == '\0') {
        break;
      }

      (*node)->buf[i] = str[str_i];
      str_i++;
      (*node)->len++;
    }

    if (str[str_i] == '\0') {
      break;
    }

    node = &(*node)->next;
  }
}

void StringBuilder_AppendInt(
  StringBuilder *string_builder,
  int val
) {
	// Yes this sucks. So what?? @_@
	char buf[10];
	sprintf(buf, "%d", val);
  StringBuilder_Append(string_builder, buf);
}

void StringBuilder_Build(
  StringBuilder *string_builder,
  char **str_out // output
) {
  size_t len = 0;
  {
    StringBuilderNode *node = string_builder->last;
    while (node != NULL) {
      len += node->len;
      node = node->next;
    }
  }

  {
    char *str = malloc(sizeof(char) * (len+1));
    *str_out = str;

    int str_i = 0;
    StringBuilderNode *node = string_builder->last;
    while (node != NULL) {
      for (int i = 0; i < node->len; ++i) {
        str[str_i] = node->buf[i];
        str_i++;
      }
      node = node->next;
    }

    str[len] = '\0';
  }
}
