#include <string.h>
#include <stdlib.h>
#include "clist.h"

void init_list(struct intrusive_list *l) {
	l->head = malloc(sizeof(struct intrusive_node));
	l->head->next = 0;
	l->head->prev = l->head;
}

struct intrusive_node add_node(struct intrusive_list *l, struct intrusive_node *n) {
	struct intrusive_node *cur = l->head;
	while (cur->next)
		cur = cur->next;
	cur->next = n;
	n->prev = cur;
	n->next = 0;
	return *n;
}


int remove_node(struct intrusive_list *l, struct intrusive_node *n) {
	struct intrusive_node *cur = l->head->next;
	while (cur && cur != n)
		cur = cur->next;
	if (!cur)
		return 0;
	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;
	free(cur);
	return 1;
}

int get_length(struct intrusive_list *l) {
	int cnt = 0;
	struct intrusive_node *cur = l->head;
	while (cur->next) {
		cur = cur->next;
		++cnt;
	}
	return cnt;
}
