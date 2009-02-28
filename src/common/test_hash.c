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

#include "testing.h"
#include "sn_hash.h"
#include "sn_string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void string_deleter( void** data )
{	
	sn_string_free( (sn_string**) data );
}

int main( int argc, char * argv[] )
{
	hash * p_hash = NULL;
	hash_element * result = NULL;
	sn_string *keys[5];
	int i=0;
	test_set_output( TEST_OUTPUT_NOT_PASSED );

	p_hash = hash_create( 7, HASH_KEY_STRING );
	p_hash->data_deleter = &string_deleter;

	keys[0] = sn_string_create( "hello" );
	keys[1] = sn_string_create( "adios" );
	keys[2] = sn_string_create( "this test sucks" );
	keys[3] = sn_string_create( "hey! this is not a test" );
	keys[4] = sn_string_create( "late night train" );

	hash_put( p_hash, keys[0], keys[0] );
	hash_put( p_hash, keys[1], keys[1] );
	hash_put( p_hash, keys[2], keys[2] );
	hash_put( p_hash, keys[3], keys[3] );
	hash_put( p_hash, keys[4], keys[4] );

	test_assert_true( p_hash->size == 5, "hash put" );
	test_assert_true( sn_string_cmp( (sn_string*) hash_get( p_hash, keys[0] )->data, keys[0] ) == 0  , "get 1" );
	test_assert_true( sn_string_cmp( (sn_string*) hash_get( p_hash, keys[1] )->data, keys[1] ) == 0  , "get 2" );
	test_assert_true( sn_string_cmp( (sn_string*) hash_get( p_hash, keys[2] )->data, keys[2] ) == 0  , "get 3" );
	test_assert_true( sn_string_cmp( (sn_string*) hash_get( p_hash, keys[3] )->data, keys[3] ) == 0  , "get 4" );
	test_assert_true( sn_string_cmp( (sn_string*) hash_get( p_hash, keys[4] )->data, keys[4] ) == 0  , "get 5" );

	for ( i=0; i<p_hash->vector_size; i++ )
	{
		printf ( "[%d] = %p\n", i, p_hash->vector[i] );
		if ( p_hash->vector[i] && p_hash->vector[i]->overflow )
		{
			int j=0;
			set_element * el = p_hash->vector[i]->overflow->head;
			while( el != NULL )
			{
				printf("\t[%d].%d = %p\n", i,j,(hash_element*) el->data );
				j++;
				el = el->next;
			}
		}
	}

	/*for ( i=0; i<5; i++)
		sn_string_free( &keys[i] ); */

	hash_free( &p_hash );
	exit(0);
}
