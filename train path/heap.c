#include "heap.h"
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 1024
#define infinity 100000000

typedef struct node {
    ITEM station;
    long priority;
} node;

typedef struct heap{
    node *array;
    int size;
}heap;

/*function below creates a new heap in memory*/
heap* createHeap(int size) {
    heap* h = malloc(sizeof(heap));
    h->array = malloc(sizeof(node) * (size + 1));
    h->size = 0;
    return h;
}

/*this function resorts the heap after a new node is added*/
void upHeap(heap *h) {
    int i = h->size;
    while (i > 1 && h->array[i].priority < h->array[i/2].priority) {
        node f = h->array[i];
        h->array[i] = h->array[i/2];
        h->array[i/2] = f;
        i = i/2;
    }
}

/*this function resorts the heap after a node is removed*/
void downHeap(heap *h) {
    int i = 1;
    while (i*2 <= h->size) {
        int j = i*2;
        if (j+1 <= h->size && h->array[j+1].priority < h->array[j].priority) {
            j++;
        }
        if (h->array[j].priority < h->array[i].priority) {
            node f = h->array[j];
            h->array[j] = h->array[i];
            h->array[i] = f;
            i = j;
        } else {
            break;
        }
    }
}

/*function takes in a heap, item to push inside and its priority and then
calls upHeap to have it sorted*/
void heapPush(heap *h, ITEM item, long priority) {
    h->size++;
    h->array[h->size].station = item;
    h->array[h->size].priority = priority;
    upHeap(h);
}


/*this function pops the root node of the heap and then rearranges the remaining nodes*/
ITEM heapPop(heap *h) {
    if (h->size == 0) {
        return NULL;
    }
    ITEM it = h->array[1].station;
    h->array[1] = h->array[h->size];
    h->size--;
    downHeap(h);
    return it;
}


/*this function is for the testing of the heap*/
void printHeap(heap *h) {
    for (int i = 1; i <= h->size; i++) {
        printf("%d ", h->array[i].station);
    }
    printf("\n");
}

ITEM heapPeek(heap *h);

/*this function returns true if the heap is empty, and false if it isnt*/
bool heap_is_empty(heap *h) {
    if (h->size == 0) {
        return true;
    } 
    return false;
}


/*this function frees the heap*/
void freeHeap(heap *h) {
    free(h->array);
    free(h);
}