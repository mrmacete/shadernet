#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sn_math.h"
#include "sn_memory.h"

matrix *        
matrix_create(int rows, int cols)
{
	int i=0;
	matrix * new_matrix = (matrix*) malloc( sizeof(matrix) );
	new_matrix->w = cols;
	new_matrix->h = rows;
	new_matrix->values = (float*) malloc( cols * rows * sizeof(float) );
	new_matrix->cols = (float**) malloc( cols * sizeof(float*) );
	for( i=0; i<cols; i++)
	{
		new_matrix->cols[i] = &new_matrix->values[i*rows];
	}
	matrix_set_identity( new_matrix );
	return new_matrix;
}

void            
matrix_free( matrix ** p_matrix )
{
	if ( p_matrix != NULL && (*p_matrix) != NULL )
	{
		sn_free( (void**) &(*p_matrix)->values );
		sn_free( (void**) &(*p_matrix)->cols );
		sn_free( (void**) p_matrix );
	}	
}

void            
matrix_set_identity( matrix * p_matrix )
{
	if ( p_matrix != NULL )
	{
		int i;
		memset( p_matrix->values, 0, p_matrix->w * p_matrix->h * sizeof(float) );
		for( i=0; i<p_matrix->w && i<p_matrix->h; i++ )
			p_matrix->cols[i][i] = 1.0;
	}
}

void            
matrix_print( matrix * p_matrix )
{
	if ( p_matrix != NULL )
	{
		int r,c;
		for( r=0; r<p_matrix->h; r++ )
		{
			for( c=0; c<p_matrix->w; c++ )
			{
				printf( "%5.3f\t", *(p_matrix->values + r * p_matrix->h + c) );
			}

			printf( "\n" );
		}
				
	}
}
