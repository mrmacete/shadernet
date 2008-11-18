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

#ifndef BLOCK_PIN_SET_H
#define BLOCK_PIN_SET_H

#include "set.h"
#include "block_pin.h"

struct _building_block;

typedef struct _block_pin_set
{
	char * name;
	set pin_set;
	struct _building_block * p_parent;

} block_pin_set;

block_pin_set * block_pin_set_create	();
void		block_pin_set_free	( block_pin_set ** p_set );

block_pin_set * block_pin_set_clone	( block_pin_set * p_src );

int 		block_pin_set_contains	( block_pin_set * p_set, block_pin * pin );
void 		block_pin_set_add	( block_pin_set * p_set, block_pin * pin );
block_pin*	block_pin_set_by_name	( block_pin_set * p_set, const char *name );

void		block_pin_set_set_name( block_pin_set * p_set, const char *name );

#endif
