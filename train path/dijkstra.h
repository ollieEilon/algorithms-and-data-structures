#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "trains.h"

typedef struct dijkstraReturn {
  Station **cameFrom;
  long *cost;
} DijkstraReturn;

DijkstraReturn dijkstra(Graph *g, Station *st1, Station *st2);

#endif  // DIJKSTRA_H