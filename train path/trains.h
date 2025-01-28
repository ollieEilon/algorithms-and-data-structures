#ifndef TRAINS_H
#define TRAINS_H
typedef struct connection Connection;

typedef struct station {
  int index; 
  Connection *connections;
  int connectionNum;
  int maxConnectionNum;
  
  //helper for dijkstra
  int _indexInArray;
} Station;

struct connection {
  Station *destination;
  int cost;
};

typedef struct graph {
  int lastStationCount;
  int stNumber; //number of stations
  Station **stations; //lists of stations
  char **stationNames;
} Graph;



Graph* newGraph(int stationNum); 
void freeGraph(Graph *g);
void newStation(Graph *g, int index, char *name);
Station *getStationByIndex(Graph *g, int index);
void addConnection(Graph *g, int st1, int st2, int cost);
void removeConnection(Graph *g, int st1, int st2);
Station *getStationByName(Graph *g, char *name);
#endif  // TRAINS_H