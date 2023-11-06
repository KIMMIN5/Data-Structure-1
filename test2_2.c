#include <stdio.h>

double factorial_iter(int n) {
    
    double result = 1 ;

    for(int i=1; i<=n; i++) {
        result = result * i ;
    }
    return result ;
}

double factorial_rec(int n) {
    if(n<=1) {
        return 1 ;
    }
    else {
        return (n * factorial_rec(n-1)) ;
    }
}

int main() {
    int n = 20 ;

    double result_iter = factorial_iter(n) ;
    double result_rec = factorial_rec(n) ;

    printf("%.0lf\n", result_iter) ;
    printf("%.0lf\n", result_rec) ;
}