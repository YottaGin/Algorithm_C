#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_KEY 21
#define SIZE_TABLE 100000

typedef struct node
{
    char key[SIZE_KEY];
    int val;
    struct node* pNextNode; // if a collison happens, use a linked list.
} node_t;

void printfHashTable(node_t** pHashTable)
{
    node_t* pNode = NULL;
    int i;
    
    for(i = 0; i < SIZE_TABLE; i++){
        if(pHashTable[i] != NULL){
            pNode = pHashTable[i];
            while(pNode != NULL){
                printf("hashVal:%d key:%s value:%d\n", i, pNode->key, pNode->val);
                pNode = pNode->pNextNode;
            }
        }
    }
    printf("\n");
    
    return;
}

int hashFunc(char* key)
{
    int sum = 0;
    int i = 0;
    
    while(key[i] != '\0'){
        sum += key[i];
        i++;
    }
    
    return sum % SIZE_TABLE;
}

void initHashTable(node_t** pHashTable)
{
    for(int i = 0; i < SIZE_TABLE; i++){
        pHashTable[i] = NULL;
    }

    return;
}

node_t* initNode(char* key, int val)
{
    node_t* pNode = NULL;
    
    pNode = (node_t*)malloc(sizeof(node_t));
    if (pNode == NULL) {
        printf("init malloc error\n");
        return NULL;
    }
    
    strcpy(pNode->key, key);
    pNode->val = val;
    pNode->pNextNode = NULL;
    
    return pNode;
}

void registerKeyVal(node_t** pHashTable, char* key, int val)
{
    node_t* pNode = NULL;
    node_t* pPreNode = NULL;
    
    if(strlen(key) > SIZE_KEY - 1){
        printf("arg error\n");
        return;
    }
    
    // if there is not a linked list
    if (pHashTable[hashFunc(key)] == NULL) {
        pHashTable[hashFunc(key)] = initNode(key, val);
        if(pHashTable[hashFunc(key)] == NULL) {
            return;
        }
        return;
    }

    // if there is a linked list
    pNode = pHashTable[hashFunc(key)];
    pPreNode = pNode;
    while(pNode != NULL){
        if(strcmp(key, pNode->key) == 0){
            pNode->val = val;
            return;
        }
        pPreNode = pNode;
        pNode = pNode->pNextNode;
    }
    
    pPreNode->pNextNode = initNode(key, val);
    
    return;
}

void deleteKey(node_t** pHashTable, char* key)
{
    node_t* pNode = NULL;
    node_t* pPreNode = NULL;
    
    if(pHashTable[hashFunc(key)] == NULL){
        printf("No key\n");
        printfHashTable(pHashTable);
        return;
    }
    pNode =  pHashTable[hashFunc(key)];
    while(pNode != NULL){
        if(strcmp(key, pNode->key) == 0){
            if(pNode == pHashTable[hashFunc(key)]){
                pHashTable[hashFunc(key)] = pNode->pNextNode;
            }else{
                pPreNode->pNextNode = pNode->pNextNode;
            }
            free(pNode);
            return;
        }
        pPreNode = pNode;
        pNode = pNode->pNextNode;
    }
    
    return;
}

void printKeyVal(node_t** pHashTable, char* key)
{
    node_t* pNode = NULL;
    node_t* pPreNode = NULL;
    
    if(pHashTable[hashFunc(key)] == NULL){
        printf("No key\n");
        printfHashTable(pHashTable);
        return;
    }
    pNode =  pHashTable[hashFunc(key)];
    while(pNode != NULL){
        if(strcmp(key, pNode->key) == 0){
            printf("key:%s value:%d\n", pNode->key, pNode->val);
            return;
        }
        pPreNode = pNode;
        pNode = pNode->pNextNode;
    }
    
    return;
}

int getKeyVal(node_t** pHashTable, char* key){
    node_t* pNode = NULL;
    node_t* pPreNode = NULL;
    
    if(pHashTable[hashFunc(key)] == NULL){
        printf("No key\n");
        printfHashTable(pHashTable);
        return -1;
    }
    pNode =  pHashTable[hashFunc(key)];
    while(pNode != NULL){
        if(strcmp(key, pNode->key) == 0){
            return pNode->val;
        }
        pPreNode = pNode;
        pNode = pNode->pNextNode;
    }
    
    return -1;
}

void deleteNode(node_t** pHashTable){
    node_t* pNode = NULL;
    node_t* pPreNode = NULL;
    int i;
    
    for(i = 0; i < SIZE_TABLE; i++){
        if(pHashTable[i] != NULL){
            pNode = pHashTable[i];
            while(pNode != NULL){
                pPreNode = pNode;
                pNode = pNode->pNextNode;
                free(pPreNode);
            }
            pHashTable[i] = NULL;
        }
    }
    printf("Delete all the node\n");
    printfHashTable(pHashTable);
    
    return;
}

int main(){
    node_t* pHashTable[SIZE_TABLE];
    
    initHashTable(pHashTable);
    
    registerKeyVal(pHashTable, "cddd", 3);
    registerKeyVal(pHashTable, "ddsf", 4);
    registerKeyVal(pHashTable, "essas", 5);
    registerKeyVal(pHashTable, "fsfds", 6);
    registerKeyVal(pHashTable, "dsfdf", 1);
    printfHashTable(pHashTable);
    printKeyVal(pHashTable, "cddd");

    deleteKey(pHashTable, "cddd");
    deleteKey(pHashTable, "ddsf");
    deleteKey(pHashTable, "fsfds");
    printfHashTable(pHashTable);
    
    deleteNode(pHashTable);
    printfHashTable(pHashTable);

    return 0;
}
