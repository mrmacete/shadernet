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

#include "parsed_building_block.h"

int main( int argc, char*argv[] )
{
	building_block * block = NULL;
	block_pin *color_a=NULL, *color_b=NULL, *color_out=NULL;
	block_parameter *param=NULL;
	const char * code = "#if ( $params.function == $params.function:multiply )\n$outputs.colorOutput = $inputs.colorA.rgb * $inputs.colorB;\n#endif\nif ( $i == 0 )\n$outputs.invalid = 2;\n$o = vec4(0.0);$notype.noinstance++;";
	code_chunk * xml_code = NULL;
	parsed_building_block *parsed_block=NULL;

	test_set_output( TEST_OUTPUT_NOT_PASSED );
		
	block = building_block_create( "ColorBlend" );

	color_a = block_pin_create( "colorA", GLSL_TYPE_VEC4 );
	color_b = block_pin_create( "colorB", GLSL_TYPE_VEC4 );
	color_out = block_pin_create( "colorOutput", GLSL_TYPE_VEC4 );

	param = block_parameter_create( "function" );

	block_pin_set_add( block->inputs, color_a );
	block_pin_set_add( block->inputs, color_b );
	block_pin_set_add( block->outputs, color_out );
	
	block_parameter_set_add( block->params, param );

	code_chunk_add_code( block->code, code, strlen(code) );

	xml_code = building_block_to_xml( block );

	code_chunk_print( xml_code, 0 );
	code_chunk_free( &xml_code );

	parsed_block = parsed_building_block_create( block, "ColorBlend1" );
	
	test_assert_true( parsed_block->undefined_references == 2, "parsed block undefined references" );
	test_assert_true( parsed_block->invalid_types == 1, "parsed block invalid types" );
		
	bookmark_set_print( parsed_block->bookmarks );

	parsed_building_block_free( &parsed_block );	


	exit(0);
} 
