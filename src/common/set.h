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

#ifndef SET_H
#define SET_H

typedef struct _set_element 
{
	void * data;
	struct _set_element * prev;
	struct _set_element * next;
} set_element;

typedef struct _set
{
	int size;
	set_element * head;
	set_element * tail;
} set;

typedef enum { 	ELEMENTS_INVALID,
		ELEMENTS_EQUAL,
		ELEMENTS_DIFFER,
		ELEMENTS_COMPATIBLE
		} compare_result;

typedef enum { 	ERROR,
		SUCCESS
		} generic_result;

generic_result	set_push_element( set * p_set, void * p_data );
set_element *	set_pop_element( set * p_set );
set_element * 	set_get_element_at ( set * p_set, int index );	
set_element * 	set_element_create( void * p_data );
void		set_element_free( set_element ** p_element );
int 		set_contains( set * p_set, void * p_data, compare_result (*compare)(void * p_data1, void * p_data2) );
set * 		set_create();
void		set_free( set ** p_set );
void 		set_soft_free( set ** p_set );

#define set_add_element set_push_element

#endif
