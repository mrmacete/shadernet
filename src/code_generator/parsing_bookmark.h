#ifndef PARSING_BOOKMARK_H
#define PARSING_BOOKMARK_H

#include <block_pin.h>
#include <block_parameter.h>
#include "parsed_couple.h"

typedef enum { BOOKMARK_PIN, BOOKMARK_PARAM, BOOKMARK_INVALID } bookmark_type;

typedef union {
	block_pin * p_pin;
	block_parameter * p_param;
} association;

typedef struct {
	char * p_start;
	int length;
	bookmark_type type;
	association u_association;
	parsed_couple * p_couple;
} parsing_bookmark;

parsing_bookmark*	parsing_bookmark_create( char * p_start, int length, parsed_couple *p_couple );
void			parsing_bookmark_free( parsing_bookmark ** pp_parsing_bookmark );
void 			parsing_bookmark_print( parsing_bookmark * p_parsing_bookmark );
#endif
