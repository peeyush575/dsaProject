#include<stdio.h>
#include<stdlib.h>
#include"graph.h"

void initVector(edgeVector* edgelist){
    edgelist->edges = (Edge*) malloc(10 * sizeof(Edge));
    edgelist->size = 0;
    edgelist->capacity = 10;
}

void push_back(edgeVector* edgelist, Edge edge){
    if(edgelist->size >= edgelist->capacity){
        edgelist->capacity += 10;
        edgelist->edges = (Edge*) realloc(edgelist->edges, edgelist->capacity * sizeof(Edge));
    }
    edgelist->edges[edgelist->size++] = edge;
}

Edge at(edgeVector* edgelist, int index){
    if(!(index >= 0 && index < edgelist->size)){
        printf("Index out of bounds!\n");
        exit(1);
    }
    return edgelist->edges[index];
}

void freeVector(edgeVector* edgelist){
    free(edgelist->edges);
}

Graph* init(int numVertices, int numEdges){
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->numEdges = numEdges;
    initVector(&graph->edgelist);
    return graph;
}

int findVertex(Graph* graph, int v){
    for(int i = 0; i < graph->numEdges; i++) if(at(graph->edgelist, i).v1 == v || at(graph->edgelist, i).v2 == v) return 1;
    return 0;
}

int findEdge(Graph* graph, int v1, int v2){
    for(int i = 0; i < graph->numEdges; i++){
        if(
            (at(graph->edgelist, i).v1 == v1 && at(graph->edgelist, i).v2 == v2) ||
            (at(graph->edgelist, i).v1 == v2 && at(graph->edgelist, i).v2 == v1)
        ) return 1;
    }
    return 0;
}

void addEdge(Graph* graph, int v1, int v2, int weight){
    if(findEdge(graph, v1, v2)) return;

    Edge edge;
    edge.v1 = v1, edge.v2 = v2, edge.weight = weight;

    push_back(graph->edgelist, edge);

    int newVertices = 2;
    if(findVertex(graph, v1)) newVertices--;
    if(findVertex(graph, v2)) newVertices--;

    graph->numEdges = graph->edgelist->size;
    graph->numVertices += newVertices;
}

void removeEdge(Graph* graph, int v1, int v2){
    int index;
    for(int i = 0; i < graph->numEdges; i++){
        if(
            (at(graph->edgelist, i).v1 == v1 && at(graph->edgelist, i).v2 == v2) ||
            (at(graph->edgelist, i).v1 == v2 && at(graph->edgelist, i).v2 == v1)
        ){
            index = i;
            break;
        }
    }
    for(int i = index; i < graph->numEdges - 1; i++) graph->edgelist->edges[i] = graph->edgelist->edges[i+1];
    graph->edgelist->size--;
    graph->numEdges--;
    int remV = 2;
    if(findVertex(graph, v1)) remV--;
    if(findVertex(graph, v2)) remV--;
    graph->numVertices -= remV;
}

void removeVertex(Graph* graph, int v){
    for(int i = 0; i < graph->numEdges; i++){
        if(at(graph->edgelist, i).v1 == v || at(graph->edgelist, i).v2 == v)
            removeEdge(graph, at(graph->edgelist, i).v1, at(graph->edgelist, i).v2);
    }
}

void printGraph(Graph* graph){
    printf("Edges in the Directed Graph:\n");
    for(int i = 0; i < graph->numEdges; i++) printf("%d --- %d --- %d\n", at(graph->edgelist, i).v1, at(graph->edgelist, i).weight, at(graph->edgelist, i).v2);
}

void freeGraph(Graph* graph){
    freeVector(graph->edgelist);
    free(graph);
}