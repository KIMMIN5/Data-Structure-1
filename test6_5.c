#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACKS_SIZE 100

int err = 0 ;

typedef char element ;

typedef struct {
    element data[MAX_STACKS_SIZE] ;
    int top ;
}StackType ;

void init_stack(StackType *s) {
    s->top = -1 ;
}

int is_empty(StackType *s) {
    return(s->top == -1) ;
}

int is_full(StackType *s) {
    return(s->top == MAX_STACKS_SIZE -1) ;
}

void push(StackType *s, element item) {
    if(is_full(s)) {
        fprintf(stderr, "Stack Full\n") ;
        exit(1) ;
    }
    else {
        s->data[++(s->top)] = item ;
    }
}

element pop(StackType *s) {
    if(is_empty(s)) {
        fprintf(stderr, "Stack Empty\n") ;
        return -1 ;
    }
    else {
        return(s->data[(s->top)--]) ;
    }
}

element peek(StackType *s) {
    if(is_empty(s)) {
        fprintf(stderr, "Stack Empty\n") ;
        return -1 ;
    }
    else {
        return(s->data[(s->top)]) ;
    }
}

int prec(char op) {
    switch(op) {
        case '(': case ')': return 0 ;
        case '+': case '-': return 1 ;
        case '*': case '/': return 2 ;
    }
    return -1 ;
}

void check_error(element exp[]) {
    err = -1 ;
    int len = strlen(exp) ;

    /*0���� ������ ���� �� ����*/
    for(int i=0; i<len; i++) {
        if(i+1 < len && exp[i] == '/' && exp[i+1] == '0') {
            printf("Error\n") ;
            printf("infix_to_postfix error0 : divide by 0\n\n") ;
            err = 0 ;
            break ;
        }
    }

    /*��ȣ ¦ �� ���� �� ����*/
    int count = 0 ;
    for(int i=0; i<len; i++) {
        if(exp[i] == '(') {
            count++ ;
        }
        else if(exp[i] == ')') {
            count-- ;
        }
    }

    if(count > 0) {
        printf("Error\n") ;
        printf("infix_to_postfix error1: Cannot match '(' ')'\n\n") ;
        err = 1 ;
    }

    else if(count < 0) {
        printf("Error\n") ;
        printf("infix_to_postfix error1: Cannot match '(' ')'\n\n") ;
        err = 1 ;
    }

    /*���ܹ��� ���� ���� �� ����*/
    for(int i=0; i<len; i++) {
        if(exp[i] == '(' || exp[i] == ')') {
            continue ;
        }
        else if(exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
            continue ; 
        }
        else if('0' <= exp[i] && exp[i] <= '9') {
            continue ;
        }
        else {
            printf("Error\n") ;
            printf("infix_to_postfix error2 : Invaild character \n\n") ;
            err = 2 ;
        }
    }

    /*�����ڰ� ���� ���� �� ����*/
    if(exp[0] == '+' || exp[0] == '-' || exp[0] == '*' || exp[0] == '/') {
        printf("Error\n") ;
        printf("infix_to_postfix error2 : Invaild expression\n\n") ;
        err = 2 ;
    }
}

int eval(char exp[]) {
    int op1, op2, value = 0, i = 0 ;
    int len = strlen(exp) ;
    char ch ;
    StackType s ;
    init_stack(&s) ;

    for(i=0; i<len; i++) {
        ch = exp[i] ;
        if(ch != '+' && ch != '-' && ch != '*' && ch != '/') {
            value = 0 ;
            while(ch >= '0' && ch <= '9') {
                value = value * 10 + (ch - '0') ;
                i++ ;
                ch = exp[i] ;
            }
            push(&s, value) ;
            i-- ;
        }
        else {
            op2 = pop(&s) ;
            op1 = pop(&s) ;
            switch(ch) {
                case '+': push(&s, op1 + op2); break ;
                case '-': push(&s, op1 - op2); break ;
                case '*': push(&s, op1 * op2); break ;
                case '/': push(&s, op1 / op2); break ;
            }
        }
    }
    return pop(&s) ;
}

element* infix_to_outfix(element exp[]) {
    check_error(exp) ;

    if(err != -1) {
        return NULL ;
    }

    int i, idx = 0 ;
    int len = strlen(exp) ;
    char ch, op ;
    StackType s ;
    element* postfix_arr = (element*)malloc(MAX_STACKS_SIZE * sizeof(element)) ;
    if(postfix_arr == NULL) {
        fprintf(stderr, "Memory allocation error\n") ;
        exit(1) ;
    }

    init_stack(&s) ;

    for(i=0; i<len; i++) {
        ch = exp[i] ;                       

        if('0' <= ch && ch <= '9') {
            char num_str[100] = "" ;
            int num_idx = 0 ;
            while(i<len && '0' <= exp[i] && exp[i] <= '9') {
                num_str[num_idx++] = exp[i++] ;
            }
            num_str[num_idx] = '\0' ;
            int num = atoi(num_str) ;
            postfix_arr[idx++] = num ;
            i-- ;
        }
        else if(ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while(!is_empty(&s) && (prec(ch) < prec(peek(&s)))) {
                postfix_arr[idx++] = peek(&s) ;
                pop(&s) ;
            }
            push(&s, ch) ;
        }
        else if(ch == '(') {
            push(&s, ch) ;
        }
        else if(ch == ')') {
            op = pop(&s) ;
            while( op != '(') {
                postfix_arr[idx++] = op ;
                op = pop(&s) ;
            }
        }
    }

    while(!is_empty(&s)) {
        op = peek(&s) ;
        pop(&s) ;
        postfix_arr[idx++] = op ;
    }

    postfix_arr[idx] = '\0' ;
    return postfix_arr ;
}

int main() {
    element expression[MAX_STACKS_SIZE] ;
    char word[100] ;

    printf("Enter an infix expression : ") ;
    scanf("%s", expression) ;

    element *result = infix_to_outfix(expression) ;
    printf("Post expression : %s\n", result) ;
    printf("Result : %d\n", eval(result)) ;

    return 0 ;
}