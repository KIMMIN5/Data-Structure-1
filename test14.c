#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode { // �떎�빆�떇�쓽 �븯�굹�쓽 �빆�쓣 �쓽誘�
    int coef ;
    int expon ;
    struct ListNode *link ; // �옄湲곗갭議고룷�씤�꽣
} ListNode ;

typedef struct ListType { // �떎�빆�떇 �쟾泥대�� �쓽誘�
    int size ;
    ListNode *head ;
    ListNode *tail ;
} ListType ;

void error(char *message) {
    fprintf(stderr, "\n%s\n", message) ;
}

ListType *create() { 
    ListType *plist = (ListType*)malloc(sizeof(ListType)) ;
    plist -> size = 0 ;
    plist -> head = plist -> tail = NULL ;
    return plist ;
}

void insert_last(ListType *plist, int coef, int expon) {
    ListNode *temp = (ListNode*)malloc(sizeof(ListNode)) ;
    if(temp == NULL) error("메모리 할당 실패") ;
    temp -> coef = coef ;
    temp -> expon = expon ;
    temp -> link = NULL ;
    if(plist -> tail == NULL) { 
        plist -> head = plist -> tail = temp ; 
    }
    else {
        plist -> tail -> link = temp ; 
        plist -> tail = temp ; 
    }
    plist -> size++ ; 
}

void poly_add(ListType *plist1, ListType *plist2, ListType *plist3) {
    ListNode *a = plist1 -> head ;
    ListNode *b = plist2 -> head ;
    int sum ;

    while(a != NULL && b != NULL) { // a && b
        if(a -> expon == b -> expon) {
            sum = a -> coef + b -> coef ;
            if(sum != 0) {
                insert_last(plist3, sum, a -> expon) ;
                a = a -> link ;
                b = b -> link ;
            }
            else {
                insert_last(plist3, sum, a -> expon) ;
                a = a -> link ;
                b = b -> link ;
            }
        }
        else if(a -> expon > b -> expon) {
            insert_last(plist3, a -> coef, a -> expon) ;
            a = a -> link ;
        }
        else { 
            insert_last(plist3, b -> coef, b -> expon) ;
            b = b -> link ;
        }
    }
    for( ; a!=NULL; a=a->link) {
        insert_last(plist3, a->coef, a->expon) ;
    }
    for( ; b!=NULL; b=b->link) {
        insert_last(plist3, b->coef, b->expon) ;
    }
}

void print_poly(ListType *plist) {
    ListNode *p = plist -> head ;

    printf("polynomial = ") ;
    for( ; p; p = p -> link) {
        printf("%dx^%d + ", p -> coef, p -> expon) ;
    }
    printf("\n") ;
}

int get_coef(char *token) {
    int coef ;
    if(strstr(token, "x") != NULL) {
        sscanf(token, "%dx^", &coef) ;
    }
    else {
        coef = atoi(token) ;
    }

    return coef ;
}

int main() {
    ListType *list1 = create() ;
    ListType *list2 = create() ;
    ListType *list3 = create() ;

    char poly1[20] ;
    char poly2[20] ;

    printf("다항식 A를 입력하세요 : ") ;
    scanf("%s", poly1) ;

    char *token_1 = strtok(poly1, "+-") ;
    while(token_1 != NULL) {
        int coef_1, expon_1 ;
        coef_1 = get_coef(token_1) ;
        
        if(strstr(token_1, "x") == NULL) {
            expon_1 = 0 ;
        }
        else {
            sscanf(token_1, "%dx^%d", &coef_1, &expon_1) ;
        }
        if(token_1[0] == '-') {
            coef_1 = -coef_1 ;
        }

        insert_last(list1, coef_1, expon_1) ;

        token_1 = strtok(NULL, "+") ;
    }

    printf("다항식 B를 입력하세요 : ") ;
    scanf("%s", poly2) ;

    char *token_2 = strtok(poly2, "+-") ;
    while(token_2 != NULL) {
        int coef_2, expon_2 ;
        coef_2 = get_coef(token_2) ;

        if(strstr(token_2, "x") == NULL) {
            expon_2 = 0 ;
        }
        else {
            sscanf(token_2, "%dx^%d", &coef_2, &expon_2) ;
        }
        if(token_2[0] == '-') {
            coef_2 = -coef_2 ;
        }

        insert_last(list2, coef_2, expon_2) ;

        token_2 = strtok(NULL, "+") ;
    }

    poly_add(list1, list2, list3) ;
    print_poly(list3) ;

    free(list1), free(list2), free(list3) ;

    return 0 ;
}