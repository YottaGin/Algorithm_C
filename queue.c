#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM 255

typedef struct queue {
    int tail;
    int head;
    int data[MAX_NUM];
} queue;


void init(queue *queue){
    queue->head = 0;
    queue->tail = -1;
}

void enqueue(queue *queue, int n){

    // when queue is not empty
    if((queue->tail + 2) % MAX_NUM == queue->head) exit(1);

    queue->data[(queue->tail + 1) % MAX_NUM] = n;
    queue->tail = (queue->tail + 1) % MAX_NUM;
}

int dequeue(queue *queue){
    int ret = 0;

    // when queue is empty
    if((queue->tail + 1) % MAX_NUM == queue->head) exit(1);

    ret = queue->data[queue->head];
    queue->head = (queue->head + 1) % MAX_NUM;
    return ret;
}

void show(queue *queue){
    int num;

    if (queue->tail < queue->head) {
        num = queue->tail + MAX_NUM - queue->head + 1;
    } else {
        num = queue->tail - queue->head + 1;
    }

    for(int i=0; i<=num-1; i++){
        printf("%d", queue->data[(queue->head + i) % MAX_NUM]);
        if (i == num -1) {
            printf("\n");
        } else {
            printf(" ");
        } 
    }
}

int main(void) {
    queue que;
    init(&que);
    
    char buf[1024];
    char str[1024];
    char *p;
    int q;
    fgets(buf, sizeof(buf), stdin);
    sscanf(buf, "%d\n", &q);
    
    for (int i=0; i<q; i++) {
        fgets(buf, sizeof(buf), stdin);
        sscanf(buf, "%[^\n]", str);
        p = strtok(str, " ");
        if (strcmp(p, "1") == 0) { // enqueue
            p = strtok(NULL, " ");
            enqueue(&que, atoi(p));
        } else { // dequeue
            int ret;
            ret = dequeue(&que);
        }
        show(&que);
    }
    
    return 0;
}
