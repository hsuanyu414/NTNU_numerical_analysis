#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define MAX_ROW 100
#define MAX_COL 100
#define ERROR 0.00001

#define X1 ( 2)
#define Y1 ( 1)
#define X2 ( 5)
#define Y2 ( 3)
#define X3 ( 5)
#define Y3 ( -3)


void print_matrix( double **matrix, int row, int col);
void print_matrix_P( int **matrix, int row, int col);
void get_matrix( double **matrix, int row, int col);
double **allocate_matrix( int row, int col);
void free_matrix( double **matrix, int row, int col);

int **allocate_matrix_P( int row, int col);
void free_matrix_P( int **matrix, int row, int col);

void matrix_multi( int **a, double *b, double *dest, int row_a, int col_a, int row_b, int col_b);
void matrix_add( double *a, double *b, double *dest, int32_t row);
void copy_matrix( double **source, double ** dest, int row, int col);
void exchange_P( int **P, int row, int col, int source, int dest);
void exchange( double **matrix, int row, int col, int source, int dest);
int choose_row( double **matrix, int col, int min, int max);
double my_abs( double a);

void gausian_elim( double **matrix, int row, int col, int **P, double **L, double ** U);
void PALU( int32_t row, int32_t col, double *answer, double **matrix);
void set_df_matrix( double *guess, double **matrix);
void set_minus_f( double *guess, double * const vector);

void copy_vector( double * const source, double *dest, int32_t row);
double min_distance( double *a, double *b, int32_t row);
void set_guess( double *guess);

void set_Dr( double *guess, double **matrix, int row);
double **transpose_matrix( double **matrix, int row, int col);

void matrix_multi_double( double **dest, int row, int col, double **a, double **b, int col_a);
void set_right( double *right, double **dr_matrix, int row, int col, double *R);
void set_dist( double *dist, int row, double *guess);


/*
Circle 1: (-1, 0) R = 1
Circle 2: (1, 1) R = 1
Circle 3: (1, -1) R = 1
*/

double x[ 3] = { 2, 5, 5};
double y[ 3] = { 1, 3, -3};
double r[ 3] = { 1, 2, 1};

int main( void)
{
    int32_t row = 3;

    int32_t col = 2;

    double *guess = calloc( row, sizeof( double));

    double *new = calloc( row, sizeof( double));

    set_guess( new);

    double **df_matrix = allocate_matrix( row, col);

    double *vector = calloc( row, sizeof( double));

    printf("%p\n", vector);

    int32_t counter = 0;

    double **dr_matrix = allocate_matrix( row, col);

    do
    {
        copy_vector( new, guess, row);

        double *R = calloc( row, sizeof( double));

        set_dist( R, row, guess);

        set_Dr( guess, dr_matrix, row);

        double **dr_matrix_T = transpose_matrix( dr_matrix, row, col);

        // testing
        printf("DR_matrix\n");
        print_matrix( dr_matrix, row, col);
        printf("DR_matrix_T\n");
        print_matrix( dr_matrix_T, col, row);

        double **left = allocate_matrix( col, col);

        matrix_multi_double( left, col, col, dr_matrix_T, dr_matrix, row);
        printf("left\n");
        print_matrix( left, col, col);

        double *right = calloc( col, sizeof( double));

        set_right( right, dr_matrix_T, col, row, R);

        printf("right\n");
        for ( int k = 0 ; k < col; k += 1)
        {
            printf("  %lf\n", right[ k]);
        }

        PALU( col, col, right, left);

        matrix_add( right, guess, new, row);

        counter++;

        printf("%d\n", counter);

        for ( int32_t i = 0; i < col; i++)
        {
            printf("%lf %lf\n", new[ i], guess[ i]);
        }

        // printf("%lf\n", min_distance( new, guess, row));

        free_matrix( dr_matrix_T, col, row);

        free_matrix( left, col, col);

        free( right);

        free( R);

    } while ( min_distance( new, guess, row) > ERROR);

    // printf("%p\n", vector);
    free( vector);

    vector = NULL;

    free_matrix( dr_matrix, row, col);



    free_matrix( df_matrix, row, row);

    free( guess);

    guess = NULL;


    free( new);

    new = NULL;

    return 0;
}

void set_dist( double *dist, int row, double *guess)
{
    for ( int i = 0 ; i < row; i+= 1)
    {
        dist[ i] = sqrt( pow( guess[ 0] - x[ i], 2) + pow( guess[ 1] - y[ i], 2) ) - r[ i];
    }// for i
    return;
}

void set_Dr( double *guess, double **matrix, int row)
{
    for ( int i = 0 ; i < row; i += 1)
    {
        double S = sqrt( pow( guess[ 0] - x[ i], 2) + pow( guess[ 1] - y[ i], 2) );

        matrix[ i][ 0] = ( guess[ 0] - x[ i]) / S;

        matrix[ i][ 1] = ( guess[ 1] - y[ i]) / S;
    }// for i
    return;
}

void set_right( double *right, double **dr_matrix_T, int row, int col, double *R)
{
    for ( int i = 0; i < row; i += 1)
    {
        double sum = 0.0;

        for ( int j = 0 ; j < col; j += 1)
        {
            sum += dr_matrix_T[ i][ j] * R[ j];
        }// for j

        right[ i] = sum;
    }// for i

    for ( int i = 0 ; i < row; i+= 1)
    {
        right[ i] *= -1;
    }// for i

    return;
}

void copy_vector( double * const source, double *dest, int32_t row)
{
    for ( int32_t i = 0; i < row; i++)
    {
        dest[ i] = source[ i];
    }// for i

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

void matrix_add( double *a, double *b, double *dest, int32_t row)
{
    for ( int32_t i = 0; i < row; i++)
    {
        dest[ i] = a[ i] + b[ i];
    }// for i

    return;
}

double min_distance( double *a, double *b, int32_t row)
{
    double answer = my_abs( a[ 0] - b[ 0]);

    for ( int32_t i = 0; i < row; i++)
    {
        if ( my_abs( a[ i] - b[ i]) > answer)
        {
            answer = my_abs( a[ i] - b[ i]);
        }// if

    }// for i

    return answer;
}

void set_guess( double *guess)
{
    guess[ 0] = 0;

    guess[ 1] = 0;

    return;
}

void set_minus_f( double *guess, double * const vector)
{
    vector[ 0] = guess[ 0] + guess[ 1] + guess[ 2] - 3;

    vector[ 1] = pow( guess[ 0], 2) + pow( guess[ 1], 2) + pow( guess[ 2], 2) - 5;

    vector[ 2] = pow( M_E, guess[ 0]) + guess[ 0] * guess[ 1] - guess[ 0] * guess[ 2] - 1;

    for ( int32_t i = 0; i < 3; i++)
    {
        vector[ i] = vector[ i] * ( -1);
    }// for i

    return;
}

void set_df_matrix( double *guess, double **matrix)
{
    matrix[ 0][ 0] = ( guess[ 0] - X1) / sqrt( pow( guess[ 0] - X1, 2) + pow( guess[ 1] - Y1, 2));
    matrix[ 0][ 1] = ( guess[ 0] - X2) / sqrt( pow( guess[ 0] - X2, 2) + pow( guess[ 1] - Y2, 2));
    matrix[ 0][ 2] = ( guess[ 0] - X3) / sqrt( pow( guess[ 0] - X3, 2) + pow( guess[ 1] - Y3, 2));

    matrix[ 1][ 0] = ( guess[ 0] - Y1) / sqrt( pow( guess[ 0] - X1, 2) + pow( guess[ 1] - Y1, 2));
    matrix[ 1][ 1] = ( guess[ 0] - Y2) / sqrt( pow( guess[ 0] - X2, 2) + pow( guess[ 1] - Y2, 2));
    matrix[ 1][ 2] = ( guess[ 0] - Y3) / sqrt( pow( guess[ 0] - X3, 2) + pow( guess[ 1] - Y3, 2));

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

    matrix_multi( P, answer_vector, buffer, row, col, row, 1);

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

void free_matrix( double **matrix, int row, int col)
{
    // free the matrix
    for ( int i = 0; i < row; i++)
    {
        free( matrix[ i]);

        matrix[ i] = NULL;
    }// for i

    free( matrix);

    matrix = NULL;

    return;
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

void get_matrix( double **matrix, int row, int col)
{
    for ( int i = 0; i < row; i++)
    {
        printf("enter the %d row\n", i + 1);

        for ( int j = 0 ; j < col; j++)
        {
            scanf("%lf", &(matrix[ i][ j]));
        }// for j

    }// for i
    return;
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

void print_matrix_P( int **matrix, int row, int col)
{
    for ( int i = 0; i < row; i ++)
    {
        for ( int j = 0; j < col; j++)
        {
            printf("%d ", matrix[ i][ j]);
        }//for j
        printf("\n");
    }// for i

    return;
}

void matrix_multi_double( double **dest, int row, int col, double **a, double **b, int col_a)
{
    for ( int i = 0; i < row; i++)
    {
        for ( int j = 0; j < col; j++)
        {
            double sum = 0;

            for ( int k = 0; k < col_a; k++)
            {
                sum += a[ i][ k] * b[ k][ j];

            }// for col_a

            dest[ i][ j] = sum;

            // printf("%lf\n", sum);
        }// for col_b

    }// for row_a

   return;
}
void matrix_multi( int **a, double *b, double *dest, int row_a, int col_a, int row_b, int col_b)
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

double my_abs( double a)
{
    if ( a < 0)
    {
        return ( -1) * a;
    }// if

    return a;
}
