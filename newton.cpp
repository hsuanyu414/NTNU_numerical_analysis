#include <iostream>
#include <math.h>

using namespace std;

// find the newtom x^3+x-1=0
double equation_1(double a)//x^5 + x - 3 = 0
{
    return (pow(a,5.0) + a - 3.0) ;
}
double dx_equation_1(double a)//5x^4 + 1 = 0
{
    return (5.0*pow(a,4.0) + 1 ) ;
}

double equation_2(double a)//   lnx + 2x^2 - 3 = 0
{
    return (log(a) + 2.0*(pow(a,2.0)) - 3.0) ;
}
double dx_equation_2(double a)//   1/x + 4x = 0
{
    return ((1.0/a) + 4*a) ;
}

double newton_1(double a)
{
    double minus = (equation_1(a)/dx_equation_1(a));//算出要減的東西
    if(minus > -0.000001 && minus < 0.000001)//終止條件
        return a ;
    else
        return newton_1(a-minus) ;//進入下一個迭代
    
}

double newton_2(double a)
{
    double minus = (equation_2(a)/dx_equation_2(a));
    if(minus > -0.000001 && minus < 0.000001)
        return a ;
    else
        return newton_2(a-minus) ;
}

int main()
{
    int init = 1 ;//給定一個初始猜想
    printf("%4lf\n" , newton_1(init));
    printf("%4lf\n" , newton_2(init));

    return 0 ;
}