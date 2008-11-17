#ifndef BOOKMARK_SET_H
#define BOOKMARK_SET_H

#include <set.h>
#include "parsing_bookmark.h"


typedef struct 
{
	set _set;

} bookmark_set;

bookmark_set * 	bookmark_set_create	();
void		bookmark_set_free	( bookmark_set ** p_set );

void 		bookmark_set_add	( bookmark_set * p_set, parsing_bookmark * bookmark );
void		bookmark_set_print	( bookmark_set * p_set );

#endif
