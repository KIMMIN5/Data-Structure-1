#include <stdio.h>

double factorial_iter(int n)
{
    int i ;
    double result = 1 ;
    for(i = 1; i <= n; i++)
    {
        result = result * i ;
    }
    return(result) ;
}

double factorial_rec(int n)
{
    if(n<=1) return (1);
    
    return (n * factorial_rec(n-1)) ;
}

int main(void) 
{
    int n = 20 ;
    
    double result_iter = factorial_iter(n) ;
    double result_rec = factorial_rec(n) ;
    
    printf("%f\n", result_iter) ;
    printf("%f\n", result_rec) ;    
}