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
