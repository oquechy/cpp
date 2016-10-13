#include <stdio.h>	
#include <string.h>
//#include <vld.h>
#include "position.h"

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

void save_txt(FILE *f, intrusive_list *l) {
	intrusive_node *head = &l->head;
	intrusive_node *node = head->next;

	while (node != head) {
		position_node *pnode = get_position(node);
		fprintf(f, "%i %i\n", pnode->x, pnode->y);
		node = node->next;
	}
}

void save_bin(FILE *f, intrusive_list *l) {
	intrusive_node *head = &l->head;
	intrusive_node *node = head->next;

	for (; node != head; node = node->next) {
		position_node *pnode = get_position(node);
		fwrite(&pnode->x, 3, 1, f);
		fwrite(&pnode->y, 3, 1, f);
	}
}

void print(void *node, void *fmt) {
	position_node *pnode = get_position(node);
	printf(fmt, pnode->x, pnode->y);
}

void count(void *node, void *res) {
//	position_node *pnode = get_position(node);
	++*(int *)res;
}

void apply(intrusive_list *lst, void(*op)(void *node, void *param), void *param) {
	intrusive_node *head = &lst->head;
	intrusive_node *node = head->next;

	for (; node != head; node = node->next)
		op(node, param);
}


int to_signed(int x) {
	if ((x >> 23) & 1) 
		return (x | (-1 << 24));
	return x;
}

int main(int argc, char **argv) {
	intrusive_list list;
	intrusive_list* l = &list;
	init_list(l);

	char lbin[] = "loadbin", stxt[] = "savetext", sbin[] = "savebin", prnt[] = "print", cont[] = "count";
	int x = 0, y = 0;
	FILE *in, *out;
	if (!strcmp(argv[1], lbin)) {
		in = fopen(argv[2], "rb");
		//printf("%i file\n", (in == 0));
		while (fread(&x, 3, 1, in)) {
			fread(&y, 3, 1, in);

			//printf("%i %i\n", x, y);
			add_position(l, to_signed(x), to_signed(y));
		}
		fclose(in);
	}
	else {
		in = fopen(argv[2], "rt");
		while (!feof(in)) {
			if (fscanf(in, "%i %i\n", &x, &y) == 2)
			//printf("%i %i\n", x, y);
				add_position(l, x, y);
		}
		fclose(in);
	}
	//show_all_positions(l);
	if (!strcmp(argv[3], stxt)) {
		out = fopen(argv[4], "wt");
		save_txt(out, l);
		fclose(out);
	}
	else if (!strcmp(argv[3], sbin)) {
		out = fopen(argv[4], "wb");
		save_bin(out, l);
		fclose(out);
	}
	else if (!strcmp(argv[3], prnt)) {
		apply(l, print, argv[4]);
		printf("\n");
	}
	else if (!strcmp(argv[3], cont)) {
		int cnt = 0;
		apply(l, count, &cnt);
		printf("%i\n", cnt);
	}
	else {
		printf("!!!\n");
	}

	remove_all(l);

	return 0;
}