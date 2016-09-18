#include <stdio.h>         
#include "test_str.h"
#include "str.h"   

void strcpy_test(char *s1, char *s2, char **res, char *ans) {
	*res = strcpy(s1, s2);
 	printf("destination -- %s, source -- %s, result -- %s, answer -- %s\n", s1, s2, *res, ans);
}                                           

void strcat_test(char *s1, char *s2, char **res, char *ans) {
	*res = strcat(s1, s2);
 	printf("destination -- %s, source -- %s, result -- %s, answer -- %s\n", s1, s2, *res, ans);
}                                           
                   
void strcmp_test(char *s1, char *s2, int *res, int *ans) {
	*res = strcmp(s1, s2);
 	printf("s1 -- %s, s2 -- %s, result -- %d, answer -- %d\n", s1, s2, *res, *ans);
} 

void strlen_test(char *s1, size_t *res, size_t *ans) {
	*res = strlen(s1);
 	printf("s -- %s, result -- %zd, answer -- %zd\n", s1, *res, *ans);
}                                           
