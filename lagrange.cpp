#include <iostream>
#include <stdio.h>

#define N 11

using namespace std ;

int main()
{
	double x[N] = {-5,-4,-3,-2,-1,0,1,2,3,4,5};
	double y[N] = { 5, 5, 5, 5, 5,5,5,5,5,5,42};
	//guess 1980 ;
	double x_ = 6 ;
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