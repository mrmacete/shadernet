#ifndef PARSED_BUILDING_BLOCK
#define PARSED_BUILDING_BLOCK

#include <building_block.h>
#include "bookmark_set.h"

typedef struct _parsed_building_block
{
	building_block * p_block;
	bookmark_set * bookmarks;
	int undefined_references;
	int invalid_types;	
	char * name;
} parsed_building_block;

parsed_building_block*	parsed_building_block_create( building_block * p_block, const char * name );
void			parsed_building_block_free( parsed_building_block ** pp_parsed_building_block );

#endif
