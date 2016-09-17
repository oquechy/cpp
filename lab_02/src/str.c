#include <stdio.h> 
#include "str.h"

char * strcpy(char * destination, const char * source) {
	char *start = destination;
	while (*source) {
		*destination = *source;
		++source;
		++destination;
	}
	*destination = *source;
	return start; 
}

char * strcat(char * destination, const char * source) {
	char *start = destination;
	while (*destination)
		++destination;
	strcpy(destination, source);
	return start; 
}

int strcmp(const char * str1, const char * str2) {
 	while (*str1 && *str2 && *str1 == *str2) {
		++str1;
		++str2;
	}
	if (*str1 < *str2)
		return -1;
	if (*str1 == *str2)
		return 0;
	return 1;
}

size_t strlen(const char * str) {
 	size_t len = 0;
	while (*(str++))
		++len;
	return len;
}

