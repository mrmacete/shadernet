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

#ifndef GLSL_TYPES_H
#define GLSL_TYPES_H
/* 
 * GLSL Basic Types
 * as from specification
 * The OpenGL Shading Language
 * version 1.20
 * revision 8
 * 07-sept-2006
 *
 * with addition of HALF extension
 */
typedef enum
{
        GLSL_TYPE_BOOL=0,
        GLSL_TYPE_INT,
        GLSL_TYPE_FLOAT,
        GLSL_TYPE_VEC4,
        GLSL_TYPE_VEC3,
        GLSL_TYPE_VEC2,
        GLSL_TYPE_BVEC4,
        GLSL_TYPE_BVEC3,
        GLSL_TYPE_BVEC2,
        GLSL_TYPE_IVEC4,
        GLSL_TYPE_IVEC3,
        GLSL_TYPE_IVEC2,
        GLSL_TYPE_MAT2,
        GLSL_TYPE_MAT3,
        GLSL_TYPE_MAT4,
        GLSL_TYPE_MAT2X2,
        GLSL_TYPE_MAT2X3,
        GLSL_TYPE_MAT2X4,
        GLSL_TYPE_MAT3X2,
        GLSL_TYPE_MAT3X3,
        GLSL_TYPE_MAT3X4,
        GLSL_TYPE_MAT4X2,
        GLSL_TYPE_MAT4X3,
        GLSL_TYPE_MAT4X4,
        GLSL_TYPE_SAMPLER1D,
        GLSL_TYPE_SAMPLER2D,
        GLSL_TYPE_SAMPLER3D,
        GLSL_TYPE_SAMPLERCUBE,
        GLSL_TYPE_SAMPLER1DSHADOW,
        GLSL_TYPE_SAMPLER2DSHADOW,
        GLSL_TYPE_HALF
} glsl_type;

char *	glsl_type_to_string( glsl_type type );

#endif
