#include <iostream>

using namespace std ;

int main()
{
	int n,i,j,k;

	cout << "Please enter the number of the variable:" ;
	cin >> n ;
	//float matrix[n][n+1] = {0};
	float matrix[4][5] = {{2,1,0,0,1},{0,1,2,0,1},{2,4,5,1,2},{8,5,0,3,0}};
	
	float A ;
	float Q[n+1];
	float answer[n] ;
	//for input
	/*
	for(int i = 0 ; i < n ; i ++)
	{
		cout << "Please enter the " << i+1 << " equation" ;
		for(int j = 0 ; j < n ; j ++)
			cin >> matrix[i][j] ;
		cin >> matrix[i][n];
	}
	*/
	for(int i = 0 ; i < n ; i ++)
	{
		if(matrix[i][i] ==0)
		{
			j = i+1;
			while(matrix[j][i] == 0)
				j ++ ;
			if(n <= j)
			{
				cout << "error" << endl ;
				return 0 ;
			}
			cout << j ;
			for(int k = 0 ; k < n+1 ; k ++)
			{
				Q[k] = matrix[i][k];
				matrix[i][k] = matrix[j][k];
				matrix[j][k] = Q[k];

			}
		}
		for(int j = 0 ; j < n ; j ++)
			if(i != j)
			{
				A = matrix[j][i]/matrix[i][i];
				for(int k = 0 ; k < n+1 ; k ++)
					matrix[j][k] = ((-1)*(A)) * matrix[i][k] + matrix[j][k];
			}
	}

	for(int i = 0 ; i < n ; i ++)
		for(int j = 0 ; j < n ; j ++)
			answer[i] = matrix[i][n]/matrix[i][i];
	cout << "x = " << answer[0] << endl ;
	cout << "y = " << answer[1] << endl ;
	cout << "z = " << answer[2] << endl ;
	cout << "w = " << answer[3] << endl ;

	return 0 ;
}