#include <stdio.h>
#include "test_str.h"
#include <string.h>

int main(void) {
	char s11[100], s12[100] = "cat", s13[100] = "cat", s14[100] = "";
	char s21[100], s22[100] = "cat", s23[100] = "cat", s24[100] = "";
	char *res = 0, *ans = 0, s[] = "cucumber", s1[] = "", s2[] = "cuc";
	int ians, ires;
	size_t stans, stres;
	ans = strcpy(s21, s);
	strcpy_test(s11, s, &res, ans);
	printf("Strcpy #1: %d\n", !strcmp(res, ans));
	ans = strcpy(s22, s);
	strcpy_test(s12, s, &res, ans);
	printf("Strcpy #2: %d\n", !strcmp(res, ans));
	ans = strcat(s23, s);
	strcat_test(s13, s, &res, ans);
	printf("Strcat #1: %d\n", !strcmp(res, ans));
	ans = strcat(s24, s);
	strcat_test(s14, s, &res, ans);
	printf("Strcpy #2: %d\n", !strcmp(res, ans));
	ians = strcmp(s, s);
	strcmp_test(s, s, &ires, &ians);
	printf("Strcmp #1: %d\n", (ires == 0 && ians == 0 || ires * ians > 0));
	ians = strcmp(s, s2);
	strcmp_test(s, s2, &ires, &ians);
	printf("Strcmp #2: %d\n", (ires == 0 && ians == 0 || ires * ians > 0));
	ians = strcmp(s1, s);
	strcmp_test(s1, s, &ires, &ians);
	printf("Strcmp #3: %d\n", (ires == 0 && ians == 0 || ires * ians > 0));
	stans = strlen(s);
	strlen_test(s, &stres, &stans);
	printf("Strlen #1: %d\n", (stres == stans));
	stans = strlen(s1);
	strlen_test(s1, &stres, &stans);
	printf("Strlen #2: %d\n", (stres == stans));
	return 0;
}
