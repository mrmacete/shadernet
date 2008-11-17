#include "block_parameter_set.h"
#include <set.h>
#include <stdlib.h>
#include <stdio.h>
#include <log.h>
#include <string.h>

#include <sn_memory.h>

static char _module_name[] = "BLOCK_PARAMETER_SET";

static compare_result 	compare_parameters( void * p_data1, void * p_data2 );
block_parameter*	block_parameter_set_by_name( block_parameter_set * p_set, const char * name );

static compare_result compare_parameters( void * p_data1, void * p_data2 )
{
	block_parameter * param1 = NULL;	
	block_parameter * param2 = NULL;

	if ( p_data1 == NULL || p_data2 == NULL )
		return ELEMENTS_INVALID;

	param1 = (block_parameter*) p_data1;	
	param2 = (block_parameter*) p_data2;

	if ( param1->name != NULL && param2->name != NULL )
	{
		if ( param1->literals != NULL && param2->literals != NULL )
		{
			if ( param1->literals->size != param2->literals->size )
				return ELEMENTS_DIFFER;

			if ( strcmp( param1->name, param2->name ) == 0 )
			{
				return ELEMENTS_EQUAL;
			}

			return ELEMENTS_DIFFER;
		}

	}

	return ELEMENTS_INVALID;	

}

int
block_parameter_set_contains( block_parameter_set * p_parameter_set, block_parameter * parameter )
{
	if ( p_parameter_set == NULL || parameter == NULL )
		return 0;

	return set_contains( &p_parameter_set->parameter_set, (void*) parameter, &compare_parameters );
}

void		
block_parameter_set_add( block_parameter_set * p_parameter_set, block_parameter * parameter )
{
	if ( p_parameter_set == NULL || parameter == NULL )
		return;
	
	if ( set_add_element( &p_parameter_set->parameter_set, (void *) parameter ) != SUCCESS )
	{
		LOG_ERROR( _module_name, "could not add element" );
	}
	
}

block_parameter*	
block_parameter_set_by_name( block_parameter_set * p_set, const char * name )
{
	set_element * el = NULL;
        int pos=0;

        if ( p_set == NULL || name==NULL )
                return NULL;


        el = p_set->parameter_set.head;
        do{
                if ( el != NULL )
                {
                        block_parameter * candidate = NULL;
                        candidate = (block_parameter*) el->data;
                        if ( candidate && candidate->name && strcmp(candidate->name, name) == 0)
                                return candidate;

                        el = el->next;
                }
                pos++;
        }while( pos < p_set->parameter_set.size && el != NULL );

        return NULL;
}

block_parameter_set * 
block_parameter_set_create()
{
	block_parameter_set * p_parameter_set = malloc( sizeof( block_parameter_set) );
	p_parameter_set->parameter_set.head = NULL;
	p_parameter_set->parameter_set.size = 0;
	p_parameter_set->p_parent = NULL;
	return p_parameter_set;	
}

block_parameter_set*    
block_parameter_set_clone( block_parameter_set * p_src )
{
	if ( p_src )
	{
		block_parameter_set * result = block_parameter_set_create();
		set_element * el = p_src->parameter_set.head;
		while ( el != NULL )
		{
			block_parameter_set_add( result, block_parameter_clone( (block_parameter*) el->data ) );
			el = el->next;
		}

		return result;

	}

	return NULL;
	
}

void                    
block_parameter_set_free( block_parameter_set ** p_set )
{
	if ( p_set != NULL && (*p_set) != NULL )
	{
		while( (*p_set)->parameter_set.size > 0 )
		{
			set_element * el = set_pop_element( &(*p_set)->parameter_set );
			if ( el != NULL )
			{
				block_parameter_free( (block_parameter**) &el->data );
				set_element_free( &el );
			}
		}
		sn_free( (void**) p_set );
	}
}
