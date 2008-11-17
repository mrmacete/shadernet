#ifndef PARSED_COUPLE_H
#define PARSED_COUPLE_H

#define PARSER_WORD 50

typedef struct {
	char type[PARSER_WORD];
	char instance[PARSER_WORD];
	char literal[PARSER_WORD];
} parsed_couple;

parsed_couple *		parsed_couple_create(const char* token);
void			parsed_couple_free( parsed_couple ** pp_parsed_couple );
void			parsed_couple_parse( parsed_couple * p_couple, const char* token);
void 			parsed_couple_print( parsed_couple * p_couple );


#endif
