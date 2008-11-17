#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <testing.h>

#include "parsed_couple.h"

int main( int argc, char *argv[] )
{
	char test[] = "if ( $outputs.val1 == $input ) $params.testParam:literal = $params.another";
	char * dollar = NULL;
	char token[102];

	test_set_output( TEST_OUTPUT_NOT_PASSED );

	dollar = test;
	while(( dollar = strchr( dollar, '$' )) != NULL )
	{
		parsed_couple * a_couple = NULL;
		sscanf( dollar, "$%101[^ ;,!=]", token );
		a_couple = parsed_couple_create( token );
		
		test_assert_true( a_couple != NULL, "parsed couple creation" );
		test_assert_true( a_couple->type[0] != 0, "parsed couple type not empty" );

		parsed_couple_print( a_couple );
		parsed_couple_free( &a_couple );

		test_assert_true( a_couple == NULL , "parsed couple destruction" );
		
		dollar++;
	}

	

	exit(0);
}
