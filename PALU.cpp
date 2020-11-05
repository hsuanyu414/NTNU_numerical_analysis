#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std ;
/* 
4x  + 2y - 1z      = 16.9
3x  - 4y + 2z   5w = -14
-2x + 6y - 5z - 2w = 25
5x  + 1y + 6z - 3w = 9.4
*/
int main()
{
    int n = 4;
    int i,j,k;
    double P[4][4] = 
    {
        {1.0,0.0,0.0,0.0},
        {0.0,1.0,0.0,0.0},
        {0.0,0.0,1.0,0.0},
        {0.0,0.0,0.0,1.0}   
    };
    double a[4][4] =
    {
        { 1.0 ,  0.0 ,  0.0 , 1.0 },
        {-1.0 ,  1.0 ,  0.0 , 1.0 },
        {-1.0 , -1.0 ,  1.0 , 1.0 },
        {-1.0 , -1.0 , -1.0 , 1.0 }  
    };

    double L[4][4] = 
    {
        {0.0 , 0.0 , 0.0 , 0.0},
        {0.0 , 0.0 , 0.0 , 0.0},
        {0.0 , 0.0 , 0.0 , 0.0},
        {0.0 , 0.0 , 0.0 , 0.0}   
    };
    double U[4][4] = 
    {
        {0.0 , 0.0 , 0 , 0},
        {0.0 , 0.0 , 0 , 0},
        {0.0 , 0.0 , 0 , 0},
        {0.0 , 0.0 , 0 , 0}   
    };

    
    double max = 0;
    int row_tmp = 0;
    for ( i = 0; i < n; ++i)
    {
        //取每一個col最大值
        //printf("第%d次\n\n",i);
        max = a[i][i]; 
        row_tmp = i ;
        for( j = i + 1 ; j < n ; j++)
        {
            if( abs(max) < abs(a[j][i]) )
            {
                max = abs(a[j][i]);
                row_tmp = j;
            }
        }
        //跟最大的那列交換
        double swap_tmp = 0;
        for( j = 0 ; j < n ; j++)
        {
            swap_tmp = a[i][j];
            a[i][j] = a[row_tmp][j];
            a[row_tmp][j] = swap_tmp;
            swap_tmp = P[i][j];
            P[i][j] = P[row_tmp][j];
            P[row_tmp][j] = swap_tmp;
            swap_tmp = L[i][j];
            L[i][j] = L[row_tmp][j];
            L[row_tmp][j] = swap_tmp;
        }

        double A = 0; //要減幾倍使其他列等於0
        for (k = i + 1;k < n;k++)
        {
            A = a[k][i] / a[i][i];
            //printf("A = %.2f\n",A); //印出倍數
            L[k][i] = A;
            for(j = 0;j < n; j++)
            {            
                a[k][j] = a[k][j] - A * a[i][j]; //相減
            }
        }
        /*相減完的結果
        for( k = 0;k < n ; k++)
        {
            for( j = 0;j < n ; j++)
            {
                printf("%.2f ",a[k][j] );
            }
            printf("\n");
        }
        printf("\n");
        */
        /*做完後P=多少
        for( k = 0;k < n ; k++)
        {
            for( j = 0;j < n ; j++)
            {
                printf("%d ",P[k][j] );
            }
            printf("\n");
        }
        */
    }
    printf("P:\n");
    for( k = 0;k < n ; k++)
    {
        for( j = 0;j < n ; j++)
        {
            printf("%.f   ",P[k][j] );
        }
        printf("\n\n");
    }
/*
    printf("A:\n");
    for( k = 0;k < n ; k++)
    {
        for( j = 0;j < n ; j++)
        {
            printf("%.2f   ",a[k][j] );
        }
        printf("\n\n");
    }
*/
    printf("L:\n");
    for( k = 0;k < n ; k++)
    {   
        L[k][k] = 1;
        for( j = 0;j < n ; j++)
        {
            printf("%.2f   ",L[k][j] );
        }
        printf("\n\n");
    }
    printf("U:\n");
    for( k = 0;k < n ; k++)
    {   
        for( j = 0;j < n ; j++)
        {   
            U[k][j] = a[k][j];//計算的那個A最終結果是U
            printf("%.2f   ",U[k][j] );
        }
        printf("\n\n");
    }
    return 0;
}