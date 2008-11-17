#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <testing.h>

#include "code_chunk.h"

int main( int argc, char *argv[] )
{
	code_chunk * test_chunk = NULL;
	code_chunk * test_chunk_splitted = NULL;
	const char * test_code="this is a test line of code\n";
	const char * test_code_del="this is a test line of code to be deleted\n";
	float overhead = 1.0f;
	test_set_output( TEST_OUTPUT_NOT_PASSED );

	test_chunk = code_chunk_create_empty();

	test_assert_true( test_chunk != NULL, "code chunk alloc" );
	test_assert_true( test_chunk->buffer == NULL, "code chunk initial NULL buffer" );
	test_assert_true( test_chunk->used_size == 0, "code chunk initial 0 used size" );
	test_assert_true( test_chunk->buffer_size == 0, "code chunk initial 0 buffer size" );
	
	code_chunk_add_code( test_chunk, test_code, strlen(test_code) ); 

	test_assert_true( test_chunk->buffer != NULL, "code chunk buffer allocated" );
	test_assert_true( test_chunk->used_size == 28, "code chunk used size is 28" );

	printf( "buffer size is %d\n", test_chunk->buffer_size );
	printf( "used size is %d\n", test_chunk->used_size );

	code_chunk_add_code( test_chunk, test_code, strlen(test_code) ); 
	code_chunk_add_code( test_chunk, test_code, strlen(test_code) ); 
	code_chunk_add_code( test_chunk, test_code_del, strlen(test_code_del) ); 
	code_chunk_add_code( test_chunk, test_code_del, strlen(test_code_del) ); 
	code_chunk_add_code( test_chunk, test_code_del, strlen(test_code_del) ); 
	code_chunk_add_code( test_chunk, test_code_del, strlen(test_code_del) ); 
	code_chunk_add_code( test_chunk, test_code, strlen(test_code) ); 
	code_chunk_add_code( test_chunk, test_code, strlen(test_code) ); 
	code_chunk_add_code( test_chunk, test_code, strlen(test_code) ); 
	code_chunk_add_code( test_chunk, test_code, strlen(test_code) ); 
	code_chunk_add_code( test_chunk, test_code, strlen(test_code) ); 
	code_chunk_add_code( test_chunk, test_code, strlen(test_code) ); 
	code_chunk_add_code( test_chunk, test_code, strlen(test_code) ); 
	code_chunk_add_code( test_chunk, test_code, strlen(test_code) ); 
	code_chunk_add_code( test_chunk, test_code, strlen(test_code) ); 
	code_chunk_add_code( test_chunk, test_code, strlen(test_code) ); 
	code_chunk_add_code( test_chunk, test_code, strlen(test_code) ); 
	code_chunk_add_code( test_chunk, test_code, strlen(test_code) ); 
	code_chunk_add_code( test_chunk, test_code, strlen(test_code) ); 
	code_chunk_add_code( test_chunk, test_code, strlen(test_code) ); 
	code_chunk_add_code( test_chunk, test_code, strlen(test_code) ); 
	code_chunk_add_code( test_chunk, test_code, strlen(test_code) ); 
	code_chunk_add_code( test_chunk, test_code_del, strlen(test_code_del) ); 

	printf( "buffer size is %d\n", test_chunk->buffer_size );
	printf( "used size is %d\n", test_chunk->used_size );


	test_assert_true( test_chunk->n_lines == 24, "number of lines" );

	code_chunk_print( test_chunk, 0 );
	code_chunk_print( test_chunk, PRINT_LINE_NUMBERS );
	overhead = code_chunk_calc_overhead( test_chunk );
	printf( "total overhead after adding code: %2.2f\n", overhead );
	
	code_chunk_delete_lines( test_chunk, 3, 4 );
	test_assert_true( test_chunk->n_lines == 20, "number of lines after deletion 1" );

	code_chunk_print( test_chunk, PRINT_LINE_NUMBERS );

	code_chunk_delete_lines( test_chunk, 19, 4 );
	test_assert_true( test_chunk->n_lines == 19, "number of lines after deletion 2" );

	code_chunk_print( test_chunk, PRINT_LINE_NUMBERS );

	test_chunk_splitted = code_chunk_split( test_chunk, 1 );

	
	test_assert_true( test_chunk->n_lines == 1, "number of lines after split on the original" );
	test_assert_true( test_chunk_splitted->n_lines == 18, "number of lines after split on the splitted" );

	code_chunk_print( test_chunk, PRINT_LINE_NUMBERS );
	code_chunk_print( test_chunk_splitted, PRINT_LINE_NUMBERS );

	code_chunk_merge( test_chunk, test_chunk_splitted );
	code_chunk_free( & test_chunk_splitted );

	code_chunk_print( test_chunk, PRINT_LINE_NUMBERS );

	test_assert_true( test_chunk->n_lines == 19, "number of lines after merge" );

	overhead = code_chunk_calc_overhead( test_chunk );
	printf( "total overhead after test: %2.2f\n", overhead );

	code_chunk_prune_unused( test_chunk );
	code_chunk_print( test_chunk, PRINT_LINE_NUMBERS );

	overhead = code_chunk_calc_overhead( test_chunk );
	printf( "total overhead after pruning: %2.2f\n", overhead );

	code_chunk_free( & test_chunk );
	test_assert_true( test_chunk == NULL, "code chunk free" );


	exit(0);
}
