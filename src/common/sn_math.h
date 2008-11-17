#ifndef SC_MATH_H
#define SC_MATH_H

#define CLAMP( val, min, max )  (val<min)?min:((val>max)?max:val)
#define SATURATE( val )  (val<0)?-1:((val>0)?1:0)
#define MAX( x, y ) (x>y)?x:y
#define MIN( x, y ) (x<y)?x:y

typedef struct 
{
	float * values;
	int w;
	int h;
	float **cols;
} matrix;

/* matrix functions */
matrix *	matrix_create(int rows, int cols);
void		matrix_free( matrix ** p_matrix );
void		matrix_set_identity( matrix * p_matrix );
void		matrix_print( matrix * p_matrix );

#endif
