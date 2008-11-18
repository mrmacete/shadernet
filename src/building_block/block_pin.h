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

#ifndef BLOCK_PIN_H
#define BLOCK_PIN_H

#include <glsl_types.h>

struct _block_pin_set;

typedef struct _block_pin
{
	char * name;
	glsl_type type;
	void * value;
	struct _block_pin_set *p_parent;
	struct _block_pin * source;
} block_pin;

void block_pin_free( block_pin ** p_pin );
block_pin * block_pin_create( const char * name, glsl_type type );
block_pin * block_pin_clone( block_pin * p_src );
/*int block_pin_compare_value( block_pin * p_left, block_pin * p_right );*/
void block_pin_connect( block_pin * source, block_pin * drain );

#endif
