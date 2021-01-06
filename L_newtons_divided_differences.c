#include <stdio.h>

#define MAX_POINTS 4

double x[ MAX_POINTS] = {-1,0,1,2};

double y[ MAX_POINTS] = {1,1,2,0};

double c[ MAX_POINTS][ MAX_POINTS] = { 0};

double p[ MAX_POINTS] = { 0};

double set_c( int start, int end);

void set_p( double input, int length);

double ans( double input);

int main( void)
{
    set_c( 1, MAX_POINTS);

    for ( int j = 0; j < MAX_POINTS + 1; j++)
    {
        for ( int i = 0; i < MAX_POINTS + 1; i++)
        {
            printf("%lf ", c[ i][ j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Input:\n");

    double input = 0.0;

    scanf("%lf", &input);

    // set_p( input, MAX_POINTS);

    printf("ANS = %lf\n", ans( input));

    return 0;
}

double set_c( int start, int end)
{
    if ( start == end)
    {
        c[ start][ end] = y[ start - 1];

        return c[ start][ end];
    }

    c[ start][ end] = ( set_c( start + 1, end) - set_c( start, end - 1)) / ( x[ end - 1] - x[ start - 1]);

    return c[ start][ end];
}

void set_p( double input, int length)
{
    p[ 0] = 1;

    for ( int i = 1; i < length + 1; i++)
    {
        p[ i] = ( input - x[ i - 1]) * p[ i - 1];
        printf("%lf ", p[ i]);
    }// for i

    printf("\n");

    return;
}

double ans( double input)
{
    double ans = c[ 1][ MAX_POINTS];

    /*
    for ( int i = 1; i < MAX_POINTS + 1; i++)
    {
        printf("%lf %lf\n", c[ 1][ i], p[ i - 1]);
        ans += c[ 1][ i] * p[ i - 1];
    }// for i */

    // NOTICE ME PLEASE
    // NOTICE ME PLEASE
    // NOTICE ME PLEASE
    // NOTICE ME PLEASE
    // NOTICE ME PLEASE
    // NOTICE ME PLEASE

    // Hey this is the Horner's Method
    for ( int i = MAX_POINTS - 1; i > 0; i--)
    {
        printf("%lf %lf %lf\n", ans, ( input - x[ i - 1]), c[ 1][ i]);
        ans = ans * ( input - x[ i - 1]) + c[ 1][ i];
    }// for i

    // NOTICE ME PLEASE
    // NOTICE ME PLEASE
    // NOTICE ME PLEASE
    // NOTICE ME PLEASE
    // NOTICE ME PLEASE

    return ans;
}
