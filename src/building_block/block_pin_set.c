#include "block_pin_set.h"
#include <set.h>
#include <stdlib.h>
#include <stdio.h>
#include <log.h>
#include <string.h>

#include <sn_memory.h>

static char _module_name[] = "BLOCK_PIN_SET";

static compare_result 	compare_pins( void * p_data1, void * p_data2 );

static compare_result compare_pins( void * p_data1, void * p_data2 )
{
	block_pin * param1 = (block_pin*) p_data1;	
	block_pin * param2 = (block_pin*) p_data2;
	int same_name = 0;
	int same_type = 0;

	if ( p_data1 == NULL || p_data2 == NULL )
		return ELEMENTS_INVALID;


	if ( param1->name != NULL && param2->name != NULL )
		if ( strcmp( param1->name, param2->name ) == 0 )
			same_name = 1;			

	if ( param1->type == param2->type )
		same_type = 1;

	if ( same_type )
	{
		return ELEMENTS_EQUAL;
	}

	return ELEMENTS_DIFFER;

}


int
block_pin_set_contains( block_pin_set * p_pin_set, block_pin * pin )
{
	if ( p_pin_set == NULL || pin == NULL )
		return 0;

	return set_contains( &p_pin_set->pin_set, (void*) pin, &compare_pins );
}

block_pin *	
block_pin_set_by_name( block_pin_set * p_pin_set, const char * name )
{
	set_element * el = NULL;
	int pos=0;

	if ( p_pin_set == NULL || name==NULL )
		return NULL;

	
	el = p_pin_set->pin_set.head;
        do{
                if ( el != NULL )
                {
			block_pin * candidate = NULL;
			candidate = (block_pin*) el->data;
			if ( candidate && candidate->name && strcmp(candidate->name, name) == 0)
				return candidate;
			
                        el = el->next;
                }
                pos++;
        }while( pos < p_pin_set->pin_set.size && el != NULL );
	
	return NULL;
}

void		
block_pin_set_add( block_pin_set * p_pin_set, block_pin * pin )
{
	if ( p_pin_set == NULL || pin == NULL )
		return;
	
	if ( set_add_element( &p_pin_set->pin_set, (void *) pin ) != SUCCESS )
	{
		LOG_ERROR( _module_name, "could not add element" );
	}
	else
	{
		pin->p_parent = p_pin_set;
	}
	
}

block_pin_set * 
block_pin_set_create()
{
	block_pin_set * p_pin_set = malloc( sizeof( block_pin_set) );
	p_pin_set->pin_set.head = NULL;
	p_pin_set->pin_set.size = 0;
	p_pin_set->p_parent = NULL;
	p_pin_set->name = NULL;
	return p_pin_set;	
}

block_pin_set * 
block_pin_set_clone     ( block_pin_set * p_src )
{
	block_pin_set * result = NULL;
	set_element * el = NULL;

	if ( p_src == NULL )
		return NULL;
	
	result = block_pin_set_create();
	el = p_src->pin_set.head;

	while( el != NULL )
	{
		block_pin * src_pin = (block_pin*) el->data;
		block_pin_set_add( result, block_pin_clone( src_pin ) );
		el = el->next;
	}

	return result;
	
}

void            
block_pin_set_free( block_pin_set ** p_set )
{
	if ( p_set != NULL && (*p_set) != NULL )
	{
		while( (*p_set)->pin_set.size > 0 )
		{
			set_element * to_be_deleted = set_pop_element( &(*p_set)->pin_set );
			if ( to_be_deleted != NULL )
			{
				block_pin_free( (block_pin**) &(to_be_deleted->data) );
				set_element_free( &to_be_deleted );
			}
		}
		sn_free( (void**) &(*p_set)->name );
		sn_free( (void**) p_set );
	}
}

void            
block_pin_set_set_name( block_pin_set * p_set, const char *name )
{
	if ( p_set == NULL )
		return;

	sn_free( (void**) &p_set->name );
	if ( name != NULL )
	{
		p_set->name = (char*) malloc( 256 * sizeof(char) );
		strncpy( p_set->name, name, 256 );
	}

}
