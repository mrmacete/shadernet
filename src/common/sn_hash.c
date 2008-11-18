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

#include "sn_hash.h"
#include "log.h"
#include "sn_memory.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char * _module_name = "SN_HASH";
static hash_element * 	recurse_get( hash_element * head, unsigned long int hf );
static hash_element * 	hash_element_create( unsigned long int hf, void * data );
static void		hash_element_free( hash_element ** pp_el, void (*data_deleter)(void**) );

hash *                  
hash_create( unsigned long int vector_size )
{
	hash * new_hash = (hash*) malloc( sizeof( hash ) );
	new_hash->size =0 ;
	new_hash->vector_size = vector_size;
	new_hash->data_deleter = NULL;

	if ( vector_size )
	{
		new_hash->vector = (hash_element**) malloc( vector_size * sizeof( hash_element* ) );
		memset( new_hash->vector, 0, vector_size * sizeof( hash_element* ) );
		
	}
	else
		new_hash->vector = NULL;

	return new_hash;

}

void
hash_free( hash ** pp_hash )
{
	if ( pp_hash && *pp_hash )
	{
		int i=0;
		for ( i=0; i<(*pp_hash)->vector_size; i++ )
		{
			if ( (*pp_hash)->vector[i] )
				hash_element_free( &(*pp_hash)->vector[i], (*pp_hash)->data_deleter );
		}

		sn_free( (void**) &(*pp_hash)->vector );
		sn_free( (void**) pp_hash );
	}
}

unsigned long int       
hash_function( const char * key )
{
	if ( key )
	{
		register unsigned short int l = strlen( key );
		register unsigned short int  i=0;
		register unsigned long int accum = 0;
		register unsigned short int r = l-i;
		register unsigned long int c = 0;
		register unsigned char shift = 0;
		for ( i=0; i<l; i+=4 )
		{
			r = l-i;
			shift=c=0;
			
			if ( r > 4 )
				r = 4;
			
			while( r > 0 )
			{
				c += key[ i + r - 1] << ( 8 * shift++ );
				r--;
			}	
			
			accum ^= c;
		}
		
		return accum;
	}

	return 0;
}

hash_element *          
hash_get( hash* p_hash, const char * key )
{
	unsigned long int hf = hash_function( key );
	unsigned long int k = hf % p_hash->vector_size;
	if ( p_hash->vector[k] == NULL )
		return NULL;
	else
		return recurse_get( p_hash->vector[k], hf );
}

hash_element * 
recurse_get( hash_element * head, unsigned long int hf )
{
	if ( head )
	{
		if ( head->k == hf )
		{
			return head;
		}
		else
		{
			set_element * el = head->overflow->head;
			while( el != NULL )
			{
				hash_element* hel = (hash_element*) el->data;
				if ( hel->k == hf )
					return hel;

				el = el->next;
			}

		}
	}

	return NULL;
}

void                    
hash_put( hash* p_hash, const char * key, void * data )
{
	unsigned long int hf = hash_function( key );
	unsigned long int k = hf % p_hash->vector_size;
	if ( p_hash->vector[k] == NULL )
	{
		p_hash->vector[k] = hash_element_create( hf, data );
	}
	else
	{
		hash_element * existing = p_hash->vector[k];
		if ( existing->overflow == NULL )
			existing->overflow = set_create();

		set_push_element( existing->overflow, hash_element_create( hf, data ) );
	}

	p_hash->size++;

}

void                    
hash_remove( hash* p_hash, const char * key )
{
	
	unsigned long int hf = hash_function( key );
	unsigned long int k = hf % p_hash->vector_size;
	if ( p_hash->vector[k] != NULL )
	{
		if ( p_hash->vector[k]->k == hf )
		{
			hash_element_free( &p_hash->vector[k], p_hash->data_deleter );
			p_hash->size--;
		}
		else
		{
			set_element * el = p_hash->vector[k]->overflow->head;
			while( el != NULL )
			{
				hash_element * hel = (hash_element*) el->data;
				if ( hel->k == hf )
				{
					hash_element_free( (hash_element**) &el->data, p_hash->data_deleter );
					if ( el->prev != NULL )
						el->prev->next = el->next;
					else
						 p_hash->vector[k]->overflow->head = el->next;

					p_hash->vector[k]->overflow->size--;
					
					set_element_free( &el );
					p_hash->size--;
					return;
				}
				el = el->next;
			}
		}	
	}
}

hash_element * 	
hash_element_create( unsigned long int hf, void * data )
{
	hash_element * el = (hash_element*) malloc( sizeof( hash_element ) );
	el->overflow = NULL;
	el->data = data;
	el->k = hf;
	return el;
}

void		
hash_element_free( hash_element ** pp_el , void (*data_deleter)(void**) )
{
	if ( pp_el && *pp_el )
	{
		(*pp_el)->k = 0;
		if ( data_deleter != NULL )
			data_deleter( &(*pp_el)->data ); 

		(*pp_el)->data = 0;

		if ( (*pp_el)->overflow )
		{
			while( (*pp_el)->overflow->size )
			{
				set_element *sel = set_pop_element( (*pp_el)->overflow );
				hash_element_free( (hash_element**) &sel->data, data_deleter );
				sn_free( (void**) &sel );
			}
		}

		sn_free( (void**) pp_el );
	}
}

