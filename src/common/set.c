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

#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include "sn_memory.h"
#include "log.h"

static char _module_name[] = "SET";

generic_result
set_push_element( set * p_set, void * p_data )
{
	set_element * last_element = NULL, *new_element = NULL;

	if ( p_set == NULL )
		return ERROR;

	if ( p_data == NULL )
		return SUCCESS;

	last_element = p_set->head;
	while( last_element != NULL && last_element->next != NULL )
	{
		last_element = last_element->next;
	}


	new_element = set_element_create( p_data );

	if ( last_element == NULL )
	{
		/* adding the first element */
		p_set->head = new_element;
	}
	else
	{
		last_element->next = new_element;
	}

	new_element->prev = last_element;;	

	p_set->tail = new_element;
	
	p_set->size++;

	return SUCCESS;

	
}

set_element *   
set_element_create( void * p_data )
{
	set_element * new_element = NULL;

	new_element = (set_element*) malloc( sizeof( set_element ) );
        new_element->data = p_data;
        new_element->next = NULL;
        new_element->prev = NULL;
	
	return new_element;
}

set_element *
set_pop_element( set * p_set )
{
	if ( p_set == NULL )
		return NULL;
	
	if ( p_set->tail != NULL && p_set->size > 0 )
	{
		set_element * result = p_set->tail;
		p_set->tail = p_set->tail->prev;
		p_set->size--;
		
		return result; 
	}

	return NULL;
}


set_element *   
set_get_element_at ( set * p_set, int index )
{
	set_element * el = NULL;
	int pos = 0;

	if ( p_set == NULL || index >= p_set->size )
		return NULL;
	
	if ( index < p_set->size / 2 || p_set->size <= 2)
	{
		/* start searching from head */
		el = p_set->head;
		while( pos < index && el != NULL )
		{
			el = el->next;	
			pos++;
		}
	}
	else
	{
		/* start searching from tail */
		el = p_set->tail;
		pos = p_set->size-1;
		while( pos >= index && el != NULL )
		{
			el = el->prev;
			pos--;
		}
	}

	return el;		
	
}

int             
set_contains( set * p_set, void * p_data, compare_result (*compare)(void * p_data1, void * p_data2) )
{
	set_element * el = NULL;
        int pos = 0;

	if ( p_set == NULL )
	{
		LOG_DEBUG( _module_name, "NULL sets contains nothing" );
		return 0;
	}

	if ( p_data == NULL )
	{
		LOG_DEBUG( _module_name, "NULL data is contained nowhere" );
		return 0;
	}

	el = p_set->head;
        do{
		if ( el != NULL )
		{
			if ( compare( el->data, p_data ) == ELEMENTS_EQUAL )
				return 1;	

	                el = el->next;  
		}
                pos++;
        }while( pos < p_set->size && el != NULL );

	LOG_DEBUG( _module_name, "set does not contain desired data" );
	return 0;
}

set *           
set_create()
{
	set * new_set = ( set * ) malloc( sizeof( set ) );
	new_set->head = NULL;
	new_set->tail = NULL;
	new_set->size = 0;
	return new_set;
}

void
set_free( set ** p_set )
{
	if ( p_set != NULL && (*p_set) != NULL )
	{
		while( (*p_set)->size > 0 )
		{
			set_element * to_be_deleted = set_pop_element( (*p_set) );
			set_element_free( &to_be_deleted );
		}

		sn_free( (void**) p_set );
	}
}

void
set_soft_free( set ** p_set )
{
        if ( p_set != NULL && (*p_set) != NULL )
        {
                while( (*p_set)->size > 0 )
                {
                        set_element * to_be_deleted = set_pop_element( (*p_set) );
			sn_free( (void**) &to_be_deleted );
                }

                sn_free( (void**) p_set );
        }
}

void            
set_element_free( set_element ** p_element )
{
	if ( p_element != NULL && (*p_element) != NULL )
	{
		sn_free( (void**) &(*p_element)->data );
		sn_free( (void**) p_element );
	}
}

