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
} hash;

hash * 			hash_create( unsigned long int vector_size );
void			hash_free( hash** pp_hash );

unsigned long int 	hash_function( const char * key );

hash_element * 		hash_get( hash* p_hash, const char * key );
void			hash_put( hash* p_hash, const char * key, void * data );
void			hash_remove( hash* p_hash, const char * key );
void			hash_clear( hash* p_hash ); 

#endif
