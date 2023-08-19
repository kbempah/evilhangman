#include "my_string.h"
#include <string.h>

Status test_kbempah_init_default_returns_nonNULL(char* buffer, int length)
{
	MY_STRING hString = my_string_init_default();

	if (hString == NULL) {
		strncpy(buffer, "test_init_default_returns_nonNULL\n"
				"my_string_init_default returns NULL", length);
		return FAILURE;
	}
	else {
		my_string_destroy(&hString);
		strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
		return SUCCESS;
	}
}

Status test_kbempah_get_size_on_init_default_returns_0(char* buffer, int length)
{
	MY_STRING hString = NULL;

	Status status;

	hString = my_string_init_default();

	if (my_string_get_size(hString) != 0) {
		status = FAILURE;
		printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
				"Did not receive 0 from get_size after init_default\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_kbempah_get_capacity_on_init_default_returns_7(char* buffer, int length)
{
	MY_STRING hString = my_string_init_default();
	Status status;

	if (my_string_get_capacity(hString) != 7) {
		status = FAILURE;
		printf("Expected a capacity of 7 but got %d\n", my_string_get_capacity(hString));
		strncpy(buffer, "test_get_capacity_on_init_default_returns_7\n"
				"Did not receive 7 from get_capacity after init_default\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_get_capacity_on_init_default_returns_7\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_kbempah_init_c_string_initializes_to_maddog(char* buffer, int length)
{
	MY_STRING hString;
	Status status;
	hString = my_string_init_c_string("maddog");

	if (hString == NULL) {
		status = FAILURE;
		printf("Expected data to be initialized with \"maddog\", but got NULL");
		strncpy(buffer, "test_init_c_string_prints_maddog\n"
				"was not initialized to \"maddog\" after init_c_string\n",length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_init_c_string_initialized_to_maddog\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_kbempah_get_size_returns_0_empty_string(char* buffer, int length) 
{
	MY_STRING hString;
	Status status;
	hString = my_string_init_c_string("");

	if (my_string_get_size(hString) != 0) {
		status = FAILURE;
		printf("Expected size 0 after initializing with empty init_c_string, but got %d\n", my_string_get_size(hString));
		strncpy(buffer, "test_get_size_returns_0_empty_string\n"
				"Did not receive 0 after init_c_string\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_get_size_returns_0_empty_string\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_kbempah_get_size_returns_size_of_init_c_string_non_empty_string(char* buffer, int length)
{
	MY_STRING hString;
	Status status;
	hString = my_string_init_c_string("maddog");

	if (my_string_get_size(hString) != 6) {
		status = FAILURE;
		printf("Expected size 6 after initializing with nonempty init_c_string, but got %d\n", my_string_get_size(hString));
		strncpy(buffer, "test_get_size_returns_size_of_init_c_string_non_empty_string\n"
				"Did not receive 6 after init_c_string\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_get_size_returns_6_non_empty_string\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_kbempah_get_size_returns_size_of_init_c_string_non_empty_string_greater_than_init_capacity(char* buffer, int length)
{
	MY_STRING hString;
	Status status;
	hString = my_string_init_c_string("maddoghis");

	if (my_string_get_size(hString) != 9) {
		status = FAILURE;
		printf("Expected size 9 after initializing with nonempty init_c_string, but got %d\n", my_string_get_size(hString));
		strncpy(buffer, "test_get_size_returns_size_of_init_c_string_non_empty_string\n"
				"Did not receive 6 after init_c_string\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_get_size_returns_9_non_empty_string\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_kbempah_get_capacity_returns_1_empty_init_c_string(char* buffer, int length)
{
	MY_STRING hString;
	Status status;
	hString = my_string_init_c_string("");

	if (my_string_get_capacity(hString) != 1) {
		status = FAILURE;
		printf("Expected capacity 1 after initializing with empty init_c_string, but got %d\n", my_string_get_capacity(hString));
		strncpy(buffer, "test_get_capacity_returns_7_empty_init_c_string\n"
				"Did not receive 1 after init_c_string\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_get_capacity_returns_1_empty_init_c_string\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_kbempah_get_capacity_returns_size_of_init_c_string_plus_one_non_empty_string(char* buffer, int length)
{
	MY_STRING hString;
	Status status;
	hString = my_string_init_c_string("maddo");

	if (my_string_get_capacity(hString) != 6) {
		status = FAILURE;
		printf("Expected capacity 6 after initializing with empty init_c_string, but got %d\n", my_string_get_capacity(hString));
		strncpy(buffer, "test_get_capacity_returns_7_empty_init_c_string\n"
				"Did not receive 6 after init_c_string\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_get_capacity_returns_6_empty_init_c_string\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_kbempah_get_capacity_returns_14_after_resize(char* buffer, int length)
{
	MY_STRING hString;
	Status status;
	hString = my_string_init_c_string("Tentacles");

	if (my_string_get_capacity(hString) != 14) {
		status = FAILURE;
		printf("Expected capacity 14 after initializing with init_c_string, but got %d\n", my_string_get_capacity(hString));
		strncpy(buffer, "test_get_capacity_returns_14_after_resize\n"
				"Did not receive 14 after resize\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_get_capacity_returns_14_after_resize\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_kbempah_my_string_compare_returns_less_than_zero(char* buffer, int length)
{
	MY_STRING left, right;
	Status status;
	left = my_string_init_c_string("app");
	right = my_string_init_c_string("apple");

	if (my_string_compare(left,right) >= 0) {
		status = FAILURE;
		printf("Expected number less than zero, but got %d\n", my_string_compare(left, right));
		strncpy(buffer, "test_my_string_compare_returns_less_than_zero\n"
				"did not receive less than zero", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_my_string_compare_returns_less_than_zero\n", length);
	}

	my_string_destroy(&left);
	my_string_destroy(&right);
	return status;
}

Status test_kbempah_my_string_compare_returns_zero(char* buffer, int length)
{
	MY_STRING left, right;
	Status status;
	left = my_string_init_c_string("jenkins");
	right = my_string_init_c_string("jenkins");

	if (my_string_compare(left,right) != 0) {
		status = FAILURE;
		printf("Expected zero, but got %d\n", my_string_compare(left, right));
		strncpy(buffer, "test_my_string_compare_returns_zero\n"
				"did not receive zero", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_my_string_compare_returns_zero\n", length);
	}

	my_string_destroy(&left);
	my_string_destroy(&right);
	return status;
}

Status test_kbempah_my_string_compare_returns_greater_than_zero(char* buffer, int length)
{
	MY_STRING left, right;
	Status status;
	left = my_string_init_c_string("yelena");
	right = my_string_init_c_string("armin");

	if (my_string_compare(left,right) <= 0) {
		status = FAILURE;
		printf("Expected number greater than zero, but got %d\n", my_string_compare(left, right));
		strncpy(buffer, "test_my_string_compare_returns_greater_than_zero\n"
				"did not receive greater than zero", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_my_string_compare_returns_greater_than_zero\n", length);
	}

	my_string_destroy(&left);
	my_string_destroy(&right);
	return status;
}

Status test_kbempah_my_string_extraction_extracts_whitesp_leading_string_from_file(char* buffer, int length)
{
	MY_STRING hString = my_string_init_default();
	Status status;
	FILE* fp = NULL;
	fp = fopen("./test1.txt", "r");

	if (my_string_extraction(hString, fp) == FAILURE) {
		status = FAILURE;
		strncpy(buffer, "string extraction hello unsuccessful\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_my_string_extraction_whitesp_successful\n", length);
	}

	fclose(fp);
	my_string_destroy(&hString);
	return status;
}

Status test_kbempah_my_string_extraction_extracts_from_file(char* buffer, int length)
{
	MY_STRING hString = my_string_init_default();
	Status status;
	FILE* fp = NULL;
	fp = fopen("./test2.txt", "r");

	if (my_string_extraction(hString, fp) == FAILURE) {
		status = FAILURE;
		strncpy(buffer, "string extraction mom unsuccessful\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_my_string_extraction_successful\n", length);
	}

	fclose(fp);
	my_string_destroy(&hString);
	return status;
}

Status test_kbempah_my_string_extraction_extracts_whitespace_trailing_string_from_file(char* buffer, int length)
{
	MY_STRING hString = my_string_init_default();
	Status status;
	FILE* fp = NULL;
	fp = fopen("./test3.txt", "r");

	if (my_string_extraction(hString, fp) == FAILURE) {
		status = FAILURE;
		strncpy(buffer, "string extraction jenkins unsuccessful\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_my_string_extraction_whitesp_successful\n", length);
	}

	fclose(fp);
	my_string_destroy(&hString);
	return status;
}

Status test_kbempah_my_string_concat_returns_result_before_concatenation(char* buffer, int length)
{
    MY_STRING hResult;
    hResult = my_string_init_c_string("mad");
    MY_STRING hAppend;
    hAppend = my_string_init_c_string("dog");
	Status status;

	if (my_string_concat(hResult, hAppend) == FAILURE) {
		status = FAILURE;
		printf("Expected 1 but got %d", (!hResult && !hAppend));
		strncpy(buffer, "test_my_string_concat_returns_result_before_concat\n"
				"did not receive 1\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_my_string_concat_returns_result_before_concat\n", length);
	}

	my_string_destroy(&hResult);
	my_string_destroy(&hAppend);
	return status;
}

Status test_kbempah_my_string_concat_returns_size_of_result_after_concatenatation(char* buffer, int length)
{
    MY_STRING hResult;
    hResult = my_string_init_c_string("mad");
    MY_STRING hAppend;
    hAppend = my_string_init_c_string("dog");
	Status status;

	my_string_concat(hResult, hAppend);

	if (my_string_get_size(hResult) != 6) {
		status = FAILURE;
		printf("Expected 6 for concatenation, but got %d\n", my_string_get_size(hResult));
		strncpy(buffer, "test_my_string_concat_returns_size_of_result_after_concatenatation\n"
				"did not receive size of resulting string\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_my_string_concat_returns_size_of_result_after_concatenatation\n", length);
	}

	my_string_destroy(&hResult);
	my_string_destroy(&hAppend);
	return status;
}

Status test_kbempah_my_string_empty_returns_1_empty_string(char* buffer, int length)
{
	MY_STRING hString;
	Status status;
	hString = my_string_init_c_string("");

	if (my_string_empty(hString) != TRUE) {
		status = FAILURE;
		printf("Expected 1 for empty string, but got %d\n", my_string_empty(hString));
		strncpy(buffer, "test_my_string_empty_returns_1_empty_string\n"
				"did not receive 1\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_my_string_empty_returns_1_empty_string\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_kbempah_my_string_empty_returns_0_non_empty_string(char* buffer, int length)
{
	MY_STRING hString;
	Status status;
	hString = my_string_init_c_string("123");

	if (my_string_empty(hString) != FALSE) {
		status = FAILURE;
		printf("Expected 0 for non empty string, but got %d\n", my_string_empty(hString));
		strncpy(buffer, "test_my_string_empty_returns_0_non_empty_string\n"
				"did not return 0\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_my_string_empty_returns_0_non_empty_string\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_kbempah_my_string_at_empty_string(char* buffer, int length)
{
    MY_STRING hString;
    hString = my_string_init_c_string("");
	Status status;

	if (my_string_at(hString, 0) != NULL) {
		status = FAILURE;
		printf("Expected NULL , but got %c\n", *my_string_at(hString, 0));
		strncpy(buffer, "test_my_string_at_empty_string\n"
				"did not receive NULL\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_my_string_at_empty_string returns NULL\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_kbempah_my_string_at_non_empty_string(char* buffer, int length)
{
    MY_STRING hString;
    hString = my_string_init_c_string("hello");
	Status status;

	if (my_string_at(hString, 0) == NULL) {
		status = FAILURE;
		printf("Expected 'h', but got %c\n", *my_string_at(hString, 0));
		strncpy(buffer, "test_my_string_at_non_empty_string\n"
				"did not receive 'h'\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_my_string_at_non_empty_string returns 'h'\n", length);
	}
	
	my_string_destroy(&hString);
	return status;
}

Status test_kbempah_my_string_at_out_of_bounds_index(char* buffer, int length)
{
    MY_STRING hString;
    hString = my_string_init_c_string("Ian");
	Status status;

	if (my_string_at(hString, 4) != NULL) {
		status = FAILURE;
		printf("Expected NULL , but got %c\n", *my_string_at(hString, 4));
		strncpy(buffer, "test_my_string_at_empty_string\n"
				"did not receive NULL\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_my_string_at_empty_string returns NULL\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_kbempah_my_string_push_back_returns_size_capacity(char* buffer, int length)
{
    MY_STRING hString;
    hString = my_string_init_c_string("hello");
	Status status;

	for (int i = 0; i < 6; i++)
		my_string_push_back(hString, 'o');
	
	if (my_string_get_size(hString) != 11 && my_string_get_capacity(hString) != 14) {
		status = FAILURE;
		printf("Expected 11 for size and 14 for capacity, but got %d %d\n", my_string_get_size(hString), my_string_get_capacity(hString));
		strncpy(buffer, "test_my_string_push_back_returns_size_capacity\n"
				"did not receive 11 and 14\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_my_string_push_back_returns_size_11_capacity_14\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_kbempah_my_string_pop_back_returns_size_item(char* buffer, int length)
{
    MY_STRING hString;
    hString = my_string_init_c_string("masayoshi");
	Status status;

	my_string_pop_back(hString);

	if (my_string_get_size(hString) != 8 && *my_string_at(hString, 7) != 'h') {
		status = FAILURE;
		printf("Expected size of 8 and 'h', but got %d %c\n", my_string_get_size(hString), *my_string_at(hString, 7));
		strncpy(buffer, "test_my_string_pop_back_return_size_item\n"
				"did not receive 8 and 'h'\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_my_string_pop_back_returns_size_8_item_'h'\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_kbempah_my_string_push_back_returns_push_back_item(char* buffer, int length)
{
    MY_STRING hString;
    hString = my_string_init_c_string("");
	Status status;

	my_string_push_back(hString, 'I');
	
	if (my_string_at(hString, 0) == NULL) {
		status = FAILURE;
		printf("Expected 'I', but got %c\n", *my_string_at(hString, 0));
		strncpy(buffer, "test_my_string_push_back_returns_push_back_item\n"
				"did not receive 'I'\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_my_string_push_back_returns_push_back_item\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_kbempah_my_string_destroy_sets_handle_to_NULL(char* buffer, int length)
{
	MY_STRING hString, hCopy;
	Status status;
	hString = my_string_init_default();
	my_string_destroy(&hString);
	hCopy = hString;

	if (hCopy != NULL) {
		status = FAILURE;
		printf("Expected NULL, but got %p\n", hCopy);
		strncpy(buffer, "test_kbempah_my_string_destroy_sets_handle_to_NULL\n"
				"did not set handle to NULL\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "test_kbempah_my_string_destroy_sets_handle_to_NULL\n", length);
	}

	return status;
}

