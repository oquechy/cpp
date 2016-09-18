#include <stdio.h> 
#include "str.h"                   

char * strcpy(char * destination, const char * source) {
	char *d = destination;
	const char *s = source;
	while (*s) {
		*d = *s;
		++s;
		++d;
	}
	*d = 0;
	//printf("!");
	return destination; 
}

char * strcat(char * destination, const char * source) {
	char *d = destination;
	const char *s = source;
	while (*d)
		++d;
	strcpy(d, s);       
	//printf("!");
	return destination; 
}

int strcmp(const char * str1, const char * str2) {
	const char *s1 = str1, *s2 = str2;
 	while (*s1 && *s2 && *s1 == *s2) {
		++s1;
		++s2;
	}                   
	//printf("!");
	if (*s1 < *s2)
		return -1;
	if (*s1 == *s2)
		return 0;
	return 1;
}

size_t strlen(const char * str) {
	const char *s = str;
 	size_t len = 0;
	while (*(s++))
		++len;
        //printf("!");
	return len;
}
