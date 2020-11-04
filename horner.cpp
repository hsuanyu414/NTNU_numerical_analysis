#include <iostream>

using namespace std;

double horner(double num)
{
    double answer = num;
    for(int i = 0 ; i < 49; i ++)
    {
        answer += 1 ;
        answer *= num ;
    }
    answer +=1;
    return answer ;
}//把x一個一個提出來加下去之後再乘

int main()
{
    printf("f(x) = 1+x^2+x^3......+x^50\n");
    printf("please enter x \n");

    double a = 1.0001 ;
    double b = 0.5 ;

    printf("%lf\n" , horner(a));
    printf("%lf\n" , horner(b));
    

}