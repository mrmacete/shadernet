#include "block_pin.h"
#include <log.h>
#include <stdio.h>
#include <stdlib.h>

#include <testing.h>
#include <sn_math.h>

void test_pin_int_value();
void test_pin_float_value();
void test_pin_matrix_value();

int main( int arch, char*argv[] )
{
	test_set_output( TEST_OUTPUT_NOT_PASSED );

	exit( 0 );

}
/*
void 
test_pin_int_value()
{
	int *value_a=NULL, *value_b=NULL;
        block_pin *pin_a=NULL, *pin_b=NULL;

        value_a = (int*) malloc( sizeof(int) );
        pin_a = block_pin_create( "testIntPinA", GLSL_TYPE_INT, value_a );
        *value_a = 4;

        value_b = (int*) malloc( sizeof(int) );
        pin_b = block_pin_create( "testIntPinB", GLSL_TYPE_INT, value_b );
        *value_b = 4;

        test_assert_true( block_pin_compare_value( pin_a, pin_b ) == 0 ,  "comparing int equals" );

        *value_a = 3;
        test_assert_true( block_pin_compare_value( pin_a, pin_b ) == -1 , "comparing int");

        *value_a = 5;
        test_assert_true( block_pin_compare_value( pin_a, pin_b ) == 1 , "comparing int more");

        block_pin_free( &pin_a );
        test_assert_true( block_pin_compare_value( pin_a, pin_b ) == 3 ,  "comparing int NULL" );

        block_pin_free( &pin_b );
        test_assert_true( pin_a == NULL && pin_b == NULL , "block_pin_free" );
}

void
test_pin_float_value()
{
        float *value_a=NULL, *value_b=NULL;
        block_pin *pin_a=NULL, *pin_b=NULL;

        value_a = (float*) malloc( sizeof(float) );
        pin_a = block_pin_create( "testFloatPinA", GLSL_TYPE_FLOAT, value_a );
        *value_a = 4.0;

        value_b = (float*) malloc( sizeof(float) );
        pin_b = block_pin_create( "testFloatPinB", GLSL_TYPE_FLOAT, value_b );
        *value_b = 4.0;

        test_assert_true( block_pin_compare_value( pin_a, pin_b ) == 0 ,  "comparing float equals" );

        *value_a = 3.9;
        test_assert_true( block_pin_compare_value( pin_a, pin_b ) == -1 , "comparing float");

        *value_a = 4.1;
        test_assert_true( block_pin_compare_value( pin_a, pin_b ) == 1 , "comparing float more");

        block_pin_free( &pin_a );
        test_assert_true( block_pin_compare_value( pin_a, pin_b ) == 3 ,  "comparing float NULL" );

        block_pin_free( &pin_b );
        test_assert_true( pin_a == NULL && pin_b == NULL , "block_pin_free" );
}

void
test_pin_matrix_value()
{
        matrix *value_a=NULL, *value_b=NULL;
        block_pin *pin_a=NULL, *pin_b=NULL;

        value_a = matrix_create(4,4);
        pin_a = block_pin_create( "testMatrixPinA", GLSL_TYPE_MAT4, value_a );

        value_b = matrix_create(4,4);
        pin_b = block_pin_create( "testMatrixPinB", GLSL_TYPE_MAT4, value_b );

        test_assert_true( block_pin_compare_value( pin_a, pin_b ) == 0 ,  "comparing matrix equals" );

        value_a->cols[0][1] = 69.0; 
        test_assert_true( block_pin_compare_value( pin_a, pin_b ) == -1 , "comparing matrix not equal");

	matrix_free( (matrix**) &pin_a->value );
        block_pin_free( &pin_a );
        test_assert_true( block_pin_compare_value( pin_a, pin_b ) == 3 ,  "comparing matrix NULL" );

	matrix_free( (matrix**) &pin_b->value );
        block_pin_free( &pin_b );
        test_assert_true( pin_a == NULL && pin_b == NULL , "block_pin_free" );
}
*/
