#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 255

typedef struct stack {
    int top;
    int data[max];
} stack;

void init(stack *stack){
    stack->top = -1;
    for(int i=0; i<max; i++)
        stack->data[i] = 0;
}

void push(stack *stack, int n){
    if (stack->top >= max-1) {
        exit(1);
    }else{
        stack->top++;
        stack->data[stack->top] = n;
    }
}

void pop(stack *stack){
    if(stack->top <= -1)
        exit(1);
    else{
        stack->data[stack->top] = 0;
        stack->top--;
    }
    
}

void show(stack *stack){
    if (stack->top == -1) {
        printf("\n");
        return;
    }

    for(int i=0; i <= stack->top; i++) {
        printf("%d", stack->data[i]);
        
        if (i == stack->top) {
            printf("\n");
        } else {
            printf(" ");
        }
        
    }
}


int main(void){
    stack st;
    init(&st);
    
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
        if (strcmp(p, "1") == 0) { // push
            p = strtok(NULL, " ");
            push(&st, atoi(p));
        } else {  // pop
            pop(&st);
        }
        show(&st);
    }
    
    return 0;
}