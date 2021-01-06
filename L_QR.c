#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define V_LENGTH(matrix,col_num,output) output = 0;\
                                        for ( int REEEEEEEE = 0 ; REEEEEEEE < ROW; REEEEEEEE += 1)\
                                        {\
                                            output += pow( matrix[ REEEEEEEE][ col_num], 2);\
                                        }\
                                        output = sqrt( output)

#define DOT(a,a_col_num,b,b_col_num,output) output = 0;\
                                            for ( int REEEEEEEE = 0 ; REEEEEEEE < ROW; REEEEEEEE += 1)\
                                            {\
                                                output += a[ REEEEEEEE][ a_col_num] * b[ REEEEEEEE][ b_col_num];\
                                            }

double **allocate_matrix( int row, int col);
double **transpose_matrix( double **matrix, int row, int col);
void free_matrix( double **matrix, int row, int col);
void matrix_multi( double **a, double **b, double **dest, int row_a, int col_a, int row_b, int col_b);
void copy_matrix( double **source, double ** dest, int row, int col);
void print_matrix( double **matrix, int row, int col);

void QR( double **matrix, int row, int col, double **ans);

#define ROW 4
#define COL 3

/*
4 8 1
0 2 -2
3 6 7
*/

int main( void)
{
    printf("Enter a matrix that is %d X %d\n", ROW, COL);

    double **matrix = allocate_matrix( ROW, COL);

    for ( int i = 0 ; i < ROW; i += 1)
    {
        for ( int j = 0 ; j < COL; j += 1)
        {
            scanf("%lf", &( matrix[ i][ j]));
        }// for j
    }// for i

    printf("Matrix\n");

    print_matrix( matrix, ROW, COL);

    double **ans = allocate_matrix( ROW, 1);

    printf("Enter ans:\n");

    for( int i = 0; i < ROW; i += 1)
    {
        scanf("%lf", &ans[ i][ 0]);
    }// for i

    QR( matrix, ROW, COL, ans);

    printf("ANS\n");

    print_matrix( ans, ROW, 1);

    free_matrix( ans, ROW, 1);

    free_matrix( matrix, ROW, COL);

    return 0;
}

void QR( double **matrix, int row, int col, double **ans)
{
    double **Q = allocate_matrix( row, col);

    double **R = allocate_matrix( col, col);

    copy_matrix( matrix, Q, row, col);

    for ( int i = 0; i < col; i += 1)
    {
        // for the y to q process
        for ( int k = 0; k < i; k += 1)
        {
            double dot = 0.0;

            DOT( matrix, i, Q, k, dot);

            R[ k][ i] = dot;

            //printf("dot %d %lf\n", k, dot);

            for ( int l = 0; l < row; l += 1)
            {
                Q[ l][ i] -= Q[ l][ k] * dot;
            }// for l
        }// for k

        // getting the length out
        double length = 0.0;

        V_LENGTH( Q, i, length);

        //printf("length col %d %lf\n", i, length);

        R[ i][ i] = length;

        for ( int j = 0; j < row; j += 1)
        {
            Q[ j][ i] = Q[ j][ i] / length;
        }// for j
    }// for i

    printf("Q\n");

    print_matrix( Q, row, col);

    printf("R\n");

    print_matrix( R, col, col);


    // set Rx = Q_T * ans
    double **Q_T = allocate_matrix( col, row);

    Q_T = transpose_matrix( Q, row, col);

    double **temp = allocate_matrix( row, 1);

    matrix_multi( Q_T, ans, temp, col, row, row, 1);

    copy_matrix( temp, ans, row, 1);

    free_matrix( temp, row, 1);

    free_matrix( Q_T, col, row);



    // solve X
    for ( int i = row - 1; i >= 0; i--)
    {
        for ( int j = row - 1; j > i; j--)
        {
            ans[ i][ 0] -= ans[ j][ 0] * R[ i][ j];
        }// for j

        ans[ i][ 0] /= R[ i][ i];
    }// for i





    free_matrix( Q_T, col, row);

    free_matrix( R, col, col);

    free_matrix( Q, row, col);

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


