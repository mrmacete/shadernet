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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "glsl_types.h"

char *  
glsl_type_to_string( glsl_type type )
{
	char * result = NULL;

	result = (char*) malloc( 16 * sizeof(char));
	switch( type )
	{
		case GLSL_TYPE_BOOL:
			strncpy( result, "bool", 16 );
			break;
		case GLSL_TYPE_INT:
			strncpy( result, "int", 16 );
			break;
		case GLSL_TYPE_FLOAT:
			strncpy( result, "float", 16 );
			break;
		case GLSL_TYPE_VEC2:
			strncpy( result, "vec2", 16 );
			break;
		case GLSL_TYPE_VEC3:
			strncpy( result, "vec3", 16 );
			break;
		case GLSL_TYPE_VEC4:
			strncpy( result, "vec4", 16 );
			break;
		case GLSL_TYPE_IVEC2:
			strncpy( result, "ivec2", 16 );
			break;
		case GLSL_TYPE_IVEC3:
			strncpy( result, "ivec3", 16 );
			break;
		case GLSL_TYPE_IVEC4:
			strncpy( result, "ivec4", 16 );
			break;
		case GLSL_TYPE_BVEC2:
			strncpy( result, "bvec2", 16 );
			break;
		case GLSL_TYPE_BVEC3:
			strncpy( result, "bvec3", 16 );
			break;
		case GLSL_TYPE_BVEC4:
			strncpy( result, "bvec4", 16 );
			break;
		case GLSL_TYPE_MAT2:
			strncpy( result, "mat2", 16 );
			break;
		case GLSL_TYPE_MAT3:
			strncpy( result, "mat3", 16 );
			break;
		case GLSL_TYPE_MAT4:
			strncpy( result, "mat4", 16 );
			break;
		case GLSL_TYPE_MAT2X2:
			strncpy( result, "mat2X2", 16 );
			break;
		case GLSL_TYPE_MAT2X3:
			strncpy( result, "mat2X3", 16 );
			break;
		case GLSL_TYPE_MAT2X4:
			strncpy( result, "mat2X4", 16 );
			break;
		case GLSL_TYPE_MAT3X2:
			strncpy( result, "mat3X2", 16 );
			break;
		case GLSL_TYPE_MAT3X3:
			strncpy( result, "mat3X3", 16 );
			break;
		case GLSL_TYPE_MAT3X4:
			strncpy( result, "mat3X4", 16 );
			break;
		case GLSL_TYPE_MAT4X2:
			strncpy( result, "mat4X2", 16 );
			break;
		case GLSL_TYPE_MAT4X3:
			strncpy( result, "mat4X3", 16 );
			break;
		case GLSL_TYPE_MAT4X4:
			strncpy( result, "mat4X4", 16 );
			break;
		case GLSL_TYPE_SAMPLER1D:
			strncpy( result, "sampler1D", 16 );
			break;
		case GLSL_TYPE_SAMPLER2D:
			strncpy( result, "sampler2D", 16 );
			break;
		case GLSL_TYPE_SAMPLER3D:
			strncpy( result, "sampler3D", 16 );
			break;
		case GLSL_TYPE_SAMPLERCUBE:
			strncpy( result, "samplerCube", 16 );
			break;
		case GLSL_TYPE_SAMPLER1DSHADOW:
			strncpy( result, "sampler1DShadow", 16 );
			break;
		case GLSL_TYPE_SAMPLER2DSHADOW:
			strncpy( result, "sampler2DShadow", 16 );
			break;
		case GLSL_TYPE_HALF:
			strncpy( result, "half", 16 );
			break;
			
		default:
			strncpy( result, "unknown", 16 );
			break;
		
	}
	
	return result;
}
