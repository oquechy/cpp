#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_str.h"
#include "str.h"   
 
int strcpy_test_empty_source(void) {
	string s3 ="fefe";
 	char s1[] = "", s2[100], ans[] = "", *res = strcpy(s2, s1);
	printf("destination -- %s, source -- %s, result -- %s, answer -- %s\n", s2, s1, res, ans);
	int d;
	if (res == ans)
		d = 1;
	else
		d = 0;
	printf("%d\n", d);
	return (res == ans);
}

int strcpy_test_filled_destination(void) {
 	char s1[] = "cucubmer", s2[] = "rerererererererer", ans[] = "cucumber", *res = strcpy(s2, s1);
	printf("destination -- %s, source -- %s, result -- %s, answer -- %s\n", s2, s1, res, ans);
	return (res == ans);
}

int strcpy_test_empty_destination(void) {
 	char s1[] = "shrimp", s2[100], ans[] = "shrimp", *res = strcpy(s2, s1);
	printf("destination -- %s, source -- %s, result -- %s, answer -- %s\n", s2, s1, res, ans);
	return (res == ans);
}

int strcat_test_empty_destination(void) {
 	char s1[] = "sweater", *s2 = (char *)malloc(100 * sizeof(char)), ans[] = "sweater", *res = strcat(s2, s1);
	s2[0] = 0;
	printf("destination -- %s, source -- %s, result -- %s, answer -- %s\n", s2, s1, res, ans);
	return (res == ans);
}

int strcat_test_empty_source(void) {
 	char s1[] = "", *s2 = (char *)malloc(100 * sizeof(char)), ans[] = "cat", *res = strcat(s2, s1);
	s2[0] = 'c';
	s2[1] = 'a';
	s2[2] = 't';
	s2[3] = 0;
	printf("destination -- %s, source -- %s, result -- %s, answer -- %s\n", s2, s1, res, ans);
	return (res == ans);
}

int strcat_test_both_empty(void) {
 	char s1[] = "", *s2 = (char *)malloc(100 * sizeof(char)), ans[] = "", *res = strcat(s2, s1);
	s2[0] = 0;
	printf("destination -- %s, source -- %s, result -- %s, answer -- %s\n", s2, s1, res, ans);
	return (res == ans);
}

int strcat_test_both_filled(void) {
 	char s1[] = "weather", *s2 = (char *)malloc(100 * sizeof(char)), ans[] = "catweather", *res = strcat(s2, s1);
	s2[0] = 'c';
	s2[1] = 'a';
	s2[2] = 't';
	s2[3] = 0;
	printf("destination -- %s, source -- %s, result -- %s, answer -- %s\n", s2, s1, res, ans);
	return (res == ans);
}

int strcmp_test_equal(void) {
 	char *s1[] = {"", "cat", "concat"}, *s2[] = {"", "cat", "concat"};
	int ans[3] = {0}, res[3];
	for (int i = 0; i < 3; ++i) {
		res[i] = strcmp(s1[i], s2[i]);
		printf("first string -- %s, second string -- %s, result -- %s, answer -- %s\n", s2[i], s1[i], res[i], ans[i]);
	}
	return (res == ans);
}

int strcmp_test_less(void) {
 	char *s1[] = {"", "cat", "concat"}, *s2[] = {"a", "car", "conscat"};
	int ans[3] = {-1, -1, -1}, res[3];
	for (int i = 0; i < 3; ++i) {
		res[i] = strcmp(s1[i], s2[i]);
		printf("first string -- %s, second string -- %s, result -- %s, answer -- %s\n", s2[i], s1[i], res[i], ans[i]);
	}
	return (res == ans);
}

int strcmp_test_greater(void) {
 	char *s1[] = {"a", "cat", "concat"}, *s2[] = {"", "cad", "concaaa"};
	int ans[3] = {0}, res[3];
	for (int i = 0; i < 3; ++i) {
		res[i] = strcmp(s1[i], s2[i]);
		printf("first string -- %s, second string -- %s, result -- %s, answer -- %s\n", s2[i], s1[i], res[i], ans[i]);
	}
	return (res == ans);
}                           

int strlen_test_empty(void) {
	size_t res = strlen(""), ans = 0;
	return (res == ans);	
}

int strlen_test_filled(void) {
	size_t res = strlen("owls"), ans = 4;
	return (res == ans);	
}
        
