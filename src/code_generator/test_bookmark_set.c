#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <testing.h>

#include "bookmark_set.h"

int main( int argc, char *argv[] )
{
	char test[] = "if ( $outputs.val1 == $input )";
	char * dollar = NULL;
	char token[102];
	bookmark_set * test_set = NULL;

	test_set_output( TEST_OUTPUT_NOT_PASSED );

	test_set = bookmark_set_create();

	test_assert_true( test_set != NULL , "bookmark set creation" );

	dollar = test;
	while(( dollar = strchr( dollar, '$' )) != NULL )
	{
		parsed_couple * a_couple = NULL;
		int rc = 0;
		rc = sscanf( dollar, "$%101[^ ;,!=]", token );
		if ( rc )
		{
			parsing_bookmark * a_bookmark = NULL;
			a_couple = parsed_couple_create( token );
			
			a_bookmark = parsing_bookmark_create( dollar, strlen(token)  + 1 , a_couple );
			parsing_bookmark_print( a_bookmark );
			bookmark_set_add( test_set, a_bookmark );

		}
		
		dollar++;
	}

	test_assert_true( test_set->_set.size == 2, "bookmark set correct size" );

	bookmark_set_free( &test_set );

	test_assert_true( test_set == NULL, "bookmark set destruction" );
	

	exit(0);
}
