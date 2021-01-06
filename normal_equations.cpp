#include <iostream>
#include <cmath>
#include <stdio.h>

#define N 12
#define C 4
#define PI 3.1415926

using namespace std ;

/*
0 6.224
1 6.665
2 6.241
3 5.302
4 5.073
5 5.127
6 4.994
7 5.012
8 5.108
9 5.377
10 5.510
11 6.372

y = c1 + c2 cos2πt + c3 sin2πt + c4 cos4πt
*/

float _abs(float x)
{
	if(x<0)
		return -1*x;
	return x ;
}



int main()
{
	double t[N] = {0};
	double b[N] = {0};
	for(int i = 0 ; i < N ; i ++)
		cin >> t[i] >> b[i] ;
	for(int i = 0 ; i < N ; i ++)
		t[i] /= 12 ;
	double A[N][C] = {0};
	for(int i = 0 ; i < N ; i ++)
	{
		A[i][0] = 1 ;
		A[i][1] = cos(2*PI*t[i]) ;
		A[i][2] = sin(2*PI*t[i]) ;
		A[i][3] = cos(4*PI*t[i]) ;
	}
	double At[C][N] = {0};
	for(int i = 0 ; i < C ; i ++)
		for(int j = 0 ; j < N ; j ++)
			At[i][j] = A[j][i];
	//At*A C*C
	double AtA[C][C] = {0} ;
	for(int i = 0 ; i < C ; i ++)
		for(int j = 0 ; j < C ; j ++)
			for(int k = 0 ; k < N ; k ++)
				AtA[i][j] += At[i][k]*A[k][j] ;
	double Atb[C] = {0} ;
	for(int i = 0 ; i < C ; i ++)
		for(int j = 0 ; j < N ; j ++)
			Atb[i] += At[i][j]*b[j] ;

	cout << "AtA matrix" << endl ;
	for(int i = 0 ; i < C ; i ++)
	{
		for(int j = 0 ; j < C ; j ++)
			printf("%lf	", AtA[i][j]);
		cout << "\n" ;
	}

	cout << "Atb matrix" << endl ;
	for(int i = 0 ; i < C ; i ++)
	{
		printf("%lf\n", Atb[i]);
	}

	for (int i = 0; i < C ; i ++)
	{
		printf("c%d = %lf\n", i , Atb[i]/AtA[i][i]);
	}

	double b_[N] = {0} ;
	double SE = 0 ;
	for(int i = 0 ; i < N ; i ++)
		for(int j = 0 ; j < C ; j ++)
			b_[i] += A[i][j] * (Atb[j]/AtA[j][j]) ;
	for(int i = 0 ; i < N ; i ++)
		SE += pow(b[i]-b_[i],2) ;
	SE /= N ;
	SE = sqrt(SE) ;
	printf("%lf\n", SE);



	return 0 ; 
}