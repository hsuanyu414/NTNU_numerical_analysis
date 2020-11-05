
#include <iostream>
#include <math.h>

#define f1(x) pow(x,3.0)-9
#define f2(x) x-pow(x,1.0/3)-2

using namespace std;

double bis_1(double a , double b)
{//x^3-9
    double mid = (a+b)*0.5;

    double mid_out = f1(mid);
    //pow(mid , 3.0) - 9 ;//計算mid帶入後f(x)的值
    if( mid_out > -0.00001 && mid_out < 0.00001 )//終止條件
        return mid ;
    else if( mid_out > 0)//往右邊靠 往左邊(a)<-(mid)(b)修正
        return bis_1(a,mid) ;
    else 
        return bis_1(mid , b);//跟上面恰恰相反
    
}

double bis_2(double a , double b)
{
    double mid = (a+b)*0.5;

    double asd = (1.0/3) ;
    double mid_out = f2(mid);
    //mid - pow(mid , asd) - 2 ;
    
    if( mid_out > -0.00001 && mid_out < 0.00001 )
        return mid ;
    else if( mid_out > 0)
        return bis_2(a , mid) ;
    else
        return bis_2(mid , b) ;
    
}

int main()
{
    printf("%lf\n" , bis_1(2.0,3.0)) ;
    printf("%lf\n" , bis_2(3.0,4.0)) ;
}