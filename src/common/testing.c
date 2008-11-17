#include "testing.h"
#include "log.h"
#include <stdio.h>

static test_output _test_output = TEST_OUTPUT_NOT_PASSED;

test_result 
test_assert_true( int expression, const char * test_name )
{
	if ( expression )
	{
		if ( _test_output == TEST_OUTPUT_BOTH || _test_output == TEST_OUTPUT_PASSED )
		{
			if ( test_name )
				printf( "TEST %s PASSED\n", test_name );
			else
				printf( "TEST PASSED\n" );
		}
		return TEST_PASSED;
	}
	else
	{
		if ( _test_output == TEST_OUTPUT_BOTH || _test_output == TEST_OUTPUT_NOT_PASSED )
		{
			if ( test_name )
				printf( "TEST %s NOT PASSED\n", test_name );
			else
				printf( "TEST NOT PASSED\n" );
		}
		return TEST_NOT_PASSED;

	}
}

void            
test_set_output( test_output output )
{
	_test_output = output;
}
