#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[100] ;
} element ;

typedef struct ListNode{
    element data ;
    struct ListNode *link ;
} ListNode ;

void error(char *message) {
    fprintf(stderr, "\n%s\n", message) ;
}

ListNode *insert_first(ListNode *head, element value) {
    ListNode *p = (ListNode*)malloc(sizeof(ListNode)) ;
    p -> data = value ;
    p -> link = head ;
    return p ;
}

ListNode *insert_last(ListNode *head, element value) {
    ListNode *p = (ListNode*)malloc(sizeof(ListNode)) ;
    p->data = value ;
    p->link = NULL ;  

    if(head == NULL) {
        return p ;
    }

    ListNode *current = head ;
    while(current->link != NULL) {
        current = current->link ;
    }
    current->link = p ;

    return head ;
}

ListNode *delete(ListNode *head, element value) {
    if(head == NULL) {
        return NULL ;
    }

    if(strcmp(head->data.name, value.name) == 0) {
        ListNode *nextNode = head->link ;
        free(head) ;
        return nextNode ;
    }

    ListNode *tmp = head ;
    while(tmp->link != NULL && strcmp(tmp->link->data.name, value.name) != 0) {
        tmp = tmp->link ;
    }

    if(tmp->link != NULL) {
        ListNode *nextNode = tmp->link->link ;
        free(tmp->link) ;
        tmp->link = nextNode ;
    }

    return head ;
}

ListNode* search_list(ListNode *head, element value) {
    ListNode *tmp = head ; 
    while(tmp != NULL) {
        if(strcmp(tmp->data.name, value.name) == 0) {
            return tmp ;
        }
        tmp = tmp -> link ;
    }
    return NULL ;
}

void print_list(ListNode *head) {
    ListNode *p = head ;
    while(p != NULL) {
        printf("%s -> ", p -> data.name) ;
        p = p -> link ;
    }
    printf("NULL\n") ;
}

int main() {
    element fruits[10] = { {"Mango"}, {"Orange"}, {"Apple"}, {"Grape"}, {"Cherry"}, {"Plum"}, {"Guava"}, {"Raspberry"}, {"Banana"}, {"Peach"} };
    ListNode *head = NULL, *tmp ;

    for(int i = 9; i >= 0; --i) {
        head = insert_first(head, fruits[i]) ;
    }

    ListNode *deleted = NULL ;
    element value ;
    int menu_bar ;

    while(1) {
        printf("\nMenu\n") ;
        printf("(1) Insert new fruit\n") ;
        printf("(2) Delete the fruit\n") ;
        printf("(3) Print the deleted list\n") ;
        printf("(4) Exit\n\n") ;
        printf("Enter the Menu : ") ; 
        scanf("%d", &menu_bar) ;

        if(menu_bar == 1) {
            printf("Enter the fruit name : ") ;
            scanf("%s", value.name) ;
            if(search_list(head, value) != NULL) {
                error("Fruit already exists.") ;
            }
            else {
                head = insert_last(head, value) ;
            }
            printf("\nFruit list : \n") ;
            print_list(head) ;
        }

        else if(menu_bar == 2) {
            printf("Enter the fruit name : ") ;
            scanf("%s", value.name) ;
            if(search_list(head, value) != NULL) {
                deleted = insert_first(deleted, value) ;
                head = delete(head, value) ;
                printf("\nFruit list : \n") ;
                print_list(head) ;
            }
            else {
                error("Fruit does not exist.") ;
                printf("\nFruit list : \n") ;
                print_list(head) ;
            }
        }
        else if(menu_bar == 3) {
            printf("Deleted fruits: ") ;
            print_list(deleted) ;
            printf("\nFruit list : \n") ;
            print_list(head) ;
        }
        else if(menu_bar == 4) {
            exit(0) ;
        }
        else {
            error("Invalid menu") ;
        }
    }
}
