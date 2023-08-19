#include <stdio.h>
#include "unit_test.h"

int main(int argc, char* argv[])
{
	Status (*tests[])(char*, int) = 
	{
		test_kbempah_init_default_returns_nonNULL,
		test_kbempah_get_size_on_init_default_returns_0,
		test_kbempah_get_capacity_on_init_default_returns_7,
		test_kbempah_init_c_string_initializes_to_maddog,
		test_kbempah_get_size_returns_0_empty_string,
		test_kbempah_get_size_returns_size_of_init_c_string_non_empty_string,
		test_kbempah_get_size_returns_size_of_init_c_string_non_empty_string_greater_than_init_capacity,
		test_kbempah_get_capacity_returns_1_empty_init_c_string,
		test_kbempah_get_capacity_returns_size_of_init_c_string_plus_one_non_empty_string,
		test_kbempah_my_string_compare_returns_less_than_zero,
		test_kbempah_my_string_compare_returns_zero,
		test_kbempah_my_string_compare_returns_greater_than_zero,
		test_kbempah_my_string_extraction_extracts_whitesp_leading_string_from_file,
		test_kbempah_my_string_extraction_extracts_from_file,
		test_kbempah_my_string_extraction_extracts_whitespace_trailing_string_from_file,
		test_kbempah_my_string_concat_returns_result_before_concatenation,
		test_kbempah_my_string_concat_returns_size_of_result_after_concatenatation,
		test_kbempah_my_string_empty_returns_0_non_empty_string,
		test_kbempah_my_string_empty_returns_1_empty_string,
		test_kbempah_my_string_at_empty_string,
		test_kbempah_my_string_at_non_empty_string,
		test_kbempah_my_string_at_out_of_bounds_index,
		test_kbempah_my_string_push_back_returns_size_capacity,
		test_kbempah_my_string_pop_back_returns_size_item,
		test_kbempah_my_string_push_back_returns_push_back_item,
		test_kbempah_my_string_destroy_sets_handle_to_NULL
	};

	int number_of_functions = sizeof(tests) / sizeof(tests[0]);
	char buffer[500];
	int success_count = 0;
	int failure_count = 0;

	for (int i = 0; i < number_of_functions; i++) {
		if (tests[i](buffer, 500) == FAILURE) {
			printf("FAILED: Test %d failed miserably\n", i);
			printf("\t%s\n", buffer);
			failure_count++;
		}
		else {
			printf("PASS: Test %d passed\n", i);
			printf("\t%s\n", buffer);
			success_count++;
		}
	}
	printf("Total number of tests: %d\n", number_of_functions);
	printf("%d/%d Pass, %d/%d Failure\n", success_count, number_of_functions, failure_count, number_of_functions);
	return 0;
}
