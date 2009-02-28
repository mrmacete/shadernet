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

#include "block_net.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <sn_memory.h>
#include <log.h>
#include <sn_config.h>
#include <sn_string.h>

#include "code_chunk.h"

static const char* _module_name = "BLOCK_NET";

static void generate_code( code_chunk* code, parsed_building_block * root );
static void generate_uniforms( code_chunk * code, block_net * net );
static void generate_header( code_chunk * code, block_net * net );
static void parsed_building_block_deleter( void ** data );
static void replace_input_names( parsed_building_block *pblock );

block_net *
block_net_create( const char * name )
{
	block_net * new_block_net = (block_net*) malloc( sizeof(block_net) );
	new_block_net->name = (char *) malloc( sizeof(char) * NAME_LENGTH );
	if ( name != NULL )
		strncpy( new_block_net->name, name, NAME_LENGTH );

	new_block_net->parsed_blocks = hash_create( 50 , HASH_KEY_STRING );
	new_block_net->parsed_blocks->data_deleter = &parsed_building_block_deleter;
	new_block_net->inputs = set_create();
	new_block_net->root = NULL;

	return new_block_net;
}

void
parsed_building_block_deleter( void ** data )
{
	parsed_building_block_free( (parsed_building_block**) data );
}

void
block_net_free( block_net ** pp_block_net )
{
	if ( pp_block_net != NULL && (*pp_block_net) != NULL )
	{
		(*pp_block_net)->root = NULL;
		hash_free( &(*pp_block_net)->parsed_blocks );
		set_soft_free( &(*pp_block_net)->inputs );
		sn_free( (void**) &(*pp_block_net)->name );
		sn_free( (void**) pp_block_net );
	}
}

void
block_net_add_parsed_block( block_net * net, parsed_building_block * block )
{
	if ( net == NULL )
	{
		LOG_DEBUG( _module_name, "cannot add blocks to a NULL net\n" );
		return;
	}

	if ( block != NULL )
	{
		hash_put( net->parsed_blocks, block->name, (void*) block );
	}
		
}

parsed_building_block*
block_net_get_parsed_block( block_net * net, const char * name )
{
	if ( net && name && net->parsed_blocks )
	{
		sn_string * name_string = sn_string_create( name );
		hash_element * result = hash_get( net->parsed_blocks, (void*) name_string );
		sn_string_free( &name_string );
		if ( result )
			return result->data;
	}

	return NULL;
}


void
clear_inputs( set * inputs )
{
	if ( inputs )
	{
		while( inputs->size )
		{
			set_element * el = set_pop_element( inputs );
			set_element_free( &el );
		}
	}
}

void
traverse_input_pins( block_pin_set * pin_set, set * inputs )
{
	if ( pin_set && inputs )
	{
		set_element * el = pin_set->pin_set.head;
		while( el != NULL )
		{
			block_pin * pin = (block_pin*) el->data;
			if ( pin->source == NULL )
				set_push_element ( inputs, pin );
			else
			{
				if ( pin->source->p_parent )
				{
					if ( pin->source->p_parent->p_parent )
						traverse_input_pins( pin->source->p_parent->p_parent->inputs, inputs );
					else
						LOG_ERROR( _module_name, "source pin's set has not a building block?\n" );
				}
				else
					LOG_ERROR( _module_name, "source pin outside pin set?\n" );
			}
			el = el->next;
		}
	}
}

void
block_net_calculate_inputs( block_net * net )
{
	if ( net && net->root && net->parsed_blocks && net->inputs)
	{
		clear_inputs( net->inputs );		
		traverse_input_pins( net->root->p_block->inputs, net->inputs );
	}
}

code_chunk*
block_net_generate_code( block_net * net )
{
	if ( net )
	{
		code_chunk * chunk = code_chunk_create_empty();
		if ( net->inputs->size == 0 )
			block_net_calculate_inputs( net );

		generate_header( chunk, net );
		generate_uniforms( chunk, net );
		
		if ( net->root )
		{
			generate_code( chunk, net->root );
		}

		return chunk;
	}

	return NULL;

}

void 
generate_code( code_chunk* code, parsed_building_block * root )
{
	if ( root )
	{
		block_pin_set *ps = root->p_block->inputs;
		set_element * el = ps->pin_set.head;
                while( el != NULL )
                {
                        block_pin * pin = (block_pin*) el->data;
                        if ( pin->source != NULL )
                        {
                                if ( pin->source->p_parent )
                                {
                                        if ( pin->source->p_parent->p_parent )
                                                generate_code( code, pin->source->p_parent->p_parent->p_parsed );
                                }
                        }
                        el = el->next;
                }

		replace_input_names( root );
		code_chunk_merge( code, root->p_block->code );		

		
	}
}

void 
generate_uniforms( code_chunk * code, block_net * net )
{
	if ( net && code )
	{
		set_element * el = net->inputs->head;
		code_chunk_add_code( code, "\n", strlen("\n" ) );
		while( el != NULL )
		{
			char * str = 0;
			sn_string * string;
			code_chunk_add_code( code, "uniform ", 8 );
			str = glsl_type_to_string( ((block_pin*) el->data)->type );
			code_chunk_add_code( code, str, strlen( str ) );
			sn_free( (void**) &str );
			code_chunk_add_code( code, " ", 1 );
			string =((block_pin*) el->data)->p_parent->p_parent->p_parsed->name;
			code_chunk_add_string( code, string );
			code_chunk_add_code( code, "_", 1);
			code_chunk_add_code( code, ((block_pin*) el->data)->name, strlen(((block_pin*) el->data)->name) );
			code_chunk_add_code( code, ";", 1 );
			code_chunk_add_code( code, "\n", strlen("\n" ) );
			el = el->next;	
		}	
	}
}

void 
generate_header( code_chunk * code, block_net * net )
{
	if ( net && code )
	{
		code_chunk_add_code( code, "/*\n", 3 );
		code_chunk_add_code( code, " * shader: ", 11 );
		code_chunk_add_code( code, net->name, strlen( net->name ) );
		code_chunk_add_code( code, "\n", 1 );
		code_chunk_add_code( code, " * generated with ShaderNet version ", 36 );
		code_chunk_add_code( code, SN_VERSION, strlen( SN_VERSION ));
		code_chunk_add_code( code, "\n", 1 );
		code_chunk_add_code( code, " */\n", 4 );
	}
}

code_chunk *
get_pin_name( block_pin * p_pin )
{
	if ( p_pin != NULL )
	{
		code_chunk * pin_name = 
			code_chunk_create_from_buffer( 
				p_pin->p_parent->p_parent->p_parsed->name->buffer,
				p_pin->p_parent->p_parent->p_parsed->name->len 
			);

		code_chunk_add_code( pin_name, "_", 1 );
		code_chunk_add_code( pin_name, p_pin->name, strlen( p_pin->name ) );

		return pin_name;
	}				
	
	return code_chunk_create_empty();
}

void 
replace_input_names( parsed_building_block *pblock )
{
	if ( pblock != NULL && pblock->bookmarks)
	{
		set_element * el = pblock->bookmarks->_set.head;
		while ( el != NULL )
		{
			parsing_bookmark * bm = (parsing_bookmark*) el->data;
			assert( bm != NULL );
			if ( bm != NULL && bm->type == BOOKMARK_PIN )
			{
				if ( bm->p_couple->type[0] == 'i' )
				{
					code_chunk * input_name = get_pin_name( bm->u_association.p_pin );
					parsed_building_block_replace( pblock, bm, input_name );
					code_chunk_free( &input_name );
				}
			}
			el = el->next;
		}
	}
	

}
