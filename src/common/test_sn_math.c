#include <stdio.h>
#include <stdlib.h>

#include "sn_math.h"
#include "testing.h"

static char _module_name[] = "TEST_SN_MATH";
int main( int argc, char *argv[] )
{

	test_set_output( TEST_OUTPUT_BOTH );

	test_assert_true( (CLAMP( 3, 0, 1 )) == 1, "clamp up" );
        test_assert_true( (CLAMP( -2, 0, 1 )) == 0, "clamp down" );
        test_assert_true( (CLAMP( 1, 0, 1 )) == 1, "clamp equal up" );
        test_assert_true( (CLAMP( 0, 0, 1 )) == 0, "clamp equal down" );

	matrix * the_matrix = matrix_create(4,4);
	matrix_print( the_matrix );
	matrix_free( &the_matrix );
	exit(0);
}
