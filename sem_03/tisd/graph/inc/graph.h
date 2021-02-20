#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define VIZ_FILE_PATH "viz/graph.gv"

#define ROAD_TYPES 2

#define INF __SIZE_MAX__

typedef struct
{
    int arived;
    size_t from;
    size_t edge_type;
    size_t length;
}way_inf_t;

typedef struct list_node lnode_t;

struct list_node
{
    size_t id;
    size_t cost;
    lnode_t *next;
};

typedef struct graph_node gnode_t;

struct graph_node
{
    way_inf_t way;
    lnode_t *near_roads[ROAD_TYPES];
};

typedef struct
{
    gnode_t *graph;
    size_t size;
}graph_t;

int create_graph(graph_t *graph, size_t size);
void free_graph(graph_t graph);
int fread_graph(FILE *src, graph_t graph);
int write_graph(graph_t graph, char **colors);
int find_way(graph_t graph, size_t start, size_t finish, size_t *min_length, char **colors);

#endif //GRAPH_H