#include "testing.h"
#include "sn_string.h"

#include <stdio.h>
#include <stdlib.h>

int main( int argc, char * argv[] )
{
	sn_string * test_string_a, * test_string_b, *c, *tmp;
	test_set_output( TEST_OUTPUT_NOT_PASSED );
	
	test_string_a = sn_string_create( "this is not " );
	test_string_b = sn_string_create( "a test" );

	test_assert_true( sn_string_cmp( test_string_a, test_string_a ) == 0, "compare same string" );
	test_assert_true( sn_string_cmp( test_string_a, test_string_b ) != 0, "compare different string" );

	sn_string_print( test_string_a );
	printf("\n" );
	
	sn_string_print( test_string_b );
	printf("\n" );

	sn_string_cat( test_string_a, test_string_b );
	
	tmp = sn_string_create( "this is not a test" );
	test_assert_true( sn_string_cmp( test_string_a, tmp ) == 0, "cat" );
	sn_string_free( &tmp );

	sn_string_print( test_string_a );
	printf("\n" );

	tmp = sn_string_create( "not a" );
	c = sn_string_mid( test_string_a, 8, 5 );
	test_assert_true( sn_string_cmp( c, tmp ) == 0, "mid" );
	sn_string_free( &tmp );
	
	sn_string_print( c );
	printf("\n" );

	sn_string_free( &test_string_a );
	sn_string_free( &test_string_b );
	sn_string_free( &c );

	exit(0);
}
