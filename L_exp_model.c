#include <iostream>
#include <cmath>
#include <stdio.h>

#define N 4
#define C 2
#define PI 3.1415926

using namespace std ;

/*

y = c1*e^(c2*t)
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