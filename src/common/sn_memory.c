#include <stdio.h>
#include <stdlib.h>

void sn_free( void ** p_memory_block )
{
	if ( p_memory_block != NULL && *p_memory_block != NULL )
	{
		free( *p_memory_block );
		*p_memory_block = NULL;
	}
}
