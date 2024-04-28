#include<stdio.h>
#include<stdlib.h>
#include"graph.h"

typedef struct subset{
    int parent;
    int rank;
}subset;

int find(subset subsets[], int i);
void Union(subset* subsets, int x, int y);
int comparator(const void* a, const void* b);
void sortEdges(edgeVector* edges);
void kruskal(Graph* graph, edgeVector* mst);

int main(){
    Graph* graph = init(0, 0);
    printf("Minimum Spanning Tree for a Dynamic Graph\n");
    printf("Select the operation you wish to conduct:\n");
    printf("1. Add Edge\n");
    printf("2. Remove Edge\n");
    printf("3. Remove Vertex\n");
    printf("4. Exit\n");
    int choice;
    scanf("%d", &choice);
    while(choice != 4){
        edgeVector* mst;
        int v1, v2, weight;
        switch(choice){
            case 1:
                printf("Enter Source Vertex: ");
                scanf("%d", &v1);
                printf("Enter Destination Vertex: ");
                scanf("%d", &v2);
                printf("Enter Weight of the Edge: ");
                scanf("%d", &weight);
                addEdge(graph, v1, v2, weight);
                printGraph(graph);
                initVector(&mst);
                kruskal(graph, mst);
                printf("Minimum Spanning Tree Edges:\n");
                for(int i = 0; i < mst->size; i++) printf("%d --- %d --- %d\n", at(mst, i).v1, at(mst, i).weight, at(mst, i).v2);
                break;

            case 2:
                printf("Enter Source Vertex: ");
                scanf("%d", &v1);
                printf("Enter Destination Vertex: ");
                scanf("%d", &v2);
                removeEdge(graph, v1, v2);
                printGraph(graph);
                initVector(&mst);
                kruskal(graph, mst);
                printf("Minimum Spanning Tree Edges:\n");
                for(int i = 0; i < mst->size; i++) printf("%d --- %d --- %d\n", at(mst, i).v1, at(mst, i).weight, at(mst, i).v2);
                break;

            case 3:
                int v;
                printf("Enter Vertex: ");
                scanf("%d", &v);
                removeVertex(graph, v);
                printGraph(graph);
                initVector(&mst);
                kruskal(graph, mst);
                printf("Minimum Spanning Tree Edges:\n");
                for(int i = 0; i < mst->size; i++) printf("%d --- %d --- %d\n", at(mst, i).v1, at(mst, i).weight, at(mst, i).v2);
                break;

            default:
                break;
        }
        printf("Select the operation you wish to conduct:\n");
        printf("1. Add Edge\n");
        printf("2. Remove Edge\n");
        printf("3. Remove Vertex\n");
        printf("4. Exit\n");
        scanf("%d", &choice);
    }
    return 0;
}

int find(subset subsets[], int i){
    if(subsets[i].parent != i) subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(subset* subsets, int x, int y){
    int xRoot = find(subsets, x), yRoot = find(subsets, y);
    if(subsets[xRoot].rank < subsets[yRoot].rank) subsets[xRoot].parent = yRoot;
    else if(subsets[xRoot].rank > subsets[yRoot].rank) subsets[yRoot].parent = xRoot;
    else{
        subsets[yRoot].parent = xRoot;
        subsets[xRoot].rank++;
    }
}

int comparator(const void* a, const void* b){
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

void sortEdges(edgeVector* edges){
    qsort(edges->edges, edges->size, sizeof(Edge), comparator);
}

void kruskal(Graph* graph, edgeVector* mst){
    subset subsets[graph->numVertices];
    for(int v = 0; v < graph->numVertices; v++){
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    sortEdges(graph->edgelist);

    for(size_t i = 0; i < graph->edgelist->size; i++){
        Edge nextEdge = graph->edgelist->edges[i];
        int x = find(subsets, nextEdge.v1), y = find(subsets, nextEdge.v2);

        if(x != y){
            push_back(mst, nextEdge);
            Union(subsets, x, y);
        }
    }
}