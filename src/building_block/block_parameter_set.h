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

#ifndef BLOCK_PARAMETER_SET_H
#define BLOCK_PARAMETER_SET_H

#include "set.h"
#include "block_parameter.h"

struct _building_block;

typedef struct _block_parameter_set
{
	set parameter_set;
	struct _building_block * p_parent;

} block_parameter_set;

block_parameter_set * 	block_parameter_set_create();
void			block_parameter_set_free( block_parameter_set ** p_set );

block_parameter_set*	block_parameter_set_clone( block_parameter_set * p_src );

int 			block_parameter_set_contains 	( block_parameter_set *, block_parameter * parameter );
void 			block_parameter_set_add 	( block_parameter_set *, block_parameter * parameter );
block_parameter *	block_parameter_set_by_name 	( block_parameter_set *, const char * name );

#endif
