#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sn_memory.h>
#include <glsl_types.h>
#include <sn_config.h>

#include "building_block.h"

building_block *        
building_block_create( const char* name )
{
	building_block * result = (building_block*) malloc( sizeof( building_block ) );
	result->params = block_parameter_set_create();
	result->params->p_parent = result;

	result->inputs = block_pin_set_create();
	result->inputs->p_parent = result;

	result->outputs = block_pin_set_create();
	result->outputs->p_parent = result;
	
	result->name = (char*) malloc( NAME_LENGTH * sizeof(char) );	
	if ( name )
		strncpy( result->name, name, NAME_LENGTH );

	result->code = code_chunk_create_empty();
	result->p_parsed = NULL;

	return result;
}

building_block *
building_block_clone( building_block * p_block )
{
	building_block * result = NULL;

	if ( p_block == NULL )
		return NULL;

	result = (building_block*) malloc( sizeof( building_block ) );

	result->params = block_parameter_set_clone( p_block->params );
	result->params->p_parent = result;	

	result->inputs = block_pin_set_clone( p_block->inputs );
	result->inputs->p_parent = result;	

	result->outputs = block_pin_set_clone( p_block->outputs );
	result->outputs->p_parent = result;	

	result->name = (char*) malloc( NAME_LENGTH * sizeof(char) );	
	if ( p_block->name != NULL )
		strncpy( result->name, p_block->name, NAME_LENGTH );

	result->code = code_chunk_clone( p_block->code );

	return result;
	
}

void                    
building_block_free( building_block ** p_block )
{
	if ( p_block != NULL && (*p_block) != NULL )
	{
		block_parameter_set_free( &(*p_block)->params ); 
		block_pin_set_free( &(*p_block)->inputs );
		block_pin_set_free( &(*p_block)->outputs );
		code_chunk_free( &(*p_block)->code );
		sn_free( (void**) &(*p_block)->name );
		sn_free( (void**) p_block );
	}
}

code_chunk *            
building_block_to_xml( building_block * p_block )
{
	int nl_len= 0;
	code_chunk * xml_code = NULL;
	set_element * el;
	xml_code = code_chunk_create_empty();

	if ( p_block == NULL )
		return xml_code;

	nl_len = strlen("\n" );
	
	code_chunk_add_code( xml_code, "<block name=\"", 13 );
	code_chunk_add_code( xml_code, p_block->name, strlen(p_block->name) );
	code_chunk_add_code( xml_code, "\" >\n", 3 + nl_len );
	
	el = p_block->inputs->pin_set.head;
	while( el != NULL )
	{
		char * string_type = NULL;	
		code_chunk_add_code( xml_code, "<input name=\"", 13 );
		code_chunk_add_code( xml_code, ((block_pin*) el->data)->name, strlen( ((block_pin*) el->data)->name ) );
		code_chunk_add_code( xml_code, "\" type=\"", 8 );
		string_type = glsl_type_to_string( ((block_pin*) el->data)->type );
		code_chunk_add_code( xml_code, string_type, strlen( string_type ) );
		sn_free( (void**) &string_type );
		code_chunk_add_code( xml_code, "\" />\n", 4 + nl_len );

		el = el->next;
	}
	
	el = p_block->outputs->pin_set.head;
        while( el != NULL )
        {
                char * string_type = NULL;
                code_chunk_add_code( xml_code, "<output name=\"", 14 );
                code_chunk_add_code( xml_code, ((block_pin*) el->data)->name, strlen( ((block_pin*) el->data)->name ) );
                code_chunk_add_code( xml_code, "\" type=\"", 8 );
                string_type = glsl_type_to_string( ((block_pin*) el->data)->type );
                code_chunk_add_code( xml_code, string_type, strlen( string_type ) );
                sn_free( (void**) &string_type );
                code_chunk_add_code( xml_code, "\" />\n", 4 + nl_len );

		el = el->next;
        }

	code_chunk_add_code( xml_code, "<code>\n", 6 + nl_len ); 
	code_chunk_add_code( xml_code, p_block->code->buffer, p_block->code->used_size );
	code_chunk_add_code( xml_code, "\n</code>\n", 7 + 2*nl_len ); 
	code_chunk_add_code( xml_code, "</block>", 8 + nl_len ); 

	return xml_code;
}
