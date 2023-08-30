#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef struct {
    char string[MAX_STACK_SIZE];
    int top;
} StackType;

void init_stack(StackType *s) {
    s->top = -1;
}

bool is_empty(StackType *s) {
    return (s->top == -1);
}

bool is_full(StackType *s) {
    return (s->top == MAX_STACK_SIZE - 1);
}

void push(StackType *s, char item) {
    if (is_full(s)) {
        fprintf(stderr, "Stack Full");
        return;
    } else {
        s->string[++(s->top)] = item;
    }
}

char pop(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "Stack Empty");
        return -1;
    } else {
        char out;
        out = s->string[(s->top)--];
        return out;
    }
}

bool check_matching(const char *input_string) {
    StackType s;
    init_stack(&s);
    int i = 0;
    
    while (input_string[i] != '\0') {
        if (isalpha(input_string[i])) {
            char c = tolower(input_string[i]);
            push(&s, c);
        }
        i++;
    }

    StackType r;
    init_stack(&r);
    int j = strlen(input_string) - 1;

    while (j >= 0) {
        if (isalpha(input_string[j])) {
            char c = tolower(input_string[j]);
            push(&r, c);
        }
        j--;
    }

    while (!is_empty(&s) && !is_empty(&r)) {
        char c1 = pop(&s);
        char c2 = pop(&r);

        if (c1 != c2) {
            return false;
        }
    }

    return is_empty(&s) && is_empty(&r);
}

int main() {
    char input_string[MAX_STACK_SIZE] = {0};

    printf("문자열을 입력하세요 : ");
    fgets(input_string, sizeof(input_string), stdin);
    if (check_matching(input_string)) {
        printf("회문입니다.\n");
    } else {
        printf("회문이 아닙니다.\n");
    }

    return 0;
}
