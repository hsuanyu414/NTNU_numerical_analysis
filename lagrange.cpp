#include <iostream>
#include <stdio.h>

#define N 4

using namespace std ;

int main()
{
	double x[N] = {1960,1970,1990,2000};
	double y[N] = {3039585530,3707475887,5281653820,6079603571};
	//guess 1980 ;
	double x_ = 1980 ;
	double y_ = 0 ;

	for(int i = 0 ; i < N ; i ++)
	{
		double up = y[i] ;
		double down = 1 ;
		for(int j = 0 ; j < N ; j ++)
		{
			if(j!=i)
			{
				up *= (x_-x[j]) ;
				down *= (x[i]-x[j]) ;
			}
		}
		y_ += up/down ;
	}

	printf("%lf\n", y_);
	return 0 ;
}