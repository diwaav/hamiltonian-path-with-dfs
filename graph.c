// CITE: Graph constructor, destructor, and struct provided by professor
#include "graph.h"

#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// The struct Graph defines the components of the graph matrix.
// vertices: the number of vertices
// undirected: is true if the graph is undirected, false otherwise
// visited: is true if the location has been visited
// matrix[][]: is a matrix that maps the graph

struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

// The graph_create() function assigns the vertices and undirected attributes to
// the graph G to create a graph.
// Inputs: number of vertices and true/false for undirected
// Outputs: pointer to the graph G

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) calloc(1, sizeof(Graph));
    G->vertices = vertices;
    G->undirected = undirected;
    return G;
}

// The graph_delete() function frees the memory allocated to the graph
// Inputs: a pointer to the pointer of the graph
// Outputs: none

void graph_delete(Graph **G) {
    free(*G);
    *G = NULL;
    return;
}

// The graph_vertices() function finds out how many vertices are in the graph
// Inputs: a pointer to the graph
// Outputs: the number of vertices in the graph

uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

// The graph_add_edge() function adds an edge to the graph with a given weight
// Inputs: a pointer to the graph, the first vertex, second vertex,
// and the weight of the edge
// Outputs: true or false depending on if both vertices are within bounds and
// were successfully added

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (G) {
        if ((i < G->vertices) && (j < G->vertices)) {
            G->matrix[i][j] = k;
            if (G->undirected) {
                G->matrix[j][i] = k;
            }
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

// The graph_has_edge() function checks if two vertices are within bounds and if
// an edge exists between them
// Inputs: a pointer to the graph, the first vertex, and the second vertex
// Outpus: true or false depending on if the edge exists

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if ((i < G->vertices) && (j < G->vertices) && (G->matrix[i][j] > 0)) {
        return true;
    } else {
        return false;
    }
}

// The graph_edge_weight() function gives the weight of the edge connecting two vertices
// Inputs: a pointer to the graph, the first vertex, and the second vertex
// Outputs: weight of the edge

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if ((i > G->vertices) || (j > G->vertices)) {
        return 0;
    } else {
        return G->matrix[i][j];
    }
}

// The graph_visited() function examines if a given vertex has been visited
// Inputs: a pointer to the graph, the vertex
// Outputs: true or false depending on if the vertex has been visited

bool graph_visited(Graph *G, uint32_t v) {
    if (G->visited[v]) {
        return true;
    } else {
        return false;
    }
}

// The graph_mark_visited() function marks vertex as visited
// Inputs: a pointer to the graph, the vertex
// Outputs: none

void graph_mark_visited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        G->visited[v] = true;
    }
    return;
}

// The graph_mark_unvisited() function marks vertex as unvisited
// Inputs: a pointer to the graph, the vertex
// Outputs: none

void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        G->visited[v] = false;
    }
    return;
}

// The graph_print() function prints out the graph so we can check if the
// graph ADT is working properly
// Inputs: a pointer to the graph
// Outputs: none

void graph_print(Graph *G) {
    for (uint32_t column = 0; column < G->vertices; column += 1) {
        for (uint32_t row = 0; row < G->vertices; row += 1) {
            printf("%3u", G->matrix[row][column]);
        }
        printf("\n");
    }
    return;
}
