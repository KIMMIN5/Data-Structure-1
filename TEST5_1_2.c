#include <stdio.h>

int main() {
    int student_num ;
    int score[student_num] ;
    int average = 0 ; 
    int max = 0 ;
    int sum = 0 ;

    printf("학생 수를 입력하세요 : ") ;
    scanf("%d", &student_num) ;

    printf("학생들의 성적을 입력하세요 : ") ;
    for(int i=0; i<student_num; i++) {
        scanf("%d", &score[i]) ;
        sum += score[i] ;
        if(max<score[i]) {
            max = score[i] ;
        }
    }

    average = sum / student_num ;
    
    printf("평균 : %d \n", average) ;
    printf("최고점수 : %d \n", max) ;

    return 0 ;

}