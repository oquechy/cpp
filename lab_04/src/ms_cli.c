#include <stdio.h>
#include <string.h>
#include "mergesort.h"

/*2. Реализовать программу, которая сортирует переданные в качестве аргументов данные 
(ms_cli.c) и печатает отсортированный массив. Элементы разделяются пробелом.

Аргументы: type elems*

type -- тип элементов. Принимает одно из значений: int, char, str.
elems -- элементы, которые требуется отсортировать.

Ввод считать всегда корректным.

Пример работы:о
> ./ms_cli int -1 2 0 3
-1 0 2 3
> ./ms_cli char z y x
x y z
> ./ms_cli str foo bar bazooka
bar bazooka foo
*/

int cmp_i(const void *i1, const void *i2) {
	int a = *((int *)i1), b = *((int *)i2);
	return a - b;
}

int cmp_c(const void *c1, const void *c2) {
	char a = *((char *)c1), b = *((char *)c2);
	return (int)(a - b);
}

int cmp_s(const void *s1, const void *s2) {
	char *a = *((char **)s1), *b = *((char **)s2);
	return strcmp(a, b);
}

int to_int(char *s) {
	int x = 0, sign = 1;
	if (s[0] == '-') {
		sign = -1;
		++s;
	}
	while (*s)
		x = x * 10 + *s++ - '0';
	return sign * x;
}

int main(int argc, char **argv) {
	int n[100], i;
	char c[100], ints[] = "int", chars[] = "char";
	if (!strcmp(argv[1], ints)) {
		for (i = 0; i < argc - 2; ++i)
			n[i] = to_int(argv[i + 2]);
		mergesort(n, argc - 2, sizeof(int), cmp_i);
		for (i = 0; i < argc - 2; ++i)
			printf("%i ", n[i]);
		printf("\n");
	}
	else if (!strcmp(argv[1], chars)) {
		for (i = 0; i < argc - 2; ++i)
			c[i] = argv[i + 2][0];
		mergesort(c, argc - 2, 1, cmp_c);
		for (i = 0; i < argc - 2; ++i)
			printf("%c ", c[i]);
		printf("\n");
	}
	else {
		mergesort(argv + 2, argc - 2, sizeof(char *), cmp_s);
		for (i = 0; i < argc - 2; ++i)
			printf("%s ", argv[i + 2]);
		printf("\n");
	}
	return 0;
}
