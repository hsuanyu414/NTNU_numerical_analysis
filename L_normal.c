#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define DATA_POINTS 12

double **allocate_matrix( int row, int col);
double **transpose_matrix( double **matrix, int row, int col);
void free_matrix( double **matrix, int row, int col);
void matrix_multi( double **a, double **b, double **dest, int row_a, int col_a, int row_b, int col_b);
void copy_matrix( double **source, double ** dest, int row, int col);
void print_matrix( double **matrix, int row, int col);

void set_A( double **A, double **data, int row);
double RMSE( double **A, double **data, double *ans, int row, int col);

void gausian_elim( double **matrix, int row, int col, int **P, double **L, double ** U);
void PALU( int32_t row, int32_t col, double *answer, double **matrix);
void matrix_multi_P( int **a, double *b, double *dest, int row_a, int col_a, int row_b, int col_b);
int **allocate_matrix_P( int row, int col);
void free_matrix_P( int **matrix, int row, int col);
void exchange_P( int **P, int row, int col, int source, int dest);
void exchange( double **matrix, int row, int col, int source, int dest);
int choose_row( double **matrix, int col, int min, int max);
double my_abs( double a);

int main( void)
{
    double **month = allocate_matrix( DATA_POINTS, 1);
    double **oil_use = allocate_matrix( DATA_POINTS, 1);

    // set month
    for ( int i = 0 ; i < DATA_POINTS; i += 1)
    {
        month[ i][ 0] = i;
    }// for i

    // set oil_use
    for ( int i = 0 ; i < DATA_POINTS; i += 1)
    {
        scanf("%lf", &( oil_use[ i][ 0]));
    }// for i

    // print_matrix( month, DATA_POINTS, 1);

    double **A = allocate_matrix( DATA_POINTS, 4);

    set_A( A, month, DATA_POINTS);
    printf("A\n");
    print_matrix( A, DATA_POINTS, 4);

    double **A_T = transpose_matrix( A, DATA_POINTS, 4);

    printf("A_T\n");
    print_matrix( A_T, 4, DATA_POINTS);

    double **left = allocate_matrix( 4, 4);
    double **right = allocate_matrix( 4, 1);

    matrix_multi( A_T, A, left, 4, DATA_POINTS, DATA_POINTS, 4);
    matrix_multi( A_T, oil_use, right, 4, DATA_POINTS, DATA_POINTS, 1);

    printf("left\n");
    print_matrix( left, 4, 4);
    printf("\n\n");
    printf("right\n");
    print_matrix( right, 4, 1);


    // finish up the A_T*Ac = A_Tb
    double *ans = calloc( DATA_POINTS, sizeof( double));

    // transfer the double ** to double *
    for ( int i = 0 ; i < 4; i += 1)
    {
        ans[ i] = right[ i][ 0];
    }// for j

    PALU( 4, 4, ans, left);

    printf("ANSWER\n");
    for ( int i = 0 ; i < 4; i += 1)
    {
        printf("%lf\n", ans[ i]);
    }// for i
    //print_matrix( ans, DATA_POINTS, 1);

    // do not use
    printf("RMSE %lf\n", RMSE( A, oil_use, ans, DATA_POINTS, 4));

    // finish
    free( ans);

    free_matrix( left, 4, 4);
    free_matrix( right, 4, 1);

    free_matrix( A_T, 4, DATA_POINTS);
    free_matrix( A, DATA_POINTS, 4);
    free_matrix( month, DATA_POINTS, 1);
    free_matrix( oil_use, DATA_POINTS, 1);


    return 0;
}

double RMSE( double **A, double **data, double *ans, int row, int col)
{
    // this is not sure
    double yeet = 0;

    double **BB = allocate_matrix( row, 1);

    double **temp = allocate_matrix( col, 1);

    for ( int i = 0 ; i < col; i += 1)
    {
        temp[ i][ 0] = ans[ i];
    }// for i

    matrix_multi( A, temp, BB, row, col, col, 1);

    printf("BB\n");
    print_matrix( BB, row, 1);

    for ( int i = 0 ; i < row; i += 1)
    {
        yeet += pow( ( data[ i][ 0] - BB[ i][ 0]), 2);
    }// for i

    free_matrix( BB, row, 1);

    free_matrix( temp, col, 1);

    yeet = sqrt( yeet / row);

    return yeet;
}

void set_A( double **A, double **data, int row)
{
    for ( int i = 0 ; i < row; i += 1)
    {
        A[ i][ 0] = 1;
        A[ i][ 1] = cos( 2 * M_PI * ( data[ i][ 0] / row));
        A[ i][ 2] = sin( 2 * M_PI * ( data[ i][ 0] / row));
        A[ i][ 3] = cos( 4 * M_PI * ( data[ i][ 0] / row));

        // A[ i][ 0] = 1;
        // A[ i][ 1] = ;
    }// for i

    return;
}


void PALU( int32_t row, int32_t col, double *answer_vector, double **matrix)
{
    // double **matrix = allocate_matrix( row, col);

    // get_matrix( matrix, row, col);

    int **P = allocate_matrix_P( row, col);

    // init P
    for ( int i = 0; i < row; i++)
    {
        P[ i][ i] = 1;
    }// for i

    double **L = allocate_matrix( row, col);

    double **U = allocate_matrix( row, col);

    gausian_elim( matrix, row, col, P, L, U);  // killed my answer_vector

    /*// print the result
    printf("P\n");

    print_matrix_P( P, row, col);

    printf("\n\n\n");

    printf("L\n");

    print_matrix( L, row, col);

    printf("\n\n\n");

    printf("U\n");

    print_matrix( U, row, col);

    printf("\n\n\n");
    */

    /* temporary answer
    printf("Vector\n");

    double *answer = calloc( sizeof( double), row);

    for ( int i = 0 ; i < row ; i++)
    {
        scanf("%lf", &answer[ i]);
    }// for i */

    double *buffer = calloc( sizeof( double), row);

    matrix_multi_P( P, answer_vector, buffer, row, col, row, 1);

    // perform the PAx=Pb
    for ( int i = 0; i < row; i++)
    {
        answer_vector[ i] = buffer[ i];
    }// for i

    free( buffer);

    /*
    printf("ANSWER start\n");

    for ( int i = 0; i < row; i++)
    {
        printf("%lf\n", answer[ i]);
    }// for i */

    // solve L
    for ( int32_t i = 0; i < row; i++)
    {
        for ( int32_t j = 0; j < i; j++)
        {
            answer_vector[ i] -= answer_vector[ j] * L[ i][ j];
        }// for j

        answer_vector[ i] = answer_vector[ i] / L[ i][ i];
    }// for i

    /*
    printf("After L\n");

    for ( int i = 0; i < row; i++)
    {
        printf("%lf\n", answer[ i]);
    }// for i */

    // solve U
    for ( int32_t i = row - 1; i >= 0; i--)
    {
        for ( int32_t j = row - 1; j > i; j--)
        {
            answer_vector[ i] -= answer_vector[ j] * U[ i][ j];
        }// for j

        answer_vector[ i] /= U[ i][ i];
    }// for i

    /*
    printf("After U finish\n");

    for ( int i = 0; i < row; i++)
    {
        printf("%lf\n", answer[ i]);
    }// for i */

    // free the eaten stuff

    // free( answer);

    // free_matrix( matrix, row, col);

    free_matrix_P( P, row, col);

    free_matrix( L, row, col);

    free_matrix( U, row, col);

    return;
}

void gausian_elim( double **matrix, int row, int col, int **P, double **L, double ** U)
{
    for ( int i = 0; i < row; i++)
    {
        int choosen_row = choose_row( matrix, i, i, row);

        exchange_P( P, row, col, choosen_row, i);

         //printf("inside %d\n", i);

        // print_matrix_P( P, row, col);

        exchange( matrix, row, col, choosen_row, i);

        exchange( L, row, col, choosen_row, i);

        L[ i][ i] = 1;

        for ( int j = i + 1; j < row; j++)
        {
            L[ j][ i] = matrix[ j][ i] / matrix[ i][ i];

            for ( int k = 0; k < col; k++)
            {
                matrix[ j][ k] -= matrix[ i][ k] * L[ j][ i];
            }// for k
        }// for j

        // printf("Matrix status %d\n", i);

        // print_matrix( matrix, row, col);
    }// for i

    copy_matrix( matrix, U, row, col);

    return;
}

void copy_matrix( double **source, double ** dest, int row, int col)
{
    for ( int i = 0; i < row; i++)
    {
        for ( int j = 0 ; j < col; j++)
        {
            dest[ i][ j] = source[ i][ j];
        }// for j
    }// for i

    return;
}

void free_matrix( double **matrix, int row, int col)
{
    // free the matrix
    for ( int i = 0; i < row; i++)
    {
        free( matrix[ i]);
    }// for i

    free( matrix);

    return;
}

double **transpose_matrix( double **matrix, int row, int col)
{
    double **dest = allocate_matrix( col, row);

    for ( int i = 0; i < row; i += 1)
    {
        for ( int j = 0 ; j < col; j += 1)
        {
            dest[ j][ i] = matrix[ i][ j];
        }// for j
    }// for i

    return dest;
}

double **allocate_matrix( int row, int col)
{
    // matrix allocation
    double **matrix = NULL;

    matrix = calloc( row, sizeof( double*));

    for ( int i = 0; i < row; i++)
    {
        matrix[ i] = calloc( col, sizeof( double));
    }// for i

    return matrix;
}

void print_matrix( double **matrix, int row, int col)
{
    for ( int i = 0; i < row; i ++)
    {
        for ( int j = 0; j < col; j++)
        {
            printf("%lf ", matrix[ i][ j]);
        }//for j
        printf("\n");
    }// for i

    return;
}

void matrix_multi( double **a, double **b, double **dest, int row_a, int col_a, int row_b, int col_b)
{
    for ( int i = 0; i < row_a; i++)
    {
        for ( int j = 0; j < col_b; j++)
        {
            double sum = 0;

            for ( int k = 0; k < col_a; k++)
            {
                sum += a[ i][ k] * b[ k][ j];

            }// for col_a

            dest[ i][ j] = sum;
        }// for col_b

    }// for row_a

    return;
}


void matrix_multi_P( int **a, double *b, double *dest, int row_a, int col_a, int row_b, int col_b)
{
    for ( int i = 0; i < row_a; i++)
    {
        for ( int j = 0; j < col_b; j++)
        {
            double sum = 0;

            for ( int k = 0; k < col_a; k++)
            {
                sum += a[ i][ k] * b[ k];

            }// for col_a

            dest[ i] = sum;

            // printf("%lf\n", sum);
        }// for col_b

    }// for row_a

    return;
}

void free_matrix_P( int **matrix, int row, int col)
{
    // free the matrix
    for ( int i = 0; i < row; i++)
    {
        free( matrix[ i]);
    }// for i

    free( matrix);

    return;
}

int **allocate_matrix_P( int row, int col)
{
    // matrix allocation
    int **matrix = NULL;

    matrix = calloc( row, sizeof( int*));

    for ( int i = 0; i < row; i++)
    {
        matrix[ i] = calloc( col, sizeof( int));
    }// for i

    return matrix;
}

void exchange_P( int **P, int row, int col, int source, int dest)
{
    int buffer[ col];

    // source copy to buffer
    for ( int i = 0; i < col; i++)
    {
        buffer[ i] = P[ source][ i];
    }// for i

    // write dest to source
    for ( int i = 0; i < col; i++)
    {
        P[ source][ i] = P[ dest][ i];
    }// for i

    // write buffer to dest
    for ( int i = 0; i < col; i++)
    {
        P[ dest][ i] = buffer[ i];
    }// for i

    return;
}

void exchange( double **matrix, int row, int col, int source, int dest)
{
    double buffer[ col];

    // source copy to buffer
    for ( int i = 0; i < col; i++)
    {
        buffer[ i] = matrix[ source][ i];
    }// for i

    // write dest to source
    for ( int i = 0; i < col; i++)
    {
        matrix[ source][ i] = matrix[ dest][ i];
    }// for i

    // write buffer to dest
    for ( int i = 0; i < col; i++)
    {
        matrix[ dest][ i] = buffer[ i];
    }// for i

    return;
}

int choose_row( double **matrix, int col, int min, int max)
{
    int value = matrix[ min][ col];

    int ans = min;

    for ( int i = min; i < max; i++)
    {
        if ( my_abs( matrix[ i][ col]) > value)
        {
            value = my_abs( matrix[ min][ col]);

            ans = i;
        }// if
    }// for i

    return ans;
}

double my_abs( double a)
{
    if ( a < 0)
    {
        return ( -1) * a;
    }// if

    return a;
}

