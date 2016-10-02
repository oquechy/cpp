#include <stddef.h>
#include <stdlib.h>

/*1. Реализовать алгоритм merge sort, способный работать с данными разных типов (mergesort.c).

int mergesort (void* base, size_t num, size_t size, int (*compar)(const void*,const void*));

base -- указатель на данные (массив, который надо отсортировать);
num -- количество элементов;
size -- размер элемента массива;
compar -- функция сравнивающая два элемента массива.

Ограничение: все операции, связанные с копированием памяти, надо реализовать самостоятельно.*/

void * copy(void *dst, const void *src, size_t len) {
	char *d = dst;
	const char *s = src;
	size_t i;
	for (i = 0; i < len; i++)
		d[i] = s[i];
	return dst;
}

int mergesort(void *base, size_t num, size_t size, int(*compar)(const void*, const void*)) {
	if (num == 1)
		return 0;

	char *b = base;
	size_t mun = num / 2;
	mergesort(b, mun, size, compar);
	mergesort(b + mun * size, num - mun, size, compar);
	char *f = malloc(size * mun), *s = b + mun * size;
	copy(f, b, size * mun);
	size_t fi = 0, si = 0, bi = 0;
	
	while (fi < mun && si < num - mun) {
		if (compar(f + fi * size, s + si * size) <= 0)
			copy(b + (bi++) * size, f + (fi++) * size, size);
		else
			copy(b + (bi++) * size, s + (si++) * size, size);
	}
	while (fi < mun)
		copy(b + (bi++) * size, f + (fi++) * size, size);
	free(f);
	return 0;
}
