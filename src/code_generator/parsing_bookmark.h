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

#ifndef PARSING_BOOKMARK_H
#define PARSING_BOOKMARK_H

#include <block_pin.h>
#include <block_parameter.h>
#include "parsed_couple.h"

typedef enum { BOOKMARK_PIN, BOOKMARK_PARAM, BOOKMARK_INVALID } bookmark_type;

typedef union {
	block_pin * p_pin;
	block_parameter * p_param;
} association;

typedef struct {
	char * p_start;
	int length;
	bookmark_type type;
	association u_association;
	parsed_couple * p_couple;
} parsing_bookmark;

parsing_bookmark*	parsing_bookmark_create( char * p_start, int length, parsed_couple *p_couple );
void			parsing_bookmark_free( parsing_bookmark ** pp_parsing_bookmark );
void 			parsing_bookmark_print( parsing_bookmark * p_parsing_bookmark );
#endif
