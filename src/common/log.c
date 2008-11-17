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
