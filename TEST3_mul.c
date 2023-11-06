#define MAX_DEGREE 101

#include <stdio.h>

typedef struct {
    int degree ; //최고차수
    float coef[MAX_DEGREE] ; // 계수
} polynomial;

polynomial poly_mult(polynomial A, polynomial B) 
{
    polynomial C ;

    int i, j ;
    for(i=0; i<=A.degree + B.degree; i++) {
        C.coef[i] = 0 ;
    }
    C.degree = A.degree + B.degree ;

    for(i=0; i<=A.degree; i++) {
        for(j=0; j<=B.degree; j++) {
            C.coef[i+j] += A.coef[i] * B.coef[j] ;
        }
    }
    return C ; 
}

void print_poly(polynomial p) 
{
    for (int i = p.degree; i>0; i--)
        printf("%.1fx^%d + ", p.coef[p.degree - i], i) ;
    printf("%.1f\n", p.coef[p.degree]) ;    
}

int main() {
polynomial a = {3,{4, 3, 2, 1}} ;
polynomial b = {2,{3, 2, 8}} ;
polynomial c ;
print_poly(a) ;
print_poly(b) ;
c = poly_mult(a, b) ;
printf("--------------------------------------------------\n") ;
print_poly(c) ;
return 0 ;
}