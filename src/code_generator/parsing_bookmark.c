#include <stdio.h>
#include <stdlib.h>

#include <log.h>
#include <sn_memory.h>

#include "parsing_bookmark.h"

static const char _module_name[] = "PARSING_BOOKMARK";

parsing_bookmark*       
parsing_bookmark_create( char * p_start, int length, parsed_couple *p_couple )
{
	parsing_bookmark * new_bookmark = (parsing_bookmark*) malloc( sizeof(parsing_bookmark) );
	new_bookmark->p_start = p_start;
	new_bookmark->length = length;
	new_bookmark->p_couple = p_couple;
	new_bookmark->type = BOOKMARK_INVALID;
	new_bookmark->u_association.p_pin = NULL;
	return new_bookmark;
}

void                    
parsing_bookmark_free( parsing_bookmark ** pp_parsing_bookmark )
{
	if ( pp_parsing_bookmark != NULL && (*pp_parsing_bookmark) != NULL )
	{
		parsed_couple_free( &(*pp_parsing_bookmark)->p_couple );
		sn_free( (void**) pp_parsing_bookmark );
	}
}

void                    
parsing_bookmark_print( parsing_bookmark * p_parsing_bookmark )
{
	if ( p_parsing_bookmark != NULL )
	{
		printf("[PBM] at %p, len %d, ", p_parsing_bookmark->p_start, p_parsing_bookmark->length );
		printf("%s, ", (p_parsing_bookmark->type!=BOOKMARK_INVALID)?"associated":"unassociated" ); 
		parsed_couple_print( p_parsing_bookmark->p_couple );
	}
}
