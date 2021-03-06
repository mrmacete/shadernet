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

#include "set.h"
#include "testing.h"
#include "sn_memory.h"


compare_result
test_set_int_compare( void * p_data1, void * p_data2 )
{
	if ( p_data1 != NULL && p_data2 != NULL )
	{
		if ( p_data1 == p_data2 )
			return ELEMENTS_EQUAL;
		if ( (*(int*)p_data1) == (*(int*)p_data2) )
			return ELEMENTS_EQUAL;
	}

	return ELEMENTS_DIFFER;

}

int main( int argc, char*argv[] )
{
	set * p_set = NULL;

	test_set_output( TEST_OUTPUT_BOTH );

	p_set = set_create();

	if ( test_assert_true ( p_set != NULL, "set creation" ) )
	{
		/* create a set with 35 elements */
		int i, *test_search;
		for( i=0; i<35; i++ )
		{
			int * test_element = (int*) malloc( sizeof(int) );
			*test_element = i;
			set_push_element( p_set, (void*) test_element );

			if ( ! test_assert_true( p_set->size == (i + 1) , "set element pushing") )
				break;

		}		

		test_search = (int*) malloc( sizeof(int) );

		/* search for an existing element */
		*test_search = 10;
		test_assert_true( set_contains( p_set, test_search, &test_set_int_compare ), "set search existing" ); 
		
		/* search for a non-existing element */
		*test_search = 56;
		test_assert_true( !set_contains( p_set, test_search, &test_set_int_compare ), "set search non-existing" ); 

		sn_free( (void**) &test_search );

		set_free( &p_set );
		
	}

	
	exit(0);
	
}
