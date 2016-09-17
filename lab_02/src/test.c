#include "test_str.h"
#include <stdio.h>

int main(void) {
	if (!strcpy_test_empty_source())
		printf("strcpy_test_empty_source failed!!!\n");
	else
		printf("Ok\n");
	if (!strcpy_test_filled_destination())
		printf("strcpy_test_filled_destination failed!!!\n");
	else
		printf("Ok\n");
	if (!strcpy_test_empty_destination())
		printf("strcpy_test_empty_destination failed!!!\n");
	else
		printf("Ok\n");
	if (!strcat_test_empty_destination())
		printf("strcat_test_empty_destination failed!!!\n");
	else
		printf("Ok\n");
	if (!strcat_test_empty_source())
		printf("strcat_test_empty_source failed!!!\n");
	else
		printf("Ok\n");
	if (!strcat_test_both_empty())
		printf("strcat_test_both_empty failed!!!\n");
	else
		printf("Ok\n");
	if (!strcat_test_both_filled())
		printf("strcat_test_both_filled failed!!!\n");
	else
		printf("Ok\n");
	if (!strcmp_test_equal())
		printf("strcmp_test_equal failed!!!\n");
	else
		printf("Ok\n");
	if (!strcmp_test_less())
		printf("strcmp_test_less failed!!!\n");
	else
		printf("Ok\n");
	if (!strcmp_test_greater())
		printf("strcmp_test_greater failed!!!\n");
	else
		printf("Ok\n");
	if (!strlen_test_empty())
		printf("strlen_test_empty failed!!!\n");
	else
		printf("Ok\n");
	if (!strlen_test_filled())
		printf("strlen_test_filled failed!!!\n");
	else
		printf("Ok\n");
	return 0;
}