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

#ifndef BLOCK_NET_H
#define BLOCK_NET_H

#include <set.h>
#include <parsed_building_block.h>

typedef struct _block_net
{
	set * parsed_blocks; /* hash will be better */
	set * inputs;
	parsed_building_block * root;

	char * name;
} block_net;

block_net*		block_net_create( const char * name );
void			block_net_free( block_net ** pp_block_net );

void			block_net_add_parsed_block( block_net * net, parsed_building_block * block );
parsed_building_block*	block_net_get_parsed_block( block_net * net, const char * name );

void 			block_net_calculate_inputs( block_net * net );
code_chunk*		block_net_generate_code( block_net * net );

#endif
