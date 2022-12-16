// CITE: TA Eugene (section video) for how to use standard input, was able to learn how to do
// FILE *infile = stdin, FILE *outfile = stdout, fgets(name, 1024, infile), and
// name[strlen(name) - 1] = '\0' after video
// CITE: I learned how to read input using fscanf from C in a Nutshell (textbook), ch18
// and from visiting multiple sections, and from my dad.

#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// The function message() prints out how to properly use this program.
// Inputs: none
// Outputs: none

void message(void) {
    fprintf(stderr, "SYNOPSIS\n"
                    "  Traveling Salesman Problem using DFS.\n"
                    "\n"
                    "USAGE\n"
                    "  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n"
                    "\n"
                    "OPTIONS\n"
                    "  -u             Use undirected graph.\n"
                    "  -v             Enable verbose printing.\n"
                    "  -h             Program usage and help.\n"
                    "  -i infile      Input containing graph (default: stdin)\n"
                    "  -o outfile     Output of computed path (default: stdout)\n");
    return;
}

// The dfs() function implements Depth-First Search to find the shortest Hamiltonian
// Paths for a given graph, and stores it into the path "shortest".
// Inputs: a pointer to the graph, the origin vertex, the current path, the shortest path,
// an array of cities, the outfile, boolean for if the user specified verbose priting, and
// the recursion count.
// Outputs: none

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile,
    bool verbose, uint32_t *r) {
    uint32_t variable = 0;
    graph_mark_visited(G, v);
    *r += 1;

    // Add vertex to path if not full, and loop through adjacent vertices of vertex
    // if they have not been visited yet
    if (path_push_vertex(curr, v, G) && (path_vertices(curr) != graph_vertices(G))) {
        for (uint32_t next = 0; next < graph_vertices(G); next += 1) {
            if (graph_has_edge(G, v, next) && !graph_visited(G, next)) {
                dfs(G, next, curr, shortest, cities, outfile, verbose, r);
            }
        }
    } else {
        // we are at the end of the path, so alter the shortest path if needed and
        // print if specified
        if (graph_has_edge(G, v, 0) && (path_push_vertex(curr, 0, G))) {
            if ((path_length(curr) < path_length(shortest)) || (path_length(shortest) == 0)) {
                path_copy(shortest, curr);
            }
            if (verbose) {
                printf("Path length: %u\n", path_length(curr));
                path_print(curr, outfile, cities);
            }
            path_pop_vertex(curr, &variable, G);
        }
    }
    path_pop_vertex(curr, &variable, G);
    graph_mark_unvisited(G, variable);
    return;
}

#define OPTIONS "uvhi:o:"

int main(int argc, char **argv) {
    // undirected signifies if the graph is undirected
    // verbose signifies if the user wants to print each path
    // infile and outfile describe the input and output
    bool undirected = false;
    bool verbose = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;

    int option = 0;
    while ((option = getopt(argc, argv, OPTIONS)) != -1) {
        switch (option) {
        case 'h': {
            message();
            return 0;
        }
        case 'u': {
            undirected = true;
            break;
        }
        case 'v': {
            verbose = true;
            break;
        }
        case 'i':
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                infile = stdin;
            }
            break;
        case 'o':
            outfile = fopen(optarg, "w");
            if (outfile == NULL) {
                outfile = stdout;
            }
            break;
        default: {
            message();
            return 0;
        }
        }
    }

    // The number of locations in the graph must be smaller than VERTICIES
    uint32_t num_locations = 0;
    int num;
    num = fscanf(infile, "%" SCNu32 "\n", &num_locations);
    if ((num != 1) || (num_locations > VERTICES)) {
        fprintf(stderr, "Error: malformed number of vertices.\n");
        return 0;
    }

    // The graph must have the above specified number of verticies
    // and undirected quality
    Graph *graph = graph_create(num_locations, undirected);

    // The names of the locations will be stored in the locations array
    char name[1024];
    char *locations[num_locations];
    for (uint32_t i = 0; i < num_locations; i += 1) {
        fgets(name, 1024, infile);
        name[strlen(name) - 1] = '\0';
        locations[i] = strdup(name);
    }

    // The variables i and j are two vertices and the weight of each
    // edge connecting i to j is represented by k
    uint32_t i = 0, j = 0, k = 0;
    int tup;
    while ((tup = fscanf(infile, "%" SCNu32 " %" SCNu32 " %" SCNu32 "\n", &i, &j, &k)) != EOF) {
        // Each i, j, and k value must be valid
        if (tup == 3) {
            graph_add_edge(graph, i, j, k);
        } else {
            fprintf(stderr, "Error: malformed edge.\n");
            for (uint32_t i = 0; i < num_locations; i += 1) {
                free(locations[i]);
            }
            graph_delete(&graph);
            return 0;
        }
    }

    // Now we can finally check for the paths
    if ((i + j + k) && (num_locations > 2)) {
        uint32_t recursive = 0;
        Path *current = path_create();
        Path *shortest = path_create();
        // Find shortest part using DFS
        dfs(graph, START_VERTEX, current, shortest, locations, outfile, verbose, &recursive);

        // If something went wrong and the shortest possible path is
        // of length 0, then there is no hamiltonian path on the graph
        if (path_length(shortest) == 0) {
            fprintf(stderr, "No Hamiltonian path found.\n");
            printf("Total recursive calls: %u\n", recursive);

            // get rid of all memory right away and exit program
            path_delete(&current);
            path_delete(&shortest);
            for (uint32_t i = 0; i < num_locations; i += 1) {
                free(locations[i]);
            }
            graph_delete(&graph);
            return 1;
        }
        // Otherwise, the length, path and number of recursive calls will be printed
        printf("Path length: %u\n", path_length(shortest));
        path_print(shortest, outfile, locations);
        printf("Total recursive calls: %u\n", recursive);

        // free memory from paths
        path_delete(&current);
        path_delete(&shortest);
    } else {
        printf("There's nowhere to go.\n");
    }

    // free the memory for location names
    for (uint32_t i = 0; i < num_locations; i += 1) {
        free(locations[i]);
    }

    // free memory from graph
    graph_delete(&graph);

    return 0;
}
