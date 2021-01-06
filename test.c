#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
x   + y   + z   = 3
x^2 + y^2 + z^2 = 5
e^x + xy  - xz  = 1
*/

//DF(x,y,z)
/*
1       1   1
2x      2y  2z
e^x+y-z x   -x
*/


int main()
{	
	int n,i,j,k,l;
	int row_tmp ;
	n = 3 ;
	double x_0[3] = {1,0,1} ;//初始猜測(x,y,z)=(1,1,1)
	double x_1[3] = {0,0,0};
	double answer[3] = {0,0,0} ;
	for(int time = 0 ; time < 100 ; time ++)
	{
		double a[3][3] ={
		{                    1,      1,       1 },
		{               2*x_0[0], 2*x_0[1],  2*x_0[2] },
		{  exp(x_0[0])+x_0[1]-x_0[2],   x_0[0], -1*x_0[0]}
		};
		double b[3]={(-1)*(x_0[0]+x_0[1]+x_0[2]-3), (-1)*(x_0[0]*x_0[0]+x_0[1]*x_0[1]+x_0[2]*x_0[2]-5) , (-1)*(exp(x_0[0])+x_0[0]*x_0[1]-x_0[0]*x_0[2]-1)};	

		double max = 0;
		int row_tmp = 0;
		
		//交換 
		for ( i = 0; i < n; ++i)
		{
			max = a[i][i]; 
			row_tmp = i;
			for( j = i + 1 ; j < n ; j++)
			{	
				if( abs(max) <= abs(a[j][i]) )
				{
					max = abs(a[j][i]);
					row_tmp = j;
				}
			}
			double swap_tmp = 0;
			for( j = 0 ; j < n ; j++)
			{
				swap_tmp = a[i][j];
				a[i][j] = a[row_tmp][j];
				a[row_tmp][j] = swap_tmp;
			}
			
			swap_tmp = b[i];
			b[i] = b[row_tmp];
			b[row_tmp] = swap_tmp;
		
			double A = 0;
		
			for(k = i + 1; k < n ; k++ )
	    	{	
		    	A = a[k][i] / a[i][i];

		        for(j = 0;j < n; j++)
		        {            
			    	a[k][j] = a[k][j] - A * a[i][j]; 
		        }
		        b[k] = b[k] - A * b[i];
			}	
		}
		for( i = 0 ; i < n ; i ++)
			for( j = 0 ; j < n ; j ++)
				answer[i] = b[i]/a[i][i];
	
		x_1[0] = x_0[0] + answer[0] ;
		x_1[1] = x_0[1] + answer[1] ;
		x_1[2] = x_0[2] + answer[2] ;
		x_0[0] = x_1[0] ;
		x_0[1] = x_1[1] ;
		x_0[2] = x_1[2] ;
	}
	printf("x=%lf\n", x_1[0]);
	printf("y=%lf\n", x_1[1]);
	printf("z=%lf\n", x_1[2]);
}