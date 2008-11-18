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

#include "sn_math.h"
#include "testing.h"

static char _module_name[] = "TEST_SN_MATH";
int main( int argc, char *argv[] )
{

	test_set_output( TEST_OUTPUT_BOTH );

	test_assert_true( (CLAMP( 3, 0, 1 )) == 1, "clamp up" );
        test_assert_true( (CLAMP( -2, 0, 1 )) == 0, "clamp down" );
        test_assert_true( (CLAMP( 1, 0, 1 )) == 1, "clamp equal up" );
        test_assert_true( (CLAMP( 0, 0, 1 )) == 0, "clamp equal down" );

	matrix * the_matrix = matrix_create(4,4);
	matrix_print( the_matrix );
	matrix_free( &the_matrix );
	exit(0);
}
