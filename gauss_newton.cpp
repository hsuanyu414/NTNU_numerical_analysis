#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std ;
/*
Circle 1: (-1,  0) R = 1
Circle 2: ( 1,  1) R = 1
Circle 3: ( 1, -1) R = 1
*/

int main()
{
	double cp[3][2]= {
		{-1 ,  0 },
		{ 1 ,  1 },
		{ 1 , -1 }
	};

	double x0[2] = { 0 , 0 } ; // 初始猜測向量 [x0,y0]T
	double x1[2] = { 0 , 0 } ; // 之後的向量　 [xi,ti]T
	double r_[3] = {1,1,1} ;
	double ans[2] = { 0 , 0} ;
	int time ;
	int n = 2 ;
	int i,j,k ;
	for( time = 0 ; time < 10 ; time ++)
	{
		double DrxkT[2][3] = { 0 } ;
		double Drxk[3][2]  = { 0 } ;
		double a[2][2] = { 0 } ;
		for( i = 0 ; i < 3 ; i ++)
			for ( j = 0 ; j < 2 ; j ++)	
				Drxk[i][j] = (x0[j]-cp[i][j])/sqrt(pow(x0[0]-cp[i][0],2)+pow(x0[1]-cp[i][1],2)) ;
		for( i = 0 ; i < 3 ; i ++)
			for ( j = 0 ; j < 2 ; j ++)
				DrxkT[j][i] = Drxk[i][j] ;
		for(i = 0 ; i < 2 ; i++)
		{
			for( j = 0 ; j < 2 ; j ++)
			{
				double total = 0 ;
				for( k = 0 ; k < 3 ; k ++)
					total += DrxkT[i][k]*Drxk[k][j] ;
				a[i][j] = total ;
			}
		}
		//左邊的部分
		double r[3] = { 0 } ;
		double b[2] = { 0 } ;
		for(i = 0 ; i < 3 ; i ++)
		{
			r[i] = sqrt(pow(x0[0]-cp[i][0],2.0)+pow(x0[1]-cp[i][1],2.0));
			r[i] -= r_[i] ;
		}
		for(i = 0 ; i < 2 ; i ++)
		{
			double total = 0 ;
			for( j = 0 ; j < 3 ; j ++)
				total -= DrxkT[i][j]*r[j] ;
			b[i] = total ;
		}
		// 右邊的部分

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
				ans[i] = b[i]/a[i][i];
		x0[0] += ans[0] ;
		x0[1] += ans[1] ;
		cout << "x = " << x0[0] << endl ;
		cout << "y = " << x0[1] << endl ;
		for(i=0;i<2;i++)
		{
			for(j=0;j<3;j++)
				cout << DrxkT[i][j] << "\t" ;
			cout << "\n" ;
		}
	}
	return 0 ;
}