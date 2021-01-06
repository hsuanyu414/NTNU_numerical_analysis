#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

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
float _abs(float x)
{
	if(x<0)
		return -1*x;
	return x ;
}

void print_matrix(float m[][4])
{
	for(int i = 0 ;i < 3 ; i ++)
	{
		for(int j = 0 ; j < 4 ; j ++)
			cout << m[i][j] << "\t\t"  ;
		cout << "\n";
	}
	cout << "\n\n" ;
	return ;
}

int main()
{	
	int n,i,j,k,l;
	int row_tmp ;
	n = 3 ;
	float s[3] = {1,2,3} ;//初始猜測(x,y,z)=(1,1,1)
	float s_2[3] = {0,0,0};
	float answer[3] = {0,0,0} ;
	for(int time = 0 ; time < 10 ; time ++)
	{
		float a[3][3] ={
		{                    1,      1,       1 },
		{               2*s[0], 2*s[1],  2*s[2] },
		{  exp(s[0])+s[1]-s[2],   s[0], -1*s[0]}
		};
		float b[3]={(-1)*(s[0]+s[1]+s[2]-3), (-1)*(s[0]*s[0]+s[1]*s[1]+s[2]*s[2]-5) , (-1)*(exp(s[0])+s[0]*s[1]-s[0]*s[2]-1)}

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
		cout << "x = " << answer[0] << endl ;
		cout << "y = " << answer[1] << endl ;
		cout << "z = " << answer[2] << endl ;
		cout << "TEST" << endl ;
		s_2[0] = s[0] + answer[0] ;
		s_2[1] = s[1] + answer[1] ;
		s_2[2] = s[2] + answer[2] ;
		s[0] = s_2[0] ;
		s[1] = s_2[1] ;
		s[2] = s_2[2] ;
	}

}