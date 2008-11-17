#include "testing.h"
#include "sn_hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char * argv[] )
{
	hash * p_hash = NULL;
	hash_element * result = NULL;
	int i=0;
	test_set_output( TEST_OUTPUT_NOT_PASSED );

	p_hash = hash_create( 7 );

	hash_put( p_hash, "ciao", (void*)1 );
	hash_put( p_hash, "fanculo", (void*) 2 );
	hash_put( p_hash, "morte al clero", (void*) 3 );
	hash_put( p_hash, "this is not a fucking test", (void*) 4 );
	hash_put( p_hash, "latenight", (void*) 5 );

	test_assert_true( p_hash->size == 5, "hash put" );
	test_assert_true( hash_get( p_hash, "ciao" ) != NULL , "get 1" );
	test_assert_true( hash_get( p_hash, "fanculo" ) != NULL , "get 2" );
	test_assert_true( hash_get( p_hash, "morte al clero" ) != NULL , "get 3" );
	test_assert_true( hash_get( p_hash, "this is not a fucking test" ) != NULL , "get 4" );
	test_assert_true( hash_get( p_hash, "latenight" ) != NULL , "get 5" );

	result = hash_get( p_hash, "this is not a fucking test" );
	if ( result )
	{
		test_assert_true( ((int) result->data ) == 4, "data get" );
	}
	
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

	/*while(1)
	{
		char command[ 256 ];
		fgets( command, 256, stdin );
		printf( "%lu\n", hash_function( command ) );
	}
	*/

	hash_free( &p_hash );
	exit(0);
}
