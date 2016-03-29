#include "sn_string.h"
#include "sn_memory.h"
#include "sn_math.h"
#include "log.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char _module_name[] = "SN_STRING";

sn_string *     
sn_string_create ( const char * c_str )
{
	sn_string * _string = (sn_string * ) malloc( sizeof( sn_string ) );
	if ( c_str != NULL )
	{
		_string->len = strlen( c_str );
		_string->buffer = (char *) malloc( _string->len * sizeof(char) );
		memcpy( _string->buffer, c_str, _string->len );
	}
	else
	{
		_string->len = 0;
		_string->buffer = NULL;
	}

	_string->is_ref = 0;

	return _string;
}

sn_string *     
sn_string_create_from_buffer( char * buffer, unsigned long int len )
{
	sn_string * _string = (sn_string*) malloc( sizeof( sn_string ) );
	if ( buffer != NULL && len > 0 )
	{
		_string->len = len;
		memcpy( _string->buffer, buffer, len );
	}
	else
	{
		_string->len = 0;
		_string->buffer = NULL;
	}

	_string->is_ref = 0;

	return _string;
}

sn_string *     
sn_string_clone ( const sn_string * p_src )
{
	if ( p_src != NULL )
	{
		return sn_string_create_from_buffer( p_src->buffer, p_src->len );
	}

	return NULL;
}

sn_string *     
sn_string_create_ref_from_buffer( char * buffer, unsigned long int len )
{
	if ( buffer != NULL )
	{
		sn_string * _string = (sn_string*) malloc( sizeof(sn_string ) );
                _string->len = len;
                _string->buffer = buffer;
                _string->is_ref = 1;
		return _string;
	}

	return NULL;
}

sn_string *     
sn_string_mid( const sn_string * p_string, unsigned long int start, unsigned long int len )
{
	if ( p_string != NULL )
	{
		if ( ( start + len ) < p_string->len )
		{
			return sn_string_create_ref_from_buffer( &p_string->buffer[start], len );
		}
		else
		{
			LOG_ERROR( _module_name, "slicing beyond end\n" );
			return NULL;
		}
	}

	return NULL;
}

void            
sn_string_free( sn_string ** pp_string )
{
	if ( pp_string != NULL && (*pp_string) != NULL )
	{
		if ( (*pp_string)->is_ref == 0 )
		{
			sn_free( (void**) &(*pp_string)->buffer );
		}

		(*pp_string)->len = 0;
		(*pp_string)->is_ref = 1;
		sn_free( (void**) pp_string );
	}
}

int             
sn_string_cmp( const sn_string * p_left, const sn_string * p_right )
{
	if ( p_left != NULL && p_right != NULL )
	{
		unsigned long int min_len = MIN( p_left->len, p_right->len );
		return strncmp( p_left->buffer, p_right->buffer, min_len );
	}

	LOG_ERROR( _module_name, "invalid compare, NULL operands\n" );
	return -2;
}

void            
sn_string_cat( sn_string * p_dst, const sn_string * p_src )
{
	if ( p_dst != NULL && p_src != NULL )
	{
		char * old_buffer = p_dst->buffer;
		p_dst->buffer = (char*) malloc( (p_dst->len + p_src->len ) * sizeof( char ) );
		memcpy( p_dst->buffer, old_buffer, p_dst->len );
		memcpy( &p_dst->buffer[p_dst->len], p_src->buffer, p_src->len );
		p_dst->len += p_src->len;
		sn_free( (void**) &old_buffer );
	}
}

sn_string *     
sn_string_left ( const sn_string * p_string, unsigned long int len )
{
	return sn_string_mid( p_string, 0, len );
}

sn_string *     
sn_string_right( const sn_string * p_string, unsigned long int len )
{
	if ( p_string != NULL )
	{
		if ( p_string->len <= len )
		{
			return sn_string_mid( p_string, p_string->len - len, len );
		}

		LOG_ERROR( _module_name, "slicing before start\n" );
		return NULL;
	}

	return NULL;
}

void            
sn_string_print( const sn_string * p_string )
{
	if ( p_string != NULL && p_string->len > 0)
	{
		unsigned long int i = 0;
		for ( i =0 ; i<p_string->len; i++ )
		{
			fputc( p_string->buffer[i], stdout );
		}
	}
}


