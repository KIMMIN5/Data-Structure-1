#define MAX_TERM 100

#include <stdio.h>

typedef struct {
    int degree ;
    float coef[MAX_TERM] ;
} polynomial ;

polynomial poly_mul(polynomial a, polynomial b) {
    polynomial c ;
    c.degree = a.degree + b.degree ;
    int i, j ;

    for(i=0; i<a.degree+b.degree; i++) {
        c.coef[i] = 0 ;
    }

    for(i=0; i<=a.degree; i++) {
        for(j=0; j<=b.degree; j++) {
            c.coef[i+j] += a.coef[i] * b.coef[j] ;
        }
    }
    return c ;
}

void print_poly(polynomial p) {
    for(int i=p.degree; i>0; i--) {
        printf("%.1fx^%d + ", p.coef[p.degree - i], i) ;
    }
    printf("%.1f\n", p.coef[p.degree]) ;
}

int main() {
    polynomial a = {3,{4,3,2,1}} ;
    polynomial b = {2,{3,2,8}} ;

    polynomial c = poly_mul(a,b) ;
    print_poly(c) ;

    return 0 ;
}