#ifndef TESTING_H
#define TESTING_H

typedef enum { TEST_NOT_PASSED=0, TEST_PASSED } test_result;
typedef enum { TEST_OUTPUT_PASSED, TEST_OUTPUT_NOT_PASSED, TEST_OUTPUT_BOTH } test_output;

test_result 	test_assert_true( int expression, const char * test_name );
void		test_set_output( test_output output );

#endif
