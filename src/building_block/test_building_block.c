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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <testing.h>

#include "building_block.h"

int main( int argc, char*argv[] )
{
	building_block * block = NULL;
	block_pin *color_a=NULL, *color_b=NULL, *color_out=NULL;
	const char * code = "$outputs.colorOutput = $inputs.colorA * $inputs.colorB;";
	code_chunk * xml_code = NULL;

	test_set_output( TEST_OUTPUT_NOT_PASSED );
		
	block = building_block_create( "ColorBlend" );

	color_a = block_pin_create( "colorA", GLSL_TYPE_VEC4 );
	color_b = block_pin_create( "colorB", GLSL_TYPE_VEC4 );
	color_out = block_pin_create( "colorOutput", GLSL_TYPE_VEC4 );

	block_pin_set_add( block->inputs, color_a );
	block_pin_set_add( block->inputs, color_b );
	block_pin_set_add( block->outputs, color_out );

	code_chunk_add_code( block->code, code, strlen(code) );

	xml_code = building_block_to_xml( block );

	code_chunk_print( xml_code, 0 );
	code_chunk_free( &xml_code );

	building_block_free( &block );

	test_assert_true( block == NULL , "building block free test" );

	exit(0);
} 
