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
#include <string.h>

#include <sn_memory.h>
#include <sn_string.h>
#include <log.h>
#include <set.h>

#include "code_chunk.h"


#define BLOCK_SIZE 512

static char _module_name[] = "CODE_CHUNK";

int             
code_chunk_get_block_size()
{
	return BLOCK_SIZE;
}

code_chunk * 
code_chunk_create_empty()
{
	code_chunk * new_code_chunk = (code_chunk*) malloc( sizeof(code_chunk) );
	new_code_chunk->buffer = NULL;
	new_code_chunk->buffer_size = 0;
	new_code_chunk->used_size = 0;
	new_code_chunk->lines = NULL;
	new_code_chunk->n_lines = 0;
	new_code_chunk->last_line = NULL;
	
	return new_code_chunk;
}

code_chunk *
code_chunk_create_from_buffer( const char * buffer, int length )
{
	code_chunk * new_code_chunk = code_chunk_create_empty();

	if ( buffer != NULL  && length > 0 )
	{
		new_code_chunk->buffer = (char*) malloc( (length+1) * sizeof(char) );
		memcpy( new_code_chunk->buffer, buffer, length );
		*(new_code_chunk->buffer + length) = 0;
		new_code_chunk->buffer_size = length;
		new_code_chunk->used_size = length;
		new_code_chunk->lines = NULL;
		new_code_chunk->n_lines = 0;
		new_code_chunk->last_line = NULL;

		code_chunk_update_lines( new_code_chunk );
	}

	return new_code_chunk;
}

float           
code_chunk_calc_overhead( code_chunk * p_chunk )
{
	float overhead = 1.0f;

	if ( p_chunk != NULL )
	{
		overhead = 1.0f - ( (float) p_chunk->used_size / (float) ( p_chunk->buffer_size + p_chunk->n_lines*4 + sizeof( code_chunk ) ) ) ;
	}

	return overhead;
}

void
code_chunk_free( code_chunk ** pp_code_chunk )
{
	if ( pp_code_chunk != NULL && *pp_code_chunk != NULL )
	{
		sn_free( (void**) & (*pp_code_chunk)->buffer );
		sn_free( (void**) & (*pp_code_chunk)->lines );
		(*pp_code_chunk)->buffer_size = 0;		
		(*pp_code_chunk)->used_size = 0;		
		sn_free( (void**) pp_code_chunk );
	}
}

void            
code_chunk_alloc_block( code_chunk * p_code_chunk, int n )
{
	char * old_buffer = NULL;
	int new_bytes = 0;

	if ( p_code_chunk == NULL )
	{
		LOG_DEBUG( _module_name, "null chunk, cannot allocate blocks" );
		return;
	}

	old_buffer = p_code_chunk->buffer;
	new_bytes = n*BLOCK_SIZE;
	p_code_chunk->buffer = (char*) malloc( (p_code_chunk->used_size + new_bytes ) * sizeof(char) );
	
	if ( old_buffer != NULL && p_code_chunk->used_size > 0 )
	{
		memcpy( p_code_chunk->buffer, old_buffer, p_code_chunk->used_size );
		sn_free( (void**) &old_buffer );
	}

	memset( p_code_chunk->buffer + p_code_chunk->used_size, 0, new_bytes );
	p_code_chunk->buffer_size += new_bytes;
}

void           
code_chunk_prune_unused( code_chunk * p_chunk )
{
	if ( p_chunk == NULL || p_chunk->used_size == 0)
		return;

	if ( p_chunk->buffer_size > p_chunk->used_size+1 )
	{
		char * old_buffer = p_chunk->buffer;
		p_chunk->buffer = (char*) malloc( (p_chunk->used_size + 1 ) * sizeof(char) );
		if ( old_buffer != NULL )
		{
			memcpy( p_chunk->buffer, old_buffer, p_chunk->used_size );
			sn_free( (void**) &old_buffer );
		}
		*(p_chunk->buffer + p_chunk->used_size ) =0;
		p_chunk->buffer_size = p_chunk->used_size+1;
		p_chunk->last_line = NULL;
		p_chunk->n_lines = 0;
		code_chunk_update_lines( p_chunk );
	}
}

void            
code_chunk_merge( code_chunk *p_dst, code_chunk *p_src)
{
	if ( p_dst == NULL || p_src == NULL )
	{
		LOG_DEBUG( _module_name, "something was NULL in merging\n" );
		return;
	}

	code_chunk_add_code( p_dst, p_src->buffer, p_src->used_size );
	p_dst->n_lines = 0;
	p_dst->last_line = NULL;
	code_chunk_update_lines( p_dst );
}

code_chunk*     
code_chunk_clone( code_chunk *p_src )
{
	code_chunk * clone = NULL;

	if ( p_src == NULL )
		return NULL;

	clone = code_chunk_create_empty();
	code_chunk_merge( clone, p_src );
	return clone;
}

code_chunk *    
code_chunk_split( code_chunk *p_src, int from_line )
{
	code_chunk * new_code_chunk = NULL;

	if ( p_src == NULL )
	{
		LOG_DEBUG( _module_name, "cannot split NULL\n" );
		return NULL;
	}

	if ( from_line >= p_src->n_lines )
	{
		LOG_ERROR( _module_name, "cannot split beyond end of text\n" );
		return NULL;
	}

	new_code_chunk = code_chunk_create_from_buffer( p_src->lines[from_line], p_src->used_size - ( p_src->lines[from_line] - p_src->buffer ) );
	code_chunk_delete_lines( p_src, from_line, p_src->n_lines - from_line );

	return new_code_chunk;

}

code_chunk *
code_chunk_split_left( code_chunk *p_src, int length )
{
        code_chunk * new_code_chunk = NULL;

        if ( p_src == NULL )
        {
                LOG_DEBUG( _module_name, "cannot split NULL\n" );
                return NULL;
        }

        if ( length >= p_src->used_size )
        {
                LOG_ERROR( _module_name, "cannot split beyond end of text\n" );
                return NULL;
        }

        new_code_chunk = code_chunk_create_from_buffer( p_src->buffer, length );
	code_chunk_delete_bytes( p_src, 0, length );

        return new_code_chunk;

}

code_chunk *
code_chunk_split_right( code_chunk *p_src, int first )
{
        code_chunk * new_code_chunk = NULL;

        if ( p_src == NULL )
        {
                LOG_DEBUG( _module_name, "cannot split NULL\n" );
                return NULL;
        }

        if ( first >= p_src->used_size )
        {
                LOG_ERROR( _module_name, "cannot split beyond end of text\n" );
                return NULL;
        }

        new_code_chunk = code_chunk_create_from_buffer( p_src->buffer + first, p_src->used_size - first );
        code_chunk_delete_bytes( p_src, first, p_src->used_size - first );

        return new_code_chunk;

}


void            
code_chunk_delete_bytes( code_chunk * p_chunk, unsigned int first, unsigned int how_many )
{
        int bytes_to_copy;
        int transfer_size;
        char * start = NULL;
        char * end = NULL;

	if ( p_chunk == NULL )
		return;

	if ( first + how_many > p_chunk->used_size )
	{
		LOG_ERROR( _module_name, "cannot delete bytes beyond end of text\n" );
	        return;
	}

	bytes_to_copy = p_chunk->used_size - first - how_many;
        transfer_size = how_many;
        start = p_chunk->buffer + first;
        end = start + transfer_size;

        /* copy a group at a time, to avoid memcpy overlapping */
        while ( bytes_to_copy )
        {
                if ( bytes_to_copy < how_many )
                        transfer_size = bytes_to_copy;
                memcpy( start, end, transfer_size );
                bytes_to_copy -= transfer_size;
                start += transfer_size;
                end += transfer_size;
        }

        p_chunk->last_line = NULL;
        p_chunk->n_lines = 0;

        p_chunk->used_size -= how_many ;
        *(p_chunk->buffer + p_chunk->used_size) = 0;

        code_chunk_update_lines( p_chunk );
}

void            
code_chunk_add_string( code_chunk * p_code_chunk, struct _sn_string * p_string )
{
	if ( p_string != NULL )
		code_chunk_add_code( p_code_chunk, p_string->buffer, p_string->len );
}

void            
code_chunk_add_code( code_chunk * p_code_chunk, const char * code, int code_size )
{
	int free_size =0;

	if ( p_code_chunk == NULL )
        {
                LOG_DEBUG( _module_name, "null chunk, cannot add code" );
                return;
        }

	if ( code==NULL || *code == 0 )
		return;
	
	free_size = p_code_chunk->buffer_size - p_code_chunk->used_size;
	if ( code_size >= free_size )
	{
		int n_blocks = 0;
		n_blocks = code_size / BLOCK_SIZE;
		if ( (code_size % BLOCK_SIZE) != 0 )
			n_blocks++;
		if ( n_blocks == 0 )
			n_blocks = 1;
		code_chunk_alloc_block( p_code_chunk, n_blocks );
		p_code_chunk->last_line = p_code_chunk->buffer;
		p_code_chunk->n_lines = 0;

	}

	memcpy( p_code_chunk->buffer + p_code_chunk->used_size, code, code_size );
	p_code_chunk->used_size += code_size;	

	code_chunk_update_lines( p_code_chunk );

}

void            
code_chunk_update_lines( code_chunk * p_chunk )
{
	if ( p_chunk == NULL )
		return;


	if ( p_chunk->buffer == NULL )
	{
		p_chunk->n_lines = 0;
		sn_free( (void**) &p_chunk->lines );
		p_chunk->last_line = NULL;
		return;	
	}
	else
	{
		set * line_set;
		char * a_line = NULL;

		if ( p_chunk->last_line == NULL )
			p_chunk->last_line = p_chunk->buffer;

		/* store line pointers in a temporary set */
		line_set = set_create();

		a_line = p_chunk->last_line;
		
		if ( a_line == p_chunk->buffer )
			set_push_element( line_set, (void*) a_line );

		while(( a_line = memchr( a_line, '\n', (p_chunk->buffer + p_chunk->used_size) - a_line ) ) != NULL )
		{
			a_line++;
			if ( *a_line != 0 )
				set_push_element( line_set, (void*) a_line );
		}

		/* convert the set to an array */
		
		if ( line_set->size > 0 )
		{
			int i = 0;
			char ** new_lines = ( char ** ) malloc( (p_chunk->n_lines + line_set->size) * sizeof( char* ) );	
			set_element * el = line_set->head;
			while( el != NULL )
			{
				new_lines[p_chunk->n_lines + i++] = (char*) el->data;
				el = el->next;
			}

			if ( p_chunk->lines != NULL )
			{
				memcpy( new_lines, p_chunk->lines, p_chunk->n_lines * sizeof( char*) );
				sn_free( (void**) &p_chunk->lines );
			}

			p_chunk->lines = new_lines;
			p_chunk->n_lines += i;
			p_chunk->last_line = p_chunk->lines[ p_chunk->n_lines - 1 ];
		}
				
		set_soft_free( &line_set );

	}
	
}

void            
code_chunk_delete_line( code_chunk * p_chunk, int line )
{
	code_chunk_delete_lines( p_chunk, line, 1 );
}

void            
code_chunk_delete_lines( code_chunk * p_chunk, int first, int how_many )
{
	if ( p_chunk == NULL )
		return;

	if ( first < 0 )
	{
		first = 0;
		LOG_DEBUG( _module_name, "start of deletion before beginning of text, set to beginning\n" );
	}
	
	if ( (first + how_many) < p_chunk->n_lines )
	{
		char * first_line = p_chunk->lines[first];
		char * last_line = p_chunk->lines[first + how_many];
		int bytes_to_copy = (p_chunk->buffer + p_chunk->used_size) - last_line;
		int group_size = last_line-first_line;
		int transfer_size = group_size;

		/* copy a group at a time, to avoid memcpy overlapping */
		while ( bytes_to_copy )
		{
			if ( bytes_to_copy < group_size )
				transfer_size = bytes_to_copy;

			memcpy( first_line, last_line, transfer_size );
			bytes_to_copy -= transfer_size;
			first_line += transfer_size;
			last_line += transfer_size;
		}

		p_chunk->last_line = NULL;
		p_chunk->n_lines = 0;

		p_chunk->used_size -= ( group_size );
		*(p_chunk->buffer + p_chunk->used_size) = 0;

		code_chunk_update_lines( p_chunk );
	}
	else if ( (first + how_many) >= p_chunk->n_lines )
	{
		char * first_line = NULL;

		if ( first>p_chunk->n_lines)
		{
			LOG_ERROR( _module_name, "start of deletion beyond end of text, aborted\n" );
			return;
		}

		if ( (first + how_many) > p_chunk->n_lines )
		{
			how_many = p_chunk->n_lines - first;
			LOG_DEBUG( _module_name, "end of deletion beyond end of text, pruned\n" );
		}
		
		first_line = p_chunk->lines[first];
		p_chunk->last_line = NULL;
		p_chunk->n_lines = 0;
		p_chunk->used_size =  first_line -  p_chunk->buffer ;
		*(p_chunk->buffer + p_chunk->used_size) = 0;
		code_chunk_update_lines( p_chunk );
	}
}

void 
code_chunk_print_lines( code_chunk *p_chunk, int first, int how_many )
{
	int i=0;
	for( i = first; i<first+how_many && i<p_chunk->n_lines; i++ )
	{
		int line_size = 0;
		if ( i < p_chunk->n_lines-1 )
			line_size = p_chunk->lines[i+1] - p_chunk->lines[i];
		else
			line_size = (p_chunk->buffer + p_chunk->used_size) - p_chunk->lines[i];

		fwrite( p_chunk->lines[i], 1, line_size, stdout);
	}
}

void
code_chunk_print_line( code_chunk *p_chunk, int line )
{
	code_chunk_print_lines( p_chunk, line, 1 );
}

void            
code_chunk_print( code_chunk * p_code_chunk, int flags )
{
	if ( p_code_chunk == NULL )
		return;

	if ( (flags & PRINT_LINE_NUMBERS ) && p_code_chunk->lines != NULL )
	{
		int i = 0;
		for( i=0; i<p_code_chunk->n_lines; i++)
		{
			printf( "%3d ", i+1 );
			code_chunk_print_line( p_code_chunk, i );	
		}
	}
	else
	{
		printf( "%s\n", p_code_chunk->buffer );
	}

	
}

char*
code_chunk_replace( code_chunk *p_dst, char * start_byte, int length, code_chunk * new_code )
{
	if ( p_dst != NULL && start_byte != NULL && new_code != NULL )
	{
		if ( start_byte >= p_dst->buffer && start_byte < (p_dst->buffer + p_dst->used_size) )
		{
			char * start_of_new_code = NULL;
			code_chunk * before = code_chunk_split_left( p_dst, start_byte - p_dst->buffer );
			code_chunk * after = code_chunk_split_right( p_dst, length );
			code_chunk_delete_lines( p_dst, 0, p_dst->n_lines );
			code_chunk_merge( p_dst, before );
			start_of_new_code = p_dst->buffer + before->used_size;
			code_chunk_merge( p_dst, new_code );
			code_chunk_merge( p_dst, after );
			code_chunk_free( &before );
			code_chunk_free( &after );
			return start_of_new_code;
		}

	}

	return NULL;
}
