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

#include "block_net.h"
#include <building_block.h>


#include <testing.h>
#include <sn_memory.h>
#include <sn_config.h>
#include <set.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct block_instance
{
	building_block * block;
	int refcount;
} block_instance;

block_instance* block_instance_create( building_block * block );

void load_base_blocks( set * block_set );

building_block* create_ColorBlend();
building_block* create_glTexCoord();
building_block* create_texture2D();
building_block* create_glFrontMaterial();
building_block* create_StdOut();

void instance_and_parse( block_net * net, set * base_blocks );
block_instance* get_base_block( set * base_blocks, const char * name );
parsed_building_block* instance_block( set* base_blocks, const char * base_name, const char * parsed_name );
void connect_parsed_blocks( block_net * net );

int main( int argc, char * argv[] )
{
	block_net * net = NULL;
	set * base_blocks = NULL;
	code_chunk * code = NULL;

	test_set_output( TEST_OUTPUT_NOT_PASSED );

	net = block_net_create( "MultiBlend" );
	base_blocks = set_create();

	load_base_blocks( base_blocks );
	instance_and_parse( net, base_blocks );

	set_free( &base_blocks );

	connect_parsed_blocks( net );

	code = block_net_generate_code( net );
	code_chunk_print( code, 1 );

	code_chunk_free( &code );

	block_net_free( &net );

	exit(0);
}

void 
load_base_blocks( set * block_set )
{
	set_push_element( block_set, block_instance_create( create_ColorBlend()) );
	set_push_element( block_set, block_instance_create( create_glTexCoord()) );
	set_push_element( block_set, block_instance_create( create_texture2D()) );
	set_push_element( block_set, block_instance_create( create_glFrontMaterial()) );
	set_push_element( block_set, block_instance_create( create_StdOut()) );
}

void
instance_and_parse( block_net * net, set * base_blocks )
{
	parsed_building_block * pblock = instance_block( base_blocks, "glTexCoord", "texCoord0" );
	if ( pblock != NULL )
	{
		block_parameter * param = block_parameter_set_by_name( pblock->p_block->params, "channel" );
		block_parameter_set_string_value( param, "0", 1 );
	}

	block_net_add_parsed_block( net, pblock );

	pblock = instance_block( base_blocks, "texture2D", "diffuseTexture" );
	block_net_add_parsed_block( net, pblock );

	
	pblock = instance_block( base_blocks, "texture2D", "occlusionTexture" );
	block_net_add_parsed_block( net, pblock );

	pblock = instance_block( base_blocks, "glFrontMaterial", "glFrontMaterial" );
	block_net_add_parsed_block( net, pblock );

	
	pblock = instance_block( base_blocks, "ColorBlend", "ColorBlend1" );
	if ( pblock != NULL )
	{
		block_parameter * param = block_parameter_set_by_name( pblock->p_block->params, "function" );
		block_parameter_set_string_value( param, "multiply", 8 );
	}
	block_net_add_parsed_block( net, pblock );

	pblock = instance_block( base_blocks, "ColorBlend", "ColorBlend2" );
	if ( pblock != NULL )
	{
		block_parameter * param = block_parameter_set_by_name( pblock->p_block->params, "function" );
		block_parameter_set_string_value( param, "multiply", 8 );
	}
	block_net_add_parsed_block( net, pblock );

	pblock = instance_block( base_blocks, "StdOut", "StdOut" );
	block_net_add_parsed_block( net, pblock );

}

void 
connect_parsed_blocks(block_net * net)
{
	parsed_building_block * block = NULL;
	if ( net == NULL )
		return;

	block = block_net_get_parsed_block( net, "texCoord0" );

	if ( block )
	{
		block_pin * source = block_pin_set_by_name( block->p_block->outputs, "coord" );
		
		block = block_net_get_parsed_block( net, "diffuseTexture" );
		if ( block )
		{
			block_pin * dest = block_pin_set_by_name( block->p_block->inputs, "uv" );
			block_pin_connect( source, dest );
		}

		block = block_net_get_parsed_block( net, "occlusionTexture" );
		if ( block )
		{
			block_pin * dest = block_pin_set_by_name( block->p_block->inputs, "uv" );
			block_pin_connect( source, dest );
		}
	}


	block = block_net_get_parsed_block( net, "diffuseTexture" );
	if ( block )
	{
		block_pin * source = block_pin_set_by_name( block->p_block->outputs, "rgba" );
		block = block_net_get_parsed_block( net, "ColorBlend1" );
		if ( block )
		{
			block_pin * dest = block_pin_set_by_name( block->p_block->inputs, "colorA" );
			block_pin_connect( source, dest );
		}
		
	}

	block = block_net_get_parsed_block( net, "occlusionTexture" );
	if ( block )
	{
		block_pin * source = block_pin_set_by_name( block->p_block->outputs, "rgba" );
		block = block_net_get_parsed_block( net, "ColorBlend2" );
		if ( block )
		{
			block_pin * dest = block_pin_set_by_name( block->p_block->inputs, "colorB" );
			block_pin_connect( source, dest );
		}
	}		
	
	block = block_net_get_parsed_block( net, "glFrontMaterial" );
	if ( block )
	{
		block_pin * source = block_pin_set_by_name( block->p_block->outputs, "diffuse" );
		block = block_net_get_parsed_block( net, "ColorBlend1" );
		if ( block )
		{
			block_pin * dest = block_pin_set_by_name( block->p_block->inputs, "colorB" );
			block_pin_connect( source, dest );
		}
	}		
	
	block = block_net_get_parsed_block( net, "ColorBlend1" );
	if ( block )
	{
		block_pin * source = block_pin_set_by_name( block->p_block->outputs, "colorOutput" );
		block = block_net_get_parsed_block( net, "ColorBlend2" );
		if ( block )
		{
			block_pin * dest = block_pin_set_by_name( block->p_block->inputs, "colorA" );
			block_pin_connect( source, dest );
		}
	}		
	
	block = block_net_get_parsed_block( net, "ColorBlend2" );
	if ( block )
	{
		block_pin * source = block_pin_set_by_name( block->p_block->outputs, "colorOutput" );
		block = block_net_get_parsed_block( net, "StdOut" );
		if ( block )
		{
			block_pin * dest = block_pin_set_by_name( block->p_block->inputs, "color" );
			block_pin_connect( source, dest );
		}
	}		

	
	net->root = block_net_get_parsed_block( net, "StdOut" );

	block_net_calculate_inputs( net );
	
}

parsed_building_block* 
instance_block( set* base_blocks, const char * base_name, const char * parsed_name )
{
	block_instance * bi = NULL;

	bi = get_base_block( base_blocks, base_name );
	if ( bi != NULL )
	{
		parsed_building_block* parsed = NULL;

		if ( bi->refcount > 0 )
		{
			parsed = parsed_building_block_create( building_block_clone( bi->block ), parsed_name );
		}
		else
		{
			parsed = parsed_building_block_create( bi->block, parsed_name );
		}
	
		bi->refcount++;	

		return parsed;
	}	

	return NULL;
}

block_instance*
block_instance_create( building_block * block )
{
	block_instance * instance = (block_instance*) malloc( sizeof( block_instance ) );
	instance->block = block;
	instance->refcount = 0;
	return instance;
}

block_instance *
get_base_block( set * base_blocks, const char * name )
{
	set_element * el = base_blocks->head;
	while ( el != NULL )
	{
		building_block * block = (building_block*)( (block_instance*) el->data )->block;
		if ( block != NULL && strncmp( block->name, name, NAME_LENGTH ) == 0 )
			return (block_instance*) el->data;
		el = el->next;
	}

	return NULL;
}

building_block* 
create_ColorBlend()
{
	building_block * block = NULL;
        block_pin *color_a=NULL, *color_b=NULL, *color_out=NULL;
        block_parameter *param=NULL;
	const char * code =
"#if ( $params.function == $params.function:multiply )\n\
	$o = $i.colorA * $i.colorB;\n\
#elif ( $params.function == $params.function:add )\n\
	$o = $i.colorA + $i.colorB;\n\
#endif\n\
";
	block = building_block_create( "ColorBlend" );

        color_a = block_pin_create( "colorA", GLSL_TYPE_VEC4 );
        color_b = block_pin_create( "colorB", GLSL_TYPE_VEC4 );
        color_out = block_pin_create( "colorOutput", GLSL_TYPE_VEC4 );

        param = block_parameter_create( "function" );
	block_parameter_add_literal( param, "multiply", 8, 0 );
	block_parameter_add_literal( param, "add", 3, 1 );

        block_pin_set_add( block->inputs, color_a );
        block_pin_set_add( block->inputs, color_b );
        block_pin_set_add( block->outputs, color_out );

        block_parameter_set_add( block->params, param );

        code_chunk_add_code( block->code, code, strlen(code) );
	code_chunk_prune_unused( block->code );
	
	return block;
}

building_block* 
create_glTexCoord()
{
	building_block * block = NULL;
	const char * code =
"$o = glTexCoord[channel];";

	block = building_block_create( "glTexCoord" );
        code_chunk_add_code( block->code, code, strlen(code) );
	code_chunk_prune_unused( block->code );
	block_parameter_set_add( block->params, block_parameter_create( "channel" ) );
	block_pin_set_add( block->outputs, block_pin_create( "coord", GLSL_TYPE_VEC4 ) );

	return block;
}

building_block* 
create_texture2D()
{
	building_block * block = NULL;
	const char * code = "$o = texture2d( $inputs.texture, $inputs.uv.uv );";

        block = building_block_create( "texture2D" );

        code_chunk_add_code( block->code, code, strlen(code) );
	code_chunk_prune_unused( block->code );

	block_pin_set_add( block->inputs, block_pin_create( "texture", GLSL_TYPE_SAMPLER2D ) );
	block_pin_set_add( block->inputs, block_pin_create( "uv", GLSL_TYPE_VEC2 ) );
	block_pin_set_add( block->outputs, block_pin_create( "rgba", GLSL_TYPE_VEC4 ) );

        return block;
}

building_block* 
create_glFrontMaterial()
{
	building_block * block = NULL;
	const char * code =
"$outputs.emission = gl_FrontMaterial.emission;\n\
$outputs.ambient = gl_FrontMaterial.ambient;\n\
$outputs.diffuse = gl_FrontMaterial.diffuse;\n\
$outputs.specular = gl_FrontMaterial.specular;\n\
$outputs.shininess = gl_FrontMaterial.shininess;\n\
";

        block = building_block_create( "glFrontMaterial" );

        code_chunk_add_code( block->code, code, strlen(code) );
	code_chunk_prune_unused( block->code );

	block_pin_set_add( block->outputs, block_pin_create( "emission", GLSL_TYPE_VEC4 ) );
	block_pin_set_add( block->outputs, block_pin_create( "ambient", GLSL_TYPE_VEC4 ) );
	block_pin_set_add( block->outputs, block_pin_create( "diffuse", GLSL_TYPE_VEC4 ) );
	block_pin_set_add( block->outputs, block_pin_create( "specular", GLSL_TYPE_VEC4 ) );
	block_pin_set_add( block->outputs, block_pin_create( "shininess", GLSL_TYPE_FLOAT ) );

        return block;
}

building_block* 
create_StdOut()
{
	building_block * block = NULL;
	const char * code =
"gl_FragColor = $i.color;\n\
gl_FragDepth = $i.depth;\n\
";

        block = building_block_create( "StdOut" );

        code_chunk_add_code( block->code, code, strlen(code) );
	code_chunk_prune_unused( block->code );

	block_pin_set_add( block->inputs, block_pin_create( "color", GLSL_TYPE_VEC4 ) );
	block_pin_set_add( block->inputs, block_pin_create( "depth", GLSL_TYPE_VEC4 ) );

        return block;
}
