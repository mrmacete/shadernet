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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sn_memory.h>
#include <set.h>
#include <log.h>

#include "bookmark_set.h"

static const char _module_name[] = "BOOKMARK_SET";

void		
bookmark_set_add( bookmark_set * p_set,  parsing_bookmark * bookmark )
{
	if ( p_set == NULL || bookmark == NULL )
		return;
	
	if ( set_add_element( &p_set->_set, (void *) bookmark ) != SUCCESS )
	{
		LOG_ERROR( _module_name, "could not add element" );
	}
}

bookmark_set * 
bookmark_set_create()
{
	bookmark_set * p_set = malloc( sizeof( bookmark_set) );
	p_set->_set.head = NULL;
	p_set->_set.size = 0;
	return p_set;	
}

void            
bookmark_set_free( bookmark_set ** p_set )
{
	if ( p_set != NULL && (*p_set) != NULL )
	{
		while( (*p_set)->_set.size > 0 )
		{
			set_element * to_be_deleted = set_pop_element( &(*p_set)->_set );
			if ( to_be_deleted != NULL )
			{
				parsing_bookmark_free( (parsing_bookmark**) &(to_be_deleted->data) );
				set_element_free( &to_be_deleted );
			}
		}
		sn_free( (void**) p_set );
	}
}

void            
bookmark_set_print( bookmark_set * p_set )
{
	set_element * el = NULL;

	if ( p_set == NULL )
		return;
	
	el = p_set->_set.head;

	while ( el!=NULL )
	{
		parsing_bookmark_print( (parsing_bookmark*) el->data );
		el = el->next;
	}
}
