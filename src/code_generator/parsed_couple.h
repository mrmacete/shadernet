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

#ifndef PARSED_COUPLE_H
#define PARSED_COUPLE_H

#define PARSER_WORD 50

typedef struct {
	char type[PARSER_WORD];
	char instance[PARSER_WORD];
	char literal[PARSER_WORD];
} parsed_couple;

parsed_couple *		parsed_couple_create(const char* token);
void			parsed_couple_free( parsed_couple ** pp_parsed_couple );
void			parsed_couple_parse( parsed_couple * p_couple, const char* token);
void 			parsed_couple_print( parsed_couple * p_couple );


#endif
