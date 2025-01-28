#include "dijkstra.h"
#include "heap.h"

#define INFINITY 100000000

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define debug(...) debug(__VA_ARGS__)
#define debug(...)


/*function below gets in the graph network, first station and destination station and returns
the dijkstra path between them as well as its cost
*/
DijkstraReturn dijkstra(Graph *g, Station *st1, Station *st2) {
  Station **cameFrom = malloc(g->stNumber * sizeof(struct station *));
  long *distances = malloc(g->stNumber * sizeof(long));

  int *visited = malloc(sizeof(int) * g->stNumber);
  memset(visited, 0, sizeof(int) * g->stNumber);

  for (int i = 0; i < g->stNumber; i++) {
    cameFrom[i] = NULL;
    distances[i] = INFINITY;
  }

  heap *h = createHeap(g->stNumber);
  heapPush(h, st1, 0);
  distances[st1->_indexInArray] = 0;
  
  while (!heap_is_empty(h)) {
    Station *current = heapPop(h);
    

    if (visited[current->_indexInArray]) {
      continue;
    }
    visited[current->_indexInArray]++;

    int currI = current->_indexInArray;
    for (int i = 0; i < current->connectionNum; i++) {
      int toI = current->connections[i].destination->_indexInArray;

      int newRouteCost = distances[currI] + current->connections[i].cost;
      
      if (newRouteCost < distances[toI]) {
        distances[toI] = newRouteCost;
        cameFrom[toI] = current;
       heapPush(h, current->connections[i].destination, newRouteCost);
      }
      debug("\n");
    }

    if (current == st2) {
      break;
    }
  }

  freeHeap(h);
  free(visited);
  return (DijkstraReturn) {
    .cameFrom = cameFrom,
    .cost = distances,
  };
}