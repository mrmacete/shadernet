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

code_chunk * 	code_chunk_create_empty();
code_chunk * 	code_chunk_create_from_buffer( const char * buffer, int length );
void 		code_chunk_free( code_chunk ** pp_code_chunk );

code_chunk*	code_chunk_clone( code_chunk *p_src );

void		code_chunk_merge( code_chunk *p_dst, code_chunk *p_src);
code_chunk *	code_chunk_split( code_chunk *p_src, int from_line );

void		code_chunk_alloc_block( code_chunk * p_code_chunk, int n );
void 		code_chunk_add_code( code_chunk * p_code_chunk, const char * code, int code_size );

void 		code_chunk_print( code_chunk * p_code_chunk, int flags );
int		code_chunk_get_block_size();

void		code_chunk_update_lines( code_chunk * p_chunk );
void		code_chunk_delete_line( code_chunk * p_chunk, int line );
void		code_chunk_delete_lines( code_chunk * p_chunk, int first, int how_many );
void		code_chunk_print_line( code_chunk * p_chunk, int line );
void		code_chunk_print_lines( code_chunk * p_chunk, int first, int how_many );

float		code_chunk_calc_overhead( code_chunk * p_chunk );
void		code_chunk_prune_unused( code_chunk * p_chunk );
#endif
