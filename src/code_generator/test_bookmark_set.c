/*---------------------------------------------------------------------------*\
 *                              ShaderNet                                    *
 *                                                                           *
 *                Copyright (C) 2008 by Francesco Tamagni                    *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/

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
