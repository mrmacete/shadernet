#ifndef BLOCK_PIN_SET_H
#define BLOCK_PIN_SET_H

#include "set.h"
#include "block_pin.h"

struct _building_block;

typedef struct _block_pin_set
{
	char * name;
	set pin_set;
	struct _building_block * p_parent;

} block_pin_set;

block_pin_set * block_pin_set_create	();
void		block_pin_set_free	( block_pin_set ** p_set );

block_pin_set * block_pin_set_clone	( block_pin_set * p_src );

int 		block_pin_set_contains	( block_pin_set * p_set, block_pin * pin );
void 		block_pin_set_add	( block_pin_set * p_set, block_pin * pin );
block_pin*	block_pin_set_by_name	( block_pin_set * p_set, const char *name );

void		block_pin_set_set_name( block_pin_set * p_set, const char *name );

#endif
