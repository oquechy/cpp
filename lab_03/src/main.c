#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "clist.h"

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

struct position_node {
  int x, y;
  struct intrusive_node node;
};


int remove_position(struct intrusive_list *l, int x, int y) { // removes all (x, y) pairs
	struct intrusive_node *cur = l->head;
	while (cur && cur->next) {
		struct position_node *to_del = container_of(cur->next, struct position_node, node);
		if (to_del->x == x && to_del->y == y) {
			if (to_del->node.next) {
				cur->next = to_del->node.next;
				to_del->node.next->prev = cur;
			}
			else
				cur->next = 0;
			free(to_del);
		}
		else 
			cur = cur->next;
	}
}

int add_position(struct intrusive_list *l, int x, int y) {
	struct intrusive_node *cur = l->head;
	while (cur->next)
		cur = cur->next;
	struct position_node *new_position = (struct position_node *)malloc(sizeof(struct position_node));
	new_position->x = x;
	new_position->y = y;
	add_node(l, &(new_position->node));
}

void show_all_positions(struct intrusive_list l) {
	struct intrusive_node *cur = l.head->next;
	struct position_node *cur_position;
	while (cur) {
		cur_position = container_of(cur, struct position_node, node);
		printf("(%i %i) ", cur_position->x, cur_position->y);
		cur = cur->next;
	}
	printf("\n");
}

void remove_all_positions(struct intrusive_list *l) {
	struct intrusive_node *cur = l->head->next;
	l->head->next = 0;
	while (cur) {
		struct position_node *to_del = container_of(cur, struct position_node, node);
		cur = cur->next;
		free(to_del);
	}
}

int get_len(struct intrusive_list l) {
	struct intrusive_node *cur = l.head->next;
	int len = 0;
	while (cur) {
		++len;
		cur = cur->next;
	}
	return len;
}


int main() {
	char input[100], add[] = "add", rm[] = "rm", print[] = "print", rma[] = "rma", len[] = "len", exit[] = "exit";
	int x, y;

	struct intrusive_list l;
	init_list(&l);

	while (scanf("%s", &input)) {
		if (!strcmp(input, add)) {
			scanf("%i %i", &x, &y);
			add_position(&l, x, y);
		}
		else if (!strcmp(input, rm)) {
			scanf("%i %i", &x, &y);
			remove_position(&l, x, y);
		}
		else if (!strcmp(input, print))
			show_all_positions(l);
		else if (!strcmp(input, rma))
			remove_all_positions(&l);
		else if (!strcmp(input, len))
			printf("%i\n", get_len(l));
		else if (!strcmp(input, exit)) {
			remove_all_positions(&l);
			free(l.head);
			break;
		}
		else
			printf("Unknown command\n");
	}
	return 0;
}

