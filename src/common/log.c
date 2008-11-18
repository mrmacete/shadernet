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

#include "log.h"
#include <stdio.h>

static log_level _log_level = LOG_LEVEL_DEBUG;

void 
LOG_ERROR( const char * module_name, const char * message )
{
	if ( _log_level > LOG_LEVEL_ERROR )
		return;

	if ( module_name != NULL && message != NULL)
		printf( "[%s] ERROR: %s\n", module_name, message );
	else if ( module_name == NULL && message != NULL )
		printf( "[GLOBAL] ERROR: %s\n", message );
	else if ( module_name != NULL && message == NULL )
		printf( "[%s] ERROR\n", module_name );
	else if ( module_name == NULL && message == NULL )
		printf( "[GLOBAL] ERROR: UNKNOWN\n" );
}

void LOG_DEBUG( const char * module_name, const char * message )
{
	if ( _log_level > LOG_LEVEL_DEBUG )
		return;

	if ( module_name != NULL && message != NULL)
		printf( "[%s] DEBUG: %s\n", module_name, message );
	else if ( module_name == NULL && message != NULL )
		printf( "[GLOBAL] DEBUG: %s\n", message );
}

void LOG_SET_LEVEL( log_level level )
{
	_log_level = level;
}
