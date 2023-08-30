#include <stdio.h>

int main(void) {
    int sum = 0 ;
    int i ;
    int j ;

    for (i=0; i<=100; i++) {
        for (j=2; j<=i; j++) {
            if(j == i) {
                sum += i ;
            }
            if(i%j == 0) break ;
        }
    }
    printf("0부터 100까지 소수들의 합 : %d\n", sum) ;
}   