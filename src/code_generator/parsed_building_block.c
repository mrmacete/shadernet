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
#include <string.h>

#include <log.h>
#include <sn_memory.h>
#include <sn_config.h>

#include "parsed_building_block.h"

static const char _module_name[]="PARSED_BUILDING_BLOCK";

static void parse_pass1( parsed_building_block* p_pblock );
static int  is_type_valid( parsed_couple * p_couple );
static int  associate_bookmark( parsing_bookmark * p_bookmark, building_block * p_block );

parsed_building_block*  
parsed_building_block_create( building_block * p_block, const char * name )
{
	parsed_building_block * new_pblock = NULL;
	if ( p_block == NULL )
		return NULL;

	new_pblock = (parsed_building_block*) malloc( sizeof( parsed_building_block ) );

	new_pblock->p_block = p_block;
	new_pblock->bookmarks = bookmark_set_create();
	new_pblock->undefined_references = 0;
	new_pblock->invalid_types = 0;

	new_pblock->name = (char*) malloc( sizeof( char ) * NAME_LENGTH );
	*new_pblock->name = 0;
	if ( name != NULL )
	{
		strncpy( new_pblock->name, name, NAME_LENGTH );
	}

	p_block->p_parsed = new_pblock;
	
	parse_pass1( new_pblock );

	printf( "[%s] %s parsed.\n", _module_name, p_block->name );
	printf( "[%s] %s undefined references: %d\n", _module_name, p_block->name, new_pblock->undefined_references );
	printf( "[%s] %s invalid types: %d\n", _module_name, p_block->name, new_pblock->invalid_types );

	return new_pblock;
}

void                    
parsed_building_block_free( parsed_building_block ** pp_parsed_building_block )
{
	if ( pp_parsed_building_block != NULL && (*pp_parsed_building_block) != NULL )
	{
		building_block_free( &(*pp_parsed_building_block)->p_block );
		bookmark_set_free( &(*pp_parsed_building_block)->bookmarks );
		sn_free( (void**) &(*pp_parsed_building_block)->name );
		sn_free( (void**) pp_parsed_building_block );
	}
}

/* fill bookmarks with all syntactically valid dollar statements and associate
 * them with the right pin 
 * */
static void 
parse_pass1( parsed_building_block* p_pblock )
{
	char * dollar = NULL;
        char token[102];

	if ( p_pblock == NULL )
		return;

	if ( p_pblock->p_block == NULL )
	{
		LOG_ERROR( _module_name, "NULL building block, cannot parse" );
		return;
	}

	if ( p_pblock->p_block->code == NULL )
	{
		LOG_ERROR( _module_name, "no code chunk to parse" );
		return;
	}

	if ( p_pblock->p_block->code->buffer == NULL )
	{
		LOG_DEBUG( _module_name, "empty code chunk, nothing to parse" );
		return;
	}

	dollar = p_pblock->p_block->code->buffer;

	while(( dollar = strchr( dollar, '$' )) != NULL )
        {
                parsed_couple * a_couple = NULL;
                int rc = 0;
                rc = sscanf( dollar, "$%101[^][ ;,!=<>*/+-]", token );
                if ( rc )
                {
                        a_couple = parsed_couple_create( token );
			
			if ( is_type_valid( a_couple ) )
			{
                        	parsing_bookmark * a_bookmark = NULL;
                        	a_bookmark = parsing_bookmark_create( dollar, strlen(token)  + 1 , a_couple );
				if ( associate_bookmark( a_bookmark, p_pblock->p_block ) )
				{
                        		bookmark_set_add( p_pblock->bookmarks, a_bookmark );
				}
				else
				{
					p_pblock->undefined_references++;
					parsing_bookmark_free( &a_bookmark );
				}
			}
			else
			{
				p_pblock->invalid_types++;
				parsed_couple_free( &a_couple );
			}	

                }

                dollar++;
        }

	
}

static int  
is_type_valid( parsed_couple * p_couple )
{
	if ( p_couple != NULL )
	{
		if ( strncmp( p_couple->type, "i", sizeof( p_couple->type ) ) == 0 )
			return 1;
		if ( strncmp( p_couple->type, "o", sizeof( p_couple->type ) ) == 0 )
			return 1;
		if ( strncmp( p_couple->type, "p", sizeof( p_couple->type ) ) == 0 )
			return 1;
		if ( strncmp( p_couple->type, "inputs", sizeof( p_couple->type ) ) == 0 )
			return 1;
		if ( strncmp( p_couple->type, "outputs", sizeof( p_couple->type ) ) == 0 )
			return 1;
		if ( strncmp( p_couple->type, "params", sizeof( p_couple->type ) ) == 0 )
			return 1;
		if ( strncmp( p_couple->type, "input", sizeof( p_couple->type ) ) == 0 
			&& p_couple->instance[0] == 0 )
			return 1;
		if ( strncmp( p_couple->type, "output", sizeof( p_couple->type ) ) == 0 
			&& p_couple->instance[0] == 0 )
			return 1;

	}

	return 0;

}

static int  
associate_bookmark( parsing_bookmark * p_bookmark, building_block * p_block )
{
	if ( p_bookmark == NULL || p_block == NULL )
		return 0;
	
	if ( p_bookmark->p_couple->type[0] == 'i' )
	{
		/* associate inputs */
		
		if ( p_bookmark->p_couple->instance[0] == 0 )
		{
			/* empty instance should refer to the lone input */
			if ( p_block->inputs->pin_set.size == 1 )
			{
				p_bookmark->u_association.p_pin = (block_pin*) p_block->inputs->pin_set.head->data;
				p_bookmark->type = BOOKMARK_PIN;
				return 1;
			}
			else
				return 0;
		}
		else
		{
			/* search among pins by instance name */
			block_pin * associated = block_pin_set_by_name( p_block->inputs, p_bookmark->p_couple->instance );
			if ( associated != NULL )
			{
				p_bookmark->u_association.p_pin = associated;
				p_bookmark->type = BOOKMARK_PIN;
				return 1;
			}
			else
				return 0;
		}

	}
	else if ( p_bookmark->p_couple->type[0] == 'o' )
	{
		/* associate outputs */
		if ( p_bookmark->p_couple->instance[0] == 0 )
                {
                        /* empty instance should refer to the lone output */
                        if ( p_block->outputs->pin_set.size == 1 )
                        {
                                p_bookmark->u_association.p_pin = (block_pin*) p_block->outputs->pin_set.head->data;
				p_bookmark->type = BOOKMARK_PIN;
                                return 1;
                        }
                        else
                                return 0;
                }
                else
                {
                        /* search among pins by instance name */
                        block_pin * associated = block_pin_set_by_name( p_block->outputs, p_bookmark->p_couple->instance );
                        if ( associated != NULL )
                        {
                                p_bookmark->u_association.p_pin = associated;
				p_bookmark->type = BOOKMARK_PIN;
                                return 1;
                        }
			else 
				return 0;
                }

	}
	else if ( p_bookmark->p_couple->type[0] == 'p' )
	{
		block_parameter * associated = block_parameter_set_by_name( p_block->params, p_bookmark->p_couple->instance );
		if ( associated != NULL )
		{
			p_bookmark->u_association.p_param = associated;
			p_bookmark->type = BOOKMARK_PARAM;
			return 1;
		}
		else
			return 0;		
	}

	return 0;
}
