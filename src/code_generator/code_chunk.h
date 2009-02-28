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

#ifndef CODE_CHUNK_H
#define CODE_CHUNK_H

typedef struct {
	char * buffer;
	int buffer_size;
	int used_size;
	char **lines;
	char *last_line;
	int n_lines;
} code_chunk;

typedef enum { PRINT_LINE_NUMBERS=1 } print_flags;

struct _sn_string;

code_chunk * 	code_chunk_create_empty();
code_chunk * 	code_chunk_create_from_buffer( const char * buffer, int length );
void 		code_chunk_free( code_chunk ** pp_code_chunk );

code_chunk*	code_chunk_clone( code_chunk *p_src );

void		code_chunk_merge( code_chunk *p_dst, code_chunk *p_src);
code_chunk *	code_chunk_split( code_chunk *p_src, int from_line );
code_chunk *	code_chunk_split_left( code_chunk *p_src, int length );
code_chunk *	code_chunk_split_right( code_chunk *p_src, int first );
char *		code_chunk_replace( code_chunk *p_dst, char * start_byte, int length, code_chunk * new_code );

void		code_chunk_alloc_block( code_chunk * p_code_chunk, int n );
void 		code_chunk_add_code( code_chunk * p_code_chunk, const char * code, int code_size );
void 		code_chunk_add_string( code_chunk * p_code_chunk, struct _sn_string * p_string );

void 		code_chunk_print( code_chunk * p_code_chunk, int flags );
int		code_chunk_get_block_size();

void		code_chunk_update_lines( code_chunk * p_chunk );
void		code_chunk_delete_line( code_chunk * p_chunk, int line );
void		code_chunk_delete_lines( code_chunk * p_chunk, int first, int how_many );
void		code_chunk_print_line( code_chunk * p_chunk, int line );
void		code_chunk_print_lines( code_chunk * p_chunk, int first, int how_many );

void		code_chunk_delete_bytes( code_chunk * p_chunk, unsigned int first, unsigned int how_many );

float		code_chunk_calc_overhead( code_chunk * p_chunk );
void		code_chunk_prune_unused( code_chunk * p_chunk );
#endif
