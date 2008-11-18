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
#include <testing.h>
#include <sn_math.h>
#include <sn_memory.h>

#include "block_pin.h"
#include "block_pin_set.h"

int main( int argc, char *argv[] )
{
	block_pin_set * pin_set = NULL;
	block_pin *a=NULL, *b=NULL, *c=NULL;

	test_set_output( TEST_OUTPUT_NOT_PASSED );
	
	/* build tested objects */
	pin_set = block_pin_set_create();
	a = block_pin_create( "rotationMatrix", GLSL_TYPE_MAT3 );
	b = block_pin_create( "bloomFactor", GLSL_TYPE_FLOAT );	
	c = block_pin_create( "blurRadius", GLSL_TYPE_INT );	
	
	block_pin_set_add( pin_set, a );
	block_pin_set_add( pin_set, b );
	block_pin_set_add( pin_set, c );
	test_assert_true( pin_set->pin_set.size == 3, "pin set add test" );

	test_assert_true( block_pin_set_contains( pin_set, c ), "pin set contains test" );
	
	test_assert_true( block_pin_set_by_name( pin_set, "bloomFactor" ) == b, "pin set by name test" );

	/* destroy tested objects */
	block_pin_set_free( &pin_set );
	test_assert_true( pin_set == NULL, "block pin set free test" ); 

	exit(0);
}
