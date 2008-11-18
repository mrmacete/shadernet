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

#include "block_pin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <log.h>
#include <sn_memory.h>
#include <sn_math.h>
#include <sn_config.h>


static char _module_name[] = "BLOCK_PIN";

/*static int (*compare_table[31]) (void * p_value1, void* p_value2) = { NULL };
static void (*free_table[31]) (void ** p_value) = { NULL };
static void init_compare_table();
static void init_free_table();
static int compare_table_inited = 0;
static int free_table_inited = 0;

static int compare_glsl_int( void *p_value1, void *p_value2 );
static int compare_glsl_float( void *p_value1, void *p_value2 );
static int compare_glsl_float_vec( void *p_value1, void *p_value2, int n );
static int compare_glsl_int_vec( void *p_value1, void *p_value2, int n );
static int compare_glsl_vec2( void *p_value1, void *p_value2 );
static int compare_glsl_vec3( void *p_value1, void *p_value2 );
static int compare_glsl_vec4( void *p_value1, void *p_value2 );
*/
void block_pin_free( block_pin ** p_pin )
{
	if ( p_pin != NULL && *p_pin != NULL )
	{
		sn_free( (void**) &(*p_pin)->name );
		sn_free( (void**) p_pin );
	} 
}

block_pin * block_pin_create( const char * name, glsl_type type )
{
	block_pin *pin = malloc( sizeof( block_pin ) );
	pin->name = (char *) malloc( NAME_LENGTH * sizeof( char ) );
	if ( name != NULL )
		pin->name = strncpy( pin->name, name, NAME_LENGTH ); 

	pin->type = type;

	pin->p_parent = NULL;
	pin->source = NULL;
	
	return pin;
}

block_pin * 
block_pin_clone( block_pin * p_src )
{
	if ( p_src != NULL )
	{
		block_pin *pin = (block_pin*) malloc( sizeof( block_pin ) );
		pin->name = (char *) malloc( NAME_LENGTH * sizeof( char ) );
		if ( p_src->name != NULL )
			pin->name = strncpy( pin->name, p_src->name, NAME_LENGTH ); 
	
		pin->type = p_src->type;
		pin->p_parent = NULL;
		pin->source = NULL;
	
		return pin;
	}

	return NULL;
	
}

void 
block_pin_connect( block_pin * source, block_pin * drain )
{
	if ( source == NULL )
	{
		LOG_ERROR( _module_name, "block_pin connect: NULL source" );
		return;
	}

	if ( drain == NULL )
	{
		LOG_ERROR( _module_name, "block_pin connect: NULL drain" );
		return;
	}

	drain->source = source;
}

/*
int block_pin_compare_value( block_pin * p_left, block_pin * p_right )
{
	if ( p_left == NULL || p_right == NULL )
	{
		LOG_DEBUG( _module_name, "compare: there are NULL input pins" );
		return 3;
	}

	if ( p_left->type == p_right->type )
	{
		if ( p_left->type < 31 )
		{
			if ( !compare_table_inited )
			{
				LOG_DEBUG( _module_name, "initing compare table" );
				init_compare_table();
			}

			if (  compare_table[ p_left->type ] == NULL )
			{
				
				return 5;
			}
			return	(*compare_table[ p_left->type ])( p_left->value, p_right->value );
		}
		else
		{
			LOG_ERROR( _module_name, "invalid type in pin value comparison" );
			return 4;
		}
			
	}
	else
	{
		LOG_DEBUG( _module_name, "compare: different types" );
		return 2;
	}
}

static int compare_glsl_int( void *p_value1, void *p_value2 )
{
	int val1, val2;
	val1 =  *((int*) p_value1 );
	val2 =  *((int*) p_value2 );
	return CLAMP( val1 - val2, -1, 1 ); 
}

static int compare_glsl_float( void *p_value1, void *p_value2 )
{
	float val1, val2;

	val1 =  *((float*) p_value1 );
	val2 =  *((float*) p_value2 );
	return SATURATE( val1 - val2 );
}

static int compare_glsl_float_vec( void *p_value1, void *p_value2, int n )
{
	int i = 0;
	int result = 1;
	for( i=0; i<n ; i++)
	{
		result = result && (compare_glsl_float( ((float*)p_value1)+i, ((float*)p_value2)+i ) == 0);
		if ( !result )
			return -1;
	}
		
	return 0;
}

static int compare_glsl_int_vec( void *p_value1, void *p_value2, int n )
{
	int i = 0;
	int result = 1;
	for( i=0; i<n ; i++)
	{
		result &= compare_glsl_int( ((int*)p_value1)+i, ((int*)p_value2)+i ) == 0;
		if ( !result )
			return 0;
	}
		
	return result;
}

static int compare_glsl_vec2( void *p_value1, void *p_value2 )
{
	return compare_glsl_float_vec( p_value1, p_value2, 2 );
}

static int compare_glsl_vec3( void *p_value1, void *p_value2 )
{
	return compare_glsl_float_vec( p_value1, p_value2, 3 );
}

static int compare_glsl_vec4( void *p_value1, void *p_value2 )
{
	return compare_glsl_float_vec( p_value1, p_value2, 4 );
}

static int compare_glsl_ivec2( void *p_value1, void *p_value2 )
{
	return compare_glsl_int_vec( p_value1, p_value2, 2 );
}

static int compare_glsl_ivec3( void *p_value1, void *p_value2 )
{
	return compare_glsl_int_vec( p_value1, p_value2, 3 );
}

static int compare_glsl_ivec4( void *p_value1, void *p_value2 )
{
	return compare_glsl_int_vec( p_value1, p_value2, 4 );
}

static int compare_glsl_mat2( void *p_value1, void *p_value2 )
{
	return compare_glsl_float_vec( ((matrix*)p_value1)->values, ((matrix*)p_value2)->values, 4 );
}

static int compare_glsl_mat3( void *p_value1, void *p_value2 )
{
	return compare_glsl_float_vec( ((matrix*)p_value1)->values, ((matrix*)p_value2)->values, 9 );
}

static int compare_glsl_mat4( void *p_value1, void *p_value2 )
{
	return compare_glsl_float_vec( ((matrix*)p_value1)->values, ((matrix*)p_value2)->values, 16 );
}

static void scalar_value_free ( void ** p_value )
{
	sn_free( p_value );
}

static void matrix_value_free ( void ** p_value )
{
	matrix_free( (matrix**) p_value );
}


static void init_compare_table()
{
	memset( &compare_table, 0, 31 * sizeof( void* ) );

	compare_table[ GLSL_TYPE_INT ] = &compare_glsl_int;
	compare_table[ GLSL_TYPE_BOOL ] = &compare_glsl_int;
	compare_table[ GLSL_TYPE_FLOAT ] = &compare_glsl_float;
	compare_table[ GLSL_TYPE_HALF ] = &compare_glsl_float;
	compare_table[ GLSL_TYPE_VEC2 ] = &compare_glsl_vec2;
	compare_table[ GLSL_TYPE_VEC3 ] = &compare_glsl_vec3;
	compare_table[ GLSL_TYPE_VEC4 ] = &compare_glsl_vec4;
	compare_table[ GLSL_TYPE_IVEC2 ] = &compare_glsl_ivec2;
	compare_table[ GLSL_TYPE_IVEC3 ] = &compare_glsl_ivec3;
	compare_table[ GLSL_TYPE_IVEC4 ] = &compare_glsl_ivec4;
	compare_table[ GLSL_TYPE_BVEC2 ] = &compare_glsl_ivec2;
	compare_table[ GLSL_TYPE_BVEC3 ] = &compare_glsl_ivec3;
	compare_table[ GLSL_TYPE_BVEC4 ] = &compare_glsl_ivec4;
	compare_table[ GLSL_TYPE_MAT2 ] = &compare_glsl_mat2;
	compare_table[ GLSL_TYPE_MAT2X2 ] = &compare_glsl_mat2;
	compare_table[ GLSL_TYPE_MAT3 ] = &compare_glsl_mat3;
	compare_table[ GLSL_TYPE_MAT3X3 ] = &compare_glsl_mat3;
	compare_table[ GLSL_TYPE_MAT4 ] = &compare_glsl_mat4;
	compare_table[ GLSL_TYPE_MAT4X4 ] = &compare_glsl_mat4;

	compare_table_inited = 1;
}

static void init_free_table()
{

	memset( &free_table, 0, 31 * sizeof( void* ) );

	free_table[ GLSL_TYPE_INT ] = &scalar_value_free;
        free_table[ GLSL_TYPE_BOOL ] = &scalar_value_free;
        free_table[ GLSL_TYPE_FLOAT ] = &scalar_value_free;
        free_table[ GLSL_TYPE_HALF ] = &scalar_value_free;
        free_table[ GLSL_TYPE_MAT2 ] = &matrix_value_free;
        free_table[ GLSL_TYPE_MAT2X2 ] = &matrix_value_free;
        free_table[ GLSL_TYPE_MAT3 ] = &matrix_value_free;
        free_table[ GLSL_TYPE_MAT3X3 ] = &matrix_value_free;
        free_table[ GLSL_TYPE_MAT4 ] = &matrix_value_free;
        free_table[ GLSL_TYPE_MAT4X4 ] = &matrix_value_free;

	free_table_inited = 1;
}
*/
