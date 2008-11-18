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

#ifndef PARSED_BUILDING_BLOCK
#define PARSED_BUILDING_BLOCK

#include <building_block.h>
#include "bookmark_set.h"

typedef struct _parsed_building_block
{
	building_block * p_block;
	bookmark_set * bookmarks;
	int undefined_references;
	int invalid_types;	
	char * name;
} parsed_building_block;

parsed_building_block*	parsed_building_block_create( building_block * p_block, const char * name );
void			parsed_building_block_free( parsed_building_block ** pp_parsed_building_block );

#endif
