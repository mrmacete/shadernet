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

#ifndef SN_HASH_H
#define SN_HASH_H

#include "sn_config.h"
#include "set.h"

typedef struct _hash_element
{
	void * data;
	unsigned long int k;
	set * overflow;

} hash_element;

typedef struct _hash
{
	hash_element ** vector;
	unsigned long int vector_size;
	unsigned long int size;
	void (*data_deleter)( void ** );
	unsigned long int (*hash_function)(void * data);
} hash;

typedef enum hash_key_type { HASH_KEY_STRING, HASH_KEY_INTEGER, HASH_KEY_CUSTOM } hash_key_type;

hash * 			hash_create( unsigned long int vector_size, hash_key_type key_type );
void			hash_free( hash** pp_hash );

unsigned long int 	hash_function_string( void * key );
unsigned long int 	hash_function_int( void * key );

hash_element * 		hash_get( hash* p_hash, void * key );
void			hash_put( hash* p_hash, void * key, void * data );
void			hash_remove( hash* p_hash, void * key );

#endif
