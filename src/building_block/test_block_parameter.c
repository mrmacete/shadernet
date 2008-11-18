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

#include "block_parameter.h"
#include <set.h>

#include <testing.h>
#include <sn_memory.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] )
{
	block_parameter * test_param = NULL;

	test_set_output( TEST_OUTPUT_NOT_PASSED );

	test_param = block_parameter_create( "function" );
	test_assert_true( test_param != NULL , "block parameter creation" );

	block_parameter_add_literal( test_param, "multiply", 8, 0 );
	block_parameter_add_literal( test_param, "add", 3, 1 );

	test_assert_true( test_param->literals->size == 2, "literals adding" );

	block_parameter_set_string_value( test_param, "test", 4 );
	test_assert_true( test_param->literal_value == -1, "set value outside literal" );

	block_parameter_set_string_value( test_param, "add", 3 );
	test_assert_true( test_param->literal_value == 1, "set value in literal 1" );
	
	block_parameter_set_string_value( test_param, "multiply", 8 );
	test_assert_true( test_param->literal_value == 0, "set value in literal 0" );
	
	block_parameter_free( &test_param );
	test_assert_true( test_param == NULL, "block parameter deletion" );

	exit(0);
}
