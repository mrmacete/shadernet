#ifndef BLOCK_PIN_H
#define BLOCK_PIN_H

#include <glsl_types.h>

struct _block_pin_set;

typedef struct _block_pin
{
	char * name;
	glsl_type type;
	void * value;
	struct _block_pin_set *p_parent;
	struct _block_pin * source;
} block_pin;

void block_pin_free( block_pin ** p_pin );
block_pin * block_pin_create( const char * name, glsl_type type );
block_pin * block_pin_clone( block_pin * p_src );
/*int block_pin_compare_value( block_pin * p_left, block_pin * p_right );*/
void block_pin_connect( block_pin * source, block_pin * drain );

#endif
