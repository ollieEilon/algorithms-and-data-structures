// #include <type.h>
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <string.h>
#include "trains.h"
#define DEFAULT_MAX_CONNECTION 10


/*the function below gets the number of stations in a graph and allocates memory for a new graph*/
Graph *newGraph(int stationNum) {
    Graph *g = malloc((sizeof(struct graph)));
    g->lastStationCount = 0;
    g->stNumber = stationNum;
    g->stations = malloc(stationNum * (sizeof(struct station *)));
    g->stationNames = malloc(stationNum * (sizeof(char *)));
    return g;
}


/*this function frees a graph*/
void freeGraph(Graph *g) {
    for (int i = 0; i < g->stNumber; i++) {
        free(g->stationNames[i]);
        free(g->stations[i]->connections);
        free(g->stations[i]); // TODO: fix me later when i have valgrind issues
    }

    free(g->stationNames);
    free(g->stations);
    free(g);
}

/*the function below is an implementation of strdup which duplicates a string */
char *strmedup(char *s) {
    int len = strlen(s);
    char *res = malloc(sizeof(char) * (len + 1));
    memcpy(res, s, sizeof(char) * (len));
    res[len] = 0;
    return res;
}

/*the function below adds a new station to the graph*/
void newStation(Graph *g, int index, char *name) {
    const int i = g->lastStationCount++;
    g->stations[i] = malloc(sizeof(struct station));
    g->stations[i]->connectionNum = 0;
    g->stations[i]->connections = malloc(DEFAULT_MAX_CONNECTION * sizeof(struct connection));
    g->stations[i]->index = index;
    g->stations[i]->maxConnectionNum = DEFAULT_MAX_CONNECTION;
    g->stations[i]->_indexInArray = i;
    g->stationNames[i] = strmedup(name);
}

/*this function gets the station struct using the index of the station*/
Station *getStationByIndex(Graph *g, int index) {
    for (int i = 0; i < g->stNumber; i++) {
        if (g->stations[i]->index == index) {
            return g->stations[i];
        }
    }
    return NULL;
}

/*the function belpw is a helper function to adding a connection and adds it into the 
connections array of the node*/
void _addConnection(Station *s, Station *dest, int cost) {
    int i = s->connectionNum++;
    s->connections[i].cost = cost;
    s->connections[i].destination = dest;
    if (s->maxConnectionNum == i + 1) {
        s->maxConnectionNum *= 2;
        s->connections = realloc (s->connections, s->maxConnectionNum * sizeof(struct connection));
    }
}

/*this function adds a connection. It findss the stations as Station from index using tyhe 
getStationIndex function and then runns the helper functions both ways */
void addConnection(Graph *g, int st1, int st2, int cost) {
    Station *s1 = getStationByIndex(g,st1);
    Station *s2 = getStationByIndex(g, st2);
    _addConnection(s1, s2, cost);
    _addConnection(s2, s1, cost);
}

/*the function below is a helper function to removeConnection, gets two stations and removes 
their connevtion from the connection array*/
void _removeConnection(Station *st1, Station *st2) {
    int i = -1;
    while (++i < st1->connectionNum && st1->connections[i].destination != st2);
    // i = index of other station in connect
    for (int j = i + 1; j < st1->connectionNum; j++) {
        st1->connections[j - 1] = st1->connections[j];
    }

    if (i < st1->connectionNum) st1->connectionNum--;
}

/*this function removes a connection from the graph 
it begins by getting the stations as a Station and then uses its helper function to 
remove the connections both ways*/
void removeConnection(Graph *g, int st1, int st2) {
    Station *s1 = getStationByIndex(g, st1);
    Station *s2 = getStationByIndex(g, st2);
    _removeConnection(s1, s2);
    _removeConnection(s2, s1);
}

/*the function below gets a station as a Station by name*/
Station *getStationByName(Graph *g, char *name) {
    for (int i = 0; i < g->stNumber; i++) {
        if (!strcmp(name, g->stationNames[i])) {
            return g->stations[i];
        }
    }
    return NULL;
}