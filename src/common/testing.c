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

#include "testing.h"
#include "log.h"
#include <stdio.h>

static test_output _test_output = TEST_OUTPUT_NOT_PASSED;

test_result 
test_assert_true( int expression, const char * test_name )
{
	if ( expression )
	{
		if ( _test_output == TEST_OUTPUT_BOTH || _test_output == TEST_OUTPUT_PASSED )
		{
			if ( test_name )
				printf( "TEST %s PASSED\n", test_name );
			else
				printf( "TEST PASSED\n" );
		}
		return TEST_PASSED;
	}
	else
	{
		if ( _test_output == TEST_OUTPUT_BOTH || _test_output == TEST_OUTPUT_NOT_PASSED )
		{
			if ( test_name )
				printf( "TEST %s NOT PASSED\n", test_name );
			else
				printf( "TEST NOT PASSED\n" );
		}
		return TEST_NOT_PASSED;

	}
}

void            
test_set_output( test_output output )
{
	_test_output = output;
}
