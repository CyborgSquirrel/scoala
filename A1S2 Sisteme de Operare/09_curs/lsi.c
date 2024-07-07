#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct node {
	int value;
	struct node *next;
} node_t;

typedef struct list {
	node_t *head;
	pthread_mutex_t m;
} list_t;

void init(list_t *list) {
	list->head = NULL;
	pthread_mutex_init(&list->m, NULL);
}

void append(list_t *list, int element) {
	node_t **p = &list->head;
	
	pthread_mutex_lock(&list->m);
	while (*p != NULL) {
		p = &((*p)->next);
	}
	*p = (node_t*) malloc(sizeof(node_t));
	(*p)->value = element;
	(*p)->next = NULL;
	pthread_mutex_unlock(&list->m);
}

int contains(list_t *list, int element) {
	node_t **p = &list->head;
	
	pthread_mutex_lock(&list->m);
	while (*p != NULL) {
		if ((*p)->value == element) {
			pthread_mutex_unlock(&list->m);
			return 1;
		}
		p = &((*p)->next);
	}
	pthread_mutex_unlock(&list->m);
	
	return 0;
}

void delete(list_t *list, int element) {
	node_t **p = &list->head;
	
	pthread_mutex_lock(&list->m);
	while (*p != NULL) {
		if ((*p)->value == element) {
			node_t *old_p = *p;
			*p = (*p)->next;
			free(old_p);
			pthread_mutex_unlock(&list->m);
			return;
		}
		p = &((*p)->next);
	}
	pthread_mutex_unlock(&list->m);
}

void destroy(list_t *list) {
	node_t *p = list->head;
	
	pthread_mutex_lock(&list->m);
	while (p != NULL) {
		node_t *next = p->next;
		free(p);
		p = next;
	}
	pthread_mutex_unlock(&list->m);
	pthread_mutex_destroy(&list->m);
}

void dbg(list_t *list) {
	node_t **p = &(list->head);
	
	pthread_mutex_lock(&list->m);
	while (*p != NULL) {
		printf("%d\n", (*p)->value);
		p = &((*p)->next);
	}
	pthread_mutex_unlock(&list->m);
}

int main() {
	list_t l;
	
	init(&l);
	
	append(&l, 1);
	append(&l, 2);
	append(&l, 3);
	dbg(&l);
	
	if (contains(&l, 4)) {
		printf("o no\n");
	}
	if (contains(&l, 2)) {
		printf("o kay\n");
	}
	
	delete(&l, 3);
	destroy(&l);
	
	return 0;
}
