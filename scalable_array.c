#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int size;
    int length;
    int *data;
} array_list;

void array_list_init(array_list *list) {
    int init_length = 4;
    list->data = (int*)malloc(sizeof(int) * init_length);
    if (list->data == NULL) exit(1);
    
    list->size = 0;
    list->length = init_length;
}

void array_list_add(array_list *list, int num) {
    if (list->size >= list->length) {
        int *new_data = (int*)realloc(list->data, list->length * 2 * sizeof(int));
        if (new_data == NULL) exit(1);
        // change pointer
        list->data = new_data;
        list->length *= 2;
    }

    list->data[list->size] = num;
    list->size += 1;
}

void array_list_free(array_list *list) {
    free(list->data);
    list->size = 0;
    list->length = 0;
}

int main(void){
    array_list list;
    array_list_init(&list);
    
    char buf[1024];
    char str[1024];
    int q;
    fgets(buf, sizeof(buf), stdin);
    sscanf(buf, "%d\n", &q);
    
    char *p;
    for (int i=0; i<q; i++) {
        fgets(buf, sizeof(buf), stdin);
        sscanf(buf, "%[^\n]", str);
        
        p = strtok(str, " ");
        if (strcmp(p, "2") == 0) continue;
        
        p = strtok(NULL, " ");
        array_list_add(&list, atoi(p));
    }
    
    printf("%d\n", list.size);
    for (int i=0; i<list.size; i++) {
        printf("%d\n", list.data[i]);
    }
    
    array_list_free(&list);
    
    return 0;
}
