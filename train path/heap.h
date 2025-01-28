#ifndef HEAP_H_
#define HEAP_H_

#include <stdbool.h>
#include <stdlib.h>
#include "trains.h"

#define ITEM Station*

typedef struct heap heap;
struct heap;
typedef struct node;


void upHeap(heap *h);
void downHeap(heap *h);
heap* createHeap(int size);
void freeHeap(heap *h);
void heapPush(heap *h, ITEM item, long priority);
ITEM heapPop(heap *h);
void printHeap(heap *h);
bool heap_is_empty(heap *h);



#endif