// CITE: Path struct was provided by professor

#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// The struct Path defines the components of a path to travel
// vertices: the locations involved in the path
// length: the length of the journey in total

struct Path {
    Stack *vertices;
    uint32_t length;
};

// The path_create() function constructs the path
// Inputs: none
// Outputs: a pointer to path p

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p) {
        p->vertices = stack_create(VERTICES);
        p->length = 0;
    }
    return p;
}

// The path_delete function destructs the path and any memory
// allocated to the path on the way
// Inputs: a pointer to the pointer to the path
// Outputs: none

void path_delete(Path **p) {
    if (*p && (*p)->vertices) {
        stack_delete(&(*p)->vertices);
        free(*p);
        *p = NULL;
    }
    return;
}

// The path_push_vertex() function pushes a location (in the
// form of a vertex) into the path
// Inputs: a pointer to the path, vertex v, and a
// pointer to the graph
// Outputs: true or false depending on if push was successful

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t top = 0;
    stack_peek(p->vertices, &top);
    if (stack_push(p->vertices, v)) {
        if (v != top) {
            p->length += graph_edge_weight(G, top, v);
        }
        return true;
    } else {
        return false;
    }
}

// The path_pop_vertex() function pops the vertices stack and
// decreases the length accordingly
// Inputs: a pointer to the path, a pointer to the vertex,
// a pointer to the graph
// Outputs: true or false based on if pop was successful

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    uint32_t top = 0;
    if (stack_pop(p->vertices, v)) {
        stack_peek(p->vertices, &top);
        if (*v != top) {
            p->length -= graph_edge_weight(G, top, *v);
        }
        return true;
    } else {
        return false;
    }
}

// The path_vertices() function counts the number of vertices (or
// locations) in the path
// Inputs: a pointer to path p
// Outputs: number of vertices in the given path

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

// The path_length() function finds the total length of the path
// Inputs: a pointer to path p
// Outputs: the length of the path

uint32_t path_length(Path *p) {
    return p->length;
}

// The path_copy() function copies a path from src to dst
// Inputs: a pointer to two paths
// Outputs: none

void path_copy(Path *dst, Path *src) {
    if (dst && src) {
        stack_copy(dst->vertices, src->vertices);
        dst->length = src->length;
    }
    return;
}

// The path_print() function prints the path to outfile
// Inputs: a pointer to the path, outfile, cities
// Outputs: none

void path_print(Path *p, FILE *outfile, char *cities[]) {
    if (p) {
        fprintf(outfile, "Path: ");
        stack_print(p->vertices, outfile, cities);
    }
    return;
}
