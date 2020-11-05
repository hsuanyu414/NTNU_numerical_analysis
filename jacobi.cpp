#include <iostream>

using namespace std ;

void print_matrix(double a[][10])
{
	int i=0;
	int j=0;
	for(i = 0 ; i < 10 ; i ++)
	{
		for(j = 0 ; j < 10 ; j ++)
			printf(" %3.f", a[i][j]);
		cout << "\n" ;
	}
	return ;
}

int main()
{
	double A[10][10] = {0.0} ;
	double b[10] = { 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0} ;
	double x[10] = { 0.0 } ;
	int i,times,j;
	for( i = 0 ; i < 10 ; i ++)
	{
		A[i][i] = 3 ;
		if(i == 9)
			break ;
		A[i][i+1] = -1 ;
		A[i+1][i] = -1 ;
	}//init the matrix by the given question
	print_matrix(A);

	double D[10][10] = {0};
	double L_U[10][10] = {0};
		
	for( times = 0 ; times < 1000 ; times ++)
	{	
		for (int i = 0; i < 10; i ++)
			for( j = 0 ; j < 10 ; j ++)
			{
				D[i][j] = 0 ; 
				L_U[i][j] = 0 ;
			}
		for( i = 0 ; i < 10 ; i ++)
			for( j = 0 ; j < 10 ; j ++)
			{
				if(i == j)
					D[i][j] = 1/A[i][j] ;
				else
					L_U[i][j] = A[i][j] ;
			}

		double temp[10] = { 0.0 } ;

		for( i = 0 ; i < 10 ; i ++)
		{	
			temp[i] = b[i] ;
			for( j = 0 ; j < 10 ; j ++)
				temp[i] -= L_U[i][j] * x[j];
		}

		for( i = 0 ; i < 10 ; i ++)
		{
			x[i] = 0 ; 
			for( j = 0 ; j < 10 ; j ++)
				x[i] += D[i][j] * temp[i];
		}
	}
	for( i = 0 ; i < 10 ; i ++)
		printf("%lf\n" ,x[i]);
	return 0 ;
}