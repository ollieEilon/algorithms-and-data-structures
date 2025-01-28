//#include <type.h>
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include "trains.h"
#include "dijkstra.h"


#define MAX_CITY_NAME 65000
#define SCAN_CITY "%65000[^\n]"

/*the function is used to reversely print the found dijkstra path. it is recursive and prints all stations*/
void reversePrint(Graph *g, Station *orig, Station *final, Station **route) {
    if (orig != final) {
        reversePrint (g, orig, route[final->_indexInArray], route);
    }

    printf("%s\n", g->stationNames[final->_indexInArray]);
}


/*the function below calls dijkstra and uses it for the users part.
it recieves the required inputs, finds the route, prints it as well as the cost
and frees the memory of the route*/
void runDijkstra(Graph *g) {
    char s1[MAX_CITY_NAME], s2[MAX_CITY_NAME];
    while (scanf("%65000[^\n]%*c", s1), s1[0] != '!') {
        scanf("%65000[^\n]%*c", s2);
        Station *st1 = getStationByName(g, s1);
        Station *st2 = getStationByName(g, s2);
        DijkstraReturn route = dijkstra(g, st1, st2);
        if (route.cameFrom[st2->_indexInArray] == NULL) {
            printf("UNREACHABLE\n");
        } else {
            reversePrint(g, st1, st2, route.cameFrom);
            printf("%ld\n", route.cost[st2->_indexInArray]);
        }

        free(route.cameFrom);
        free(route.cost);
    }
    
}

/*this function reads the main input and initialises the graph, stations and connnection 
addition and removal*/
Graph *readInput() {
    int numberOfStations;
    scanf("%d%*c", &numberOfStations);
    Graph *g = newGraph(numberOfStations);
    
    int index;
    char nameOfStation[MAX_CITY_NAME];
    for (int i = 0; i < numberOfStations; i++) {
        scanf("%d%*c%65000[^\n]%*c", &index, nameOfStation);
        newStation(g, index, nameOfStation);
    }

    int con, st1, st2, cost;
    scanf("%d%*c", &con);
    for (int i = 0; i < con; i++) {
        scanf("%d%*c%d%*c%d%*c", &st1, &st2, &cost);
        addConnection(g, st1, st2, cost);
    }

    int dis;
    char s1[MAX_CITY_NAME], s2[MAX_CITY_NAME];
    scanf("%d%*c", &dis);
    for (int i = 0; i < dis; i++) {
        scanf("%65000[^\n]%*c%65000[^\n]%*c", s1, s2);
        Station *sta1 = getStationByName(g, s1);
        Station *sta2 = getStationByName(g, s2);
        removeConnection(g, sta1->index, sta2->index);
    }

    return g;
}


int main(int argc, char *argv[]) {
    int repeats; 
    scanf("%d%*c", &repeats);
    while (repeats--) {
        Graph *g = readInput();
        runDijkstra(g);
        freeGraph(g);
    }
    return 0;
}