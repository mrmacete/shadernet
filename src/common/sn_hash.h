#ifndef SN_HASH_H
#define SN_HASH_H

#include "sn_config.h"
#include "set.h"

typedef struct _hash_element
{
	void * data;
	/*char key[ NAME_LENGTH ];*/
	unsigned long int k;
	set * overflow;

} hash_element;

typedef struct _hash
{
	hash_element ** vector;
	unsigned long int vector_size;
	unsigned long int size;
} hash;

hash * 			hash_create( unsigned long int vector_size );
void			hash_free( hash** pp_hash );

unsigned long int 	hash_function( const char * key );

hash_element * 		hash_get( hash* p_hash, const char * key );
void			hash_put( hash* p_hash, const char * key, void * data );
void			hash_remove( hash* p_hash, const char * key );
void			hash_clear( hash* p_hash ); 

#endif
