#include <iostream>
#include <cstdio>
#include <cmath>

#define ROW 3
#define COL 3

using namespace std ;

int main()
{
	double A[ROW][COL] = { 0 } ;
	double Q[ROW][COL] = { 0 } ;
	double R[COL][COL] = { 0 } ;
	
	A[0][0] =  4 ;
	A[0][1] =  8 ;
	A[0][2] =  1 ;
	A[1][0] =  0 ;
	A[1][1] =  2 ;
	A[1][2] = -2 ;
	A[2][0] =  3 ;
	A[2][1] =  6 ;
	A[2][2] =  7 ;

	double len[COL] = { 0 } ;
	double Y[ROW][COL] = { 0 } ;
	for(int i = 0 ; i < COL ; i ++) //先複製過去
		for(int j = 0 ; j < ROW ; j ++)
			Y[j][i] = A[j][i] ;
	
	//第一個col (不用變)
	for(int i = 0 ; i < ROW ; i ++) //計算長度
		len[0] += pow(Y[i][0],2) ;
	len[0] = sqrt(len[0]) ;

	//第二個column
	double y1Tx2 = 0 ;
	double y12 = pow(len[0] , 2 ) ;
	for(int i = 0 ; i < COL ; i ++)
		y1Tx2 += Y[i][0]*A[i][1]/y12 ;
	for(int i = 0 ; i < ROW ; i ++)
		Y[i][1] -= y1Tx2*Y[i][0] ;
	for(int i = 0 ; i < ROW ; i ++) //計算長度
		len[1] += pow(Y[i][1],2) ;
	len[1] = sqrt(len[1]) ;

	//第三個column
	double y1Tx3 = 0 ;
	double y2Tx3 = 0 ;
	double y22 = pow(len[1] , 2 ) ;
	for(int i = 0 ; i < COL ; i ++)
	{
		y1Tx3 += Y[i][0]*A[i][2]/y12 ;
		y2Tx3 += Y[i][1]*A[i][2]/y22 ;
	}
	for(int i = 0 ; i < COL ; i ++)
	{
		Y[i][2] -= y1Tx3*Y[i][0] ;
		Y[i][2] -= y2Tx3*Y[i][1] ;
	}
	for(int i = 0 ; i < ROW ; i ++) //計算長度
		len[2] += pow(Y[i][2],2) ;
	len[2] = sqrt(len[2]) ;

	//單位化
	for(int i = 0 ; i < COL ; i ++)
	{
		double div = len[i] ;
		for(int j = 0 ; j < ROW ; j ++)
			Q[j][i] = Y[j][i]/div ;
	}

	for(int i = 0 ; i < COL ; i ++)
	{
		for(int j = 0 ; j < ROW ; j ++)
			printf("%lf\t", Q[i][j]);
		cout << "\n" ;
	}

	cout << "------------------" << endl ;

	for(int i = 0 ; i < COL ; i ++)
		R[i][i] = len[i] ;
	
	//R[0][1]
	for(int i = 0 ; i < COL ; i ++)
		R[0][1] += Q[i][0]*A[i][1] ;
	//R[0][2]
	for(int i = 0 ; i < COL ; i ++)
		R[0][2] += Q[i][0]*A[i][2] ;
	//R[1][2] =
	for(int i = 0 ; i < COL ; i ++)
		R[1][2] += Q[i][1]*A[i][2] ;
	for(int i = 0 ; i < COL ; i ++)
	{
		for(int j = 0 ; j < COL ; j ++)
			printf("%lf\t", R[i][j]);
		cout << "\n" ;
	}





	return 0 ;
}
