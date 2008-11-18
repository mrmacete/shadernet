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

#ifndef SC_MATH_H
#define SC_MATH_H

#define CLAMP( val, min, max )  (val<min)?min:((val>max)?max:val)
#define SATURATE( val )  (val<0)?-1:((val>0)?1:0)
#define MAX( x, y ) (x>y)?x:y
#define MIN( x, y ) (x<y)?x:y

typedef struct 
{
	float * values;
	int w;
	int h;
	float **cols;
} matrix;

/* matrix functions */
matrix *	matrix_create(int rows, int cols);
void		matrix_free( matrix ** p_matrix );
void		matrix_set_identity( matrix * p_matrix );
void		matrix_print( matrix * p_matrix );

#endif
