#ifndef BLOCK_PARAMETER
#define BLOCK_PARAMETER

struct _block_parameter_set;
struct _set;

typedef struct _literal
{
	char * key;
	unsigned int key_len;
	int value;

} literal;

typedef struct _block_parameter
{
	char * name;
	char * string_value;
	int literal_value;
	unsigned int string_len;
	struct _block_parameter_set * p_parent;
	struct _set *literals;
} block_parameter;

void 			block_parameter_free( block_parameter ** p_paramater );
block_parameter * 	block_parameter_create( const char* name );
block_parameter * 	block_parameter_clone( block_parameter * p_src );
void			block_parameter_add_literal( block_parameter *p_param, const char *key, unsigned int key_len, int value );	
void			block_parameter_set_string_value( block_parameter *p_param, const char * string_value, unsigned int string_len );

#endif
