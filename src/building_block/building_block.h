#ifndef BUILDING_BLOCK_H
#define BUILDING_BLOCK_H

#include "code_chunk.h"

#include "block_parameter_set.h"
#include "block_pin_set.h"

typedef struct _building_block
{
	char * name;

	block_parameter_set *params;
	block_pin_set *inputs;
	block_pin_set *outputs;
	code_chunk * code; 
	struct _parsed_building_block * p_parsed;
} building_block;

building_block *	building_block_create(const char * name);
void 			building_block_free( building_block ** p_block );
code_chunk *		building_block_to_xml( building_block * p_block );
building_block *	building_block_clone( building_block * p_block );

#endif
