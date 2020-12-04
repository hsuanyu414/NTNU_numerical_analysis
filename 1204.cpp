#include <stdio.h>
#define n 4
/*
1800 280
1850 283
1900 291
1950 ???
2000 370
*/

int main()
{
int i = 0,j = 0;

double x[n] = {1800,1850,1900,2000} ;
double y[n] = {280,283,291,370};

double P = 0;//ans_y

double ans_x = 1950;

double array[n][n] = {0};

for(i = 0; i < n; i++)
{
array[0][i] = y[i];
}

for(j = 1;j < n ; j++)
{
for(i = 0;i < n - j; i++)
{
array[j][i] = (array[j - 1][i + 1] - array[j - 1][i]) / (x[i + j] - x[i]);
}
}
/*
for(i = 0;i < n; i++)
{
for(j = 0 ; j < n; j++)
{
printf("%lf\t",array[j][i]);
}
printf("\n");
}
*/
for(i = 0; i < n ; i++)
{
double tmp = 0;
tmp = array[i][0];
for(j = 0 ; j < i; j++)
{
tmp = tmp * (ans_x - x[j]);
}
P += tmp;
}

printf("%lf",P);

//for(i = 0;i < n; i++)
//printf("%lf",array[i][0]);
}
