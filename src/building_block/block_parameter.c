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

#include "block_parameter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sn_memory.h>
#include <sn_math.h>
#include <set.h>

#include <sn_config.h>
#define VALUE_LENGTH NAME_LENGTH

static void 	block_parameter_free_literals( set ** pp_literals );
static int 	block_parameter_lookup_literal_value( block_parameter *p_param );

static void
block_parameter_free_literals( set ** pp_literals )
{
	if ( pp_literals != NULL && *pp_literals != NULL )
	{
		set_element * el = (*pp_literals)->head;
		while( el )
		{
			literal * l = (literal*) el->data;
			sn_free( (void**) &l->key );
			sn_free( (void**) &el->data );
			el = el->next;
		}

		set_soft_free( pp_literals );

	}
}

block_parameter * block_parameter_create( const char * name )
{
	block_parameter * parameter = (block_parameter*) malloc( sizeof( block_parameter) );
	parameter->name = (char*) malloc( NAME_LENGTH * sizeof(char) );
	if ( name != NULL )
		strncpy( parameter->name, name, NAME_LENGTH );
	parameter->string_value = (char*) malloc( VALUE_LENGTH * sizeof(char) );
	*(parameter->string_value) = 0;
	parameter->string_len = 0;
	parameter->literals = set_create();
	parameter->literal_value = -1;
	return parameter;
}

block_parameter *       
block_parameter_clone( block_parameter * p_src )
{
	if ( p_src )
	{
		block_parameter * parameter = block_parameter_create( p_src->name );	
		set_element * el = p_src->literals->head;
		while( el != NULL )
		{
			literal * l = (literal*) el->data;
			if ( l )
				block_parameter_add_literal( parameter, l->key, l->key_len, l->value );
			el = el->next;
		}

		return parameter;
	}

	return NULL;
}

void block_parameter_free( block_parameter ** p_parameter )
{
	if ( p_parameter != NULL && *p_parameter != NULL )
	{
		sn_free( (void**) &(*p_parameter)->name );
		sn_free( (void**) &(*p_parameter)->string_value );
		block_parameter_free_literals( &(*p_parameter)->literals );
		sn_free( (void**) p_parameter );
	}
}

void                    
block_parameter_add_literal( block_parameter *p_param, const char *key, unsigned int key_len, int value )
{
	literal * new_literal = NULL;

	if ( key == NULL || key_len == 0 || p_param == NULL )
		return;

	new_literal = (literal*) malloc( sizeof( literal ) );
	new_literal->key = (char*) malloc( (key_len+1) * sizeof(char) );
	strncpy( new_literal->key, key, key_len+1 );
	*(new_literal->key + key_len ) = 0;
	new_literal->value = value;
	new_literal->key_len = key_len;
	
	set_push_element( p_param->literals, new_literal );
	
}

static int
block_parameter_lookup_literal_value( block_parameter *p_param )
{
	set_element * el = NULL;

	if ( p_param == NULL )
		return -1;

	if ( p_param->literals == NULL )
		return -1;

	if ( p_param->literals->size == 0 )
		return -1;

	el = p_param->literals->head;
	while( el )
	{
		literal * l = (literal*) el->data;
		if ( l->key_len == p_param->string_len )
		{
			if ( strncmp( l->key, p_param->string_value, l->key_len ) == 0 )
				return l->value;
		}
		el=el->next;
	}

	return -1;

}

void                    
block_parameter_set_string_value( block_parameter *p_param, const char * string_value, unsigned int string_len )
{
	int len = MIN( VALUE_LENGTH-1, string_len );
	if ( p_param == NULL || string_value == NULL || string_len == 0 || p_param->string_value == NULL)
		return;

	strncpy( p_param->string_value, string_value, MIN( (VALUE_LENGTH-1), string_len ) );
	*(p_param->string_value + len)=0;
	p_param->string_len = string_len;

	p_param->literal_value = block_parameter_lookup_literal_value( p_param );
}
