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
