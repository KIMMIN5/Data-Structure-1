#include <stdio.h>
#include <stdlib.h>

typedef int element ;
typedef struct ListNode {
    element data ;
    struct ListNode *link ;
} ListNode ;

void error(char *message) {
    fprintf(stderr, "\n%s\n", message) ;
}

ListNode *insert_first(ListNode *head, element value) {
    ListNode *p = (ListNode*)malloc(sizeof(ListNode)) ;
    p -> data = value ;

    if(head == NULL) {
        head = p ;
        p -> link = head ;
    }
    else {
        p -> link = head -> link ;
        head -> link = p ;
    }
    return head ;
}

ListNode *insert_last(ListNode *head, element value) {
    ListNode *p = (ListNode*)malloc(sizeof(ListNode)) ;
    p -> data = value ;

    if(head == NULL) {
        head = p ;
        p -> link = head ;
    }
    else {
        p -> link = head -> link ;
        head -> link = p ;
        head = p ;
    }
    return head ;
}

ListNode *delete_first(ListNode *head) {
    if(head == NULL) {
        error("List is Empty") ;
        return NULL ;
    }
    
    if(head -> link == head) {
        free(head) ;
        return NULL ;
    }
    else {
        ListNode *removed ;
        removed = head -> link ;
        head -> link = removed -> link ;
        free(removed) ;
    }
    return head ;
}

ListNode *delete_last(ListNode *head) {
    if(head -> link == NULL) {
        return NULL ;
    }
    if(head -> link == head) {
        free(head) ;
        return NULL ;
    }
    else {
    ListNode *removed = head ;
    ListNode *prev = head ;
    while(prev -> link != head) {
        prev = prev -> link ;
    }
    prev -> link = removed -> link ;
    head = prev ;
    free(removed) ;
    }
    return head ;
}

void print_list(ListNode *head) {
    ListNode *p ;

    if(p == NULL) {
        error("List is Empty") ;
    }
    p = head -> link ;
    do {
        printf("%d -> ", p -> data) ;
        p = p -> link ;
    } while(p != head -> link) ;
    printf("\n") ;
}

int main() {
    int menu, value ;
    ListNode *head = NULL ;

    while(1) {
        printf("\nCircular Linked-List\n") ;
        printf("1. Insert First\n") ;
        printf("2. Insert Last\n") ;
        printf("3. Delete First\n") ;
        printf("4. Delete Last\n") ;
        printf("5. Print List\n") ;
        printf("0. Exit\n") ;
        printf("Enter the menu : ") ;
        scanf("%d", &menu) ;

        if(menu == 1) {
            printf("Enter a value : ") ;
            scanf("%d", &value) ;
            head = insert_first(head, value) ;
        }
        else if(menu == 2) {
            printf("Enter a value : ") ;
            scanf("%d", &value) ;
            head = insert_last(head, value) ;            
        }
        else if(menu == 3) {
            head = delete_first(head) ;
            printf("head : %d\n", head -> data) ;
        }
        else if(menu == 4) {
            head = delete_last(head) ;
            printf("head : %d\n", head -> data) ;
        }
        else if(menu == 5) {
            print_list(head) ;
        }
        else {
            exit(0) ;
        }
    }

    return 0 ;
}