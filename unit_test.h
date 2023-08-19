#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"

Status test_kbempah_init_default_returns_nonNULL(char* buffer, int length);
Status test_kbempah_get_size_on_init_default_returns_0(char* buffer, int length);
Status test_kbempah_get_capacity_on_init_default_returns_7(char* buffer, int length);
Status test_kbempah_init_c_string_initializes_to_maddog(char* buffer, int length);
Status test_kbempah_get_size_returns_0_empty_string(char* buffer, int length);
Status test_kbempah_get_size_returns_size_of_init_c_string_non_empty_string(char* buffer, int length);
Status test_kbempah_get_size_returns_size_of_init_c_string_non_empty_string_greater_than_init_capacity(char* buffer, int length);
Status test_kbempah_get_capacity_returns_1_empty_init_c_string(char* buffer, int length);
Status test_kbempah_get_capacity_returns_size_of_init_c_string_plus_one_non_empty_string(char* buffer, int length);
Status test_kbempah_get_capacity_returns_14_after_resize(char* buffer, int length);
Status test_kbempah_my_string_compare_returns_less_than_zero(char* buffer, int length);
Status test_kbempah_my_string_compare_returns_zero(char* buffer, int length);
Status test_kbempah_my_string_compare_returns_greater_than_zero(char* buffer, int length);
Status test_kbempah_my_string_extraction_extracts_whitesp_leading_string_from_file(char* buffer, int length);
Status test_kbempah_my_string_extraction_extracts_from_file(char* buffer, int length);
Status test_kbempah_my_string_extraction_extracts_whitespace_trailing_string_from_file(char* buffer, int length);
Status test_kbempah_my_string_concat_returns_result_before_concatenation(char* buffer, int length);
Status test_kbempah_my_string_concat_returns_size_of_result_after_concatenatation(char* buffer, int length);
Status test_kbempah_my_string_empty_returns_1_empty_string(char* buffer, int length);
Status test_kbempah_my_string_empty_returns_0_non_empty_string(char* buffer, int length);
Status test_kbempah_my_string_at_empty_string(char* buffer, int length);
Status test_kbempah_my_string_at_non_empty_string(char* buffer, int length);
Status test_kbempah_my_string_at_out_of_bounds_index(char* buffer, int length);
Status test_kbempah_my_string_push_back_returns_size_capacity(char* buffer, int length);
Status test_kbempah_my_string_pop_back_returns_size_item(char* buffer, int length);
Status test_kbempah_my_string_push_back_returns_push_back_item(char* buffer, int length);
Status test_kbempah_my_string_destroy_sets_handle_to_NULL(char* buffer, int length);

#endif
