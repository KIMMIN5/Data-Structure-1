#define MAX_QUEUE_SIZE 5
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

void init_queue(QueueType *qptr) {
    qptr->front = qptr->rear = 0;
}

int is_empty(QueueType *qptr) {
    return(qptr->rear == qptr->front);
}

int is_full(QueueType *qptr) {
    return((qptr->rear + 1) % MAX_QUEUE_SIZE == qptr->front);
}

void enqueue(QueueType *qptr, element item) {
    if(is_full(qptr)) {
        fprintf(stderr, "Queue is Full\n");
    }
    else {
        qptr->rear = (qptr->rear + 1) % MAX_QUEUE_SIZE;
        qptr->data[qptr->rear] = item;
    }
}

element dequeue(QueueType *qptr) {
    if(is_empty(qptr)) {
        fprintf(stderr, "Queue is Empty\n");
        return -1;
    }
    else {
        qptr->front = (qptr->front + 1) % MAX_QUEUE_SIZE;
        return qptr->data[qptr->front];
    }
}

void queue_print(QueueType *qptr) {
    printf("Queue(front = %d, rear = %d) = ", qptr->front, qptr->rear);
    if(!is_empty(qptr)) {
        int i = qptr->front;
        do {
            i = (i + 1) % MAX_QUEUE_SIZE;
            printf("%d | ", qptr->data[i]);
        } while (i != qptr->rear);
    }
    printf("\n");
}

int main() {
    int select_num;
    QueueType q;
    init_queue(&q);

    while(select_num != 4) {
        printf("\n===== Menu =====\n");
        printf("1. Input data and Enqueue\n");
        printf("2. Dequeue data and Print data\n");
        printf("3. Print Queue\n");
        printf("4. Exit\n");

        printf("\nSelect the number : ");
        scanf("%d", &select_num);

        printf("\n");

        if(select_num == 1) {
            if (!is_full(&q)) {
                element inputdata;
                printf("Input the data : ");
                scanf("%d", &inputdata);

                printf("Enqueue : %d\n", inputdata);
                enqueue(&q, inputdata);
            }
            else {
                printf("isfull\n");
            }
        }
        else if(select_num == 2) {
            printf("Dequeue : %d\n", dequeue(&q));
        }
        else if(select_num == 3) {
            queue_print(&q);
        }
        else if(select_num == 4) {
            printf("Exit the program\n");
            exit(1);
        }
    }

    return 0;
}
