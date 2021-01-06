#include <iostream>
#include <stdio.h>

using namespace std ;

#define N 4

/*
1800 280
1850 283
1900 291
2000 370
*/

int main()
{
	float x[N] = {-1,0,1,2} ;
	float ans_x = 0 ;
	int i,j = 0 ;
	float _1 = 1 ;
	float _2 = 1 ;
	float _3 = 2 ;
	float _4 = 0 ;
	float _12 = (_2-_1)/(x[1]-x[0]);
	float _23 = (_3-_2)/(x[2]-x[1]);
	float _34 = (_4-_3)/(x[3]-x[2]);
	float _123 = (_23-_12)/(x[2]-x[0]);
	float _234 = (_34-_23)/(x[3]-x[1]);
	float _1234 = (_234-_123)/(x[3]-x[0]);
	cout << _34 << endl ;
	float ans_y = 0 ;
	ans_y += _1;
	ans_y += _12*(ans_x-x[0]);
	ans_y += _123*(ans_x-x[0])*(ans_x-x[1]);
	ans_y += _1234*(ans_x-x[0])*(ans_x-x[1])*(ans_x-x[2]);
	
	
	float _ans = ((_1234*(ans_x-x[2])+_123)*(ans_x-x[1])+_12)*(ans_x-x[0])+_1 ;
	
	printf("%f",ans_y);
	
	printf("%f",_ans);
		
	return 0 ;
}
