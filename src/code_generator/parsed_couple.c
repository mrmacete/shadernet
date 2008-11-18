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

#include <sn_memory.h>
#include <log.h>

#include "parsed_couple.h"

static const char _module_name[] = "PARSED_COUPLE";

parsed_couple *         
parsed_couple_create(const char* token)
{
	parsed_couple * new_parsed_couple = (parsed_couple*) malloc( sizeof(parsed_couple) );
	parsed_couple_parse( new_parsed_couple, token );
	return new_parsed_couple;
}

void                    
parsed_couple_free( parsed_couple ** pp_parsed_couple )
{
	sn_free( (void**) pp_parsed_couple );
}

void                    
parsed_couple_parse( parsed_couple * p_couple, const char* token)
{
	char *point = NULL;

	if ( p_couple == NULL )
		return;

	if (( point = strchr( token, '.' )) != NULL )
	{
		char * colon = NULL;
		char * other_point = NULL;
		other_point = strchr( point + 1, '.' );

		if ( point-token+1<sizeof(p_couple->type))
		{
			strncpy( p_couple->type, token, point - token );
			p_couple->type[ point - token ] = 0;	
		}
		if (( colon = strchr( point+1, ':')) != NULL )
		{
			int how_much = sizeof( p_couple->literal );
			if ( other_point != NULL && other_point-colon-1<how_much)
				how_much = other_point-colon-1;

			if ( colon - point < sizeof( p_couple->instance ) )
			{
				strncpy( p_couple->instance, point+1, colon - point - 1 );
				p_couple->instance[ colon - point - 1 ] = 0;
			}

			strncpy( p_couple->literal, colon+1, how_much );
			if ( how_much < sizeof( p_couple->literal ) )
				p_couple->literal[ how_much ] = 0;
		}
		else
		{
			int how_much = sizeof( p_couple->instance );
			if ( other_point != NULL && other_point-point-1<how_much)
				how_much = other_point-point-1;

			strncpy( p_couple->instance, point + 1, how_much ); 		
			if ( how_much < sizeof( p_couple->instance)  )
				p_couple->instance[ how_much ] = 0;
			p_couple->literal[0] = 0;
		}
	}
	else
	{
		
		strncpy( p_couple->type, token, sizeof( p_couple->type ) );
		p_couple->instance[0] = 0; 		
		p_couple->literal[0] = 0;
	}

}

void                    
parsed_couple_print( parsed_couple * p_couple )
{
	if ( p_couple != NULL )
	{
		printf( "[PC] T:\"%s\" I:\"%s\" L:\"%s\"\n", p_couple->type, p_couple->instance, p_couple->literal );
	}
}
