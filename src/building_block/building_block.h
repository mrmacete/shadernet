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

#ifndef BUILDING_BLOCK_H
#define BUILDING_BLOCK_H

#include "code_chunk.h"

#include "block_parameter_set.h"
#include "block_pin_set.h"

typedef struct _building_block
{
	char * name;

	block_parameter_set *params;
	block_pin_set *inputs;
	block_pin_set *outputs;
	code_chunk * code; 
	struct _parsed_building_block * p_parsed;
} building_block;

building_block *	building_block_create(const char * name);
void 			building_block_free( building_block ** p_block );
code_chunk *		building_block_to_xml( building_block * p_block );
building_block *	building_block_clone( building_block * p_block );

#endif
