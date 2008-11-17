#ifndef BLOCK_PARAMETER_SET_H
#define BLOCK_PARAMETER_SET_H

#include "set.h"
#include "block_parameter.h"

struct _building_block;

typedef struct _block_parameter_set
{
	set parameter_set;
	struct _building_block * p_parent;

} block_parameter_set;

block_parameter_set * 	block_parameter_set_create();
void			block_parameter_set_free( block_parameter_set ** p_set );

block_parameter_set*	block_parameter_set_clone( block_parameter_set * p_src );

int 			block_parameter_set_contains 	( block_parameter_set *, block_parameter * parameter );
void 			block_parameter_set_add 	( block_parameter_set *, block_parameter * parameter );
block_parameter *	block_parameter_set_by_name 	( block_parameter_set *, const char * name );

#endif
