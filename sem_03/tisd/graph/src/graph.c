#include "exit_codes.h"
#include "graph.h"

lnode_t *create_lnode()
{
    lnode_t *lnode = malloc(sizeof(lnode_t));

    return lnode;
}

void free_lnode(lnode_t *lnode)
{
    free(lnode);
}

void free_list(lnode_t *lnode)
{
    while (lnode)
    {
        lnode_t *next = lnode->next;
        free_lnode(lnode);
        lnode = next;
    }
}

int add_without_repeat(lnode_t **head, size_t id, size_t cost)
{
    lnode_t *cur = *head;
    while (cur)
    {
        if (cur->id == id)
            return EXIT_SUCCESS;
        cur = cur->next;
    }
    
    cur = create_lnode();
    if (!cur)
        return MEM_ER;
    
    cur->id = id;
    cur->cost = cost;
    cur->next = *head;
    *head = cur;

    return EXIT_SUCCESS;
}

int create_graph(graph_t *graph, size_t size)
{
    graph->graph = malloc(size * sizeof(gnode_t));
    if (!graph->graph)
        return MEM_ER;
    
    graph->size = size;
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < ROAD_TYPES; j++)
            graph->graph[i].near_roads[j] = NULL;
    }
    
    return EXIT_SUCCESS;
}

void free_graph(graph_t graph)
{
    for (size_t i = 0; i < graph.size; i++)
    {
        for (size_t j = 0; j < ROAD_TYPES; j++)
            free_list(graph.graph[i].near_roads[j]);
    }
    
    free(graph.graph);
}

int fread_graph(FILE *src, graph_t graph)
{
    long type;
    size_t id_from, id_to, cost;
    while (1)
    {
        if (fscanf(src, "%ld", &type) != 1 || type >= ROAD_TYPES)
            return READ_ER;
        if (type < 0)
            return EXIT_SUCCESS;
        if (fscanf(src, "%zu %zu %zu", &id_from, &id_to, &cost) != 3)
            return READ_ER;
        if (id_from >= graph.size || id_to >= graph.size)
            return READ_ER;

        int rc = add_without_repeat(&graph.graph[id_from].near_roads[type], id_to, cost);
        if (rc)
            return rc;
        rc = add_without_repeat(&graph.graph[id_to].near_roads[type], id_from, cost);
        if (rc)
            return rc;
    }    
}

int graph_to_dot(char *file_name, graph_t graph, char **colors)
{
    FILE *f = fopen(file_name, "w");
    if (!f)
        return OPEN_ER;
    
    fprintf(f, "graph my_graph {\n");
    for (size_t i = 0; i < graph.size; i++)
    {
        fprintf(f, "%zu\n", i);
        for (size_t j = 0; j < ROAD_TYPES; j++)
        {
            lnode_t *cur = graph.graph[i].near_roads[j];
            while (cur)
            {
                if (cur->id <= i)
                    fprintf(f, "%zu -- %zu [color = \"%s\", label = \"%zu\"]\n",
                            i, cur->id, colors[j], cur->cost);
                cur = cur->next;
            }
        }
    }
    fprintf(f, "}");

    fclose(f);

    return EXIT_SUCCESS;
}

int write_graph(graph_t graph, char **colors)
{
    int rc = graph_to_dot(VIZ_FILE_PATH, graph, colors);
    if (rc)
        return rc;
    
    system("dot -Tpng viz/graph.gv -o viz/graph.png && libreoffice --draw viz/graph.png");

    return EXIT_SUCCESS;
}

void dijkstra_init(graph_t graph, size_t start)
{
    for (size_t i = 0; i < graph.size; i++)
    {
        graph.graph[i].way.arived = 0;
        graph.graph[i].way.edge_type = ROAD_TYPES;
        if (i == start)
        {
            graph.graph[i].way.from = start;
            graph.graph[i].way.length = 0;
        }
        else
        {
            graph.graph[i].way.from = INF;
            graph.graph[i].way.length = INF;
        }
    }
}

void dijkstra_relax(graph_t graph, size_t from, size_t to, size_t edge_length, size_t edge_type)
{
    if (graph.graph[to].way.length > graph.graph[from].way.length + edge_length)
    {
        graph.graph[to].way.length = graph.graph[from].way.length + edge_length;
        graph.graph[to].way.from = from;
        graph.graph[to].way.edge_type = edge_type;
    }
}

size_t find_next_node(graph_t graph)
{
    size_t next_node = INF;
    for (size_t i = 0; i < graph.size; i++)
        if (!graph.graph[i].way.arived && graph.graph[i].way.length != INF)
            if (next_node == INF || graph.graph[next_node].way.length > graph.graph[i].way.length)
                next_node = i;
    
    return next_node;
}

void dijkstra(graph_t graph, size_t start, size_t finish)
{
    dijkstra_init(graph, start);

    size_t next_node = find_next_node(graph);
    while (next_node < graph.size && next_node != finish)
    {
        graph.graph[next_node].way.arived = 1;
        for (size_t j = 0; j < ROAD_TYPES; j++)
        {
            lnode_t *cur = graph.graph[next_node].near_roads[j];
            while (cur)
            {
                dijkstra_relax(graph, next_node, cur->id, cur->cost, j);
                cur = cur->next;
            }
        }
        next_node = find_next_node(graph);
    }
}

void two_nodes_inf(graph_t graph, size_t node1, size_t node2, size_t start, size_t finish,
                   size_t cost, size_t *change, int *in_way)
{
    size_t cur_node = finish;
    *change = 0;
    *in_way = 0;
    while (cur_node != start && cur_node != INF)
    {
        if (cur_node == node2 && graph.graph[cur_node].way.from == node1)
        {
            if (graph.graph[node1].way.edge_type != graph.graph[node2].way.edge_type)
                *change = 1;
            if (graph.graph[node2].way.length - graph.graph[node1].way.length == cost)
                *in_way = 1;
        }
        if (cur_node == node1 && graph.graph[cur_node].way.from == node2)
        {
            if (graph.graph[node1].way.edge_type != graph.graph[node2].way.edge_type)
                *change = 2;
            if (graph.graph[node1].way.length - graph.graph[node2].way.length == cost)
                *in_way = 1;
        }
        cur_node = graph.graph[cur_node].way.from;
    }
}

long type_min_edge_btw_2(graph_t graph, size_t node1, size_t node2, size_t *cost)
{
    long type = ROAD_TYPES;
    *cost = INF;
    for (size_t j = 0; j < ROAD_TYPES; j++)
    {
        lnode_t *cur = graph.graph[node1].near_roads[j];
        while (cur)
        {
            if (cur->id == node2 && cur->cost < *cost)
            {
                *cost = cur->cost;
                type = j;
            }
            cur = cur->next;
        }
        
    }

    return type;
}

int find_way(graph_t graph, size_t start, size_t finish, size_t *min_length, char **colors)
{
    dijkstra(graph, start, finish);
    if (graph.graph[finish].way.length == INF)
        return NOT_FOUND;
    
    *min_length = graph.graph[finish].way.length;
    
    FILE *f = fopen(VIZ_FILE_PATH, "w");
    if (!f)
        return OPEN_ER;
    
    fprintf(f, "graph way_graph {\n");
    for (size_t i = 0; i < graph.size; i++)
    {
        fprintf(f, "%zu\n", i);
        for (size_t j = 0; j < ROAD_TYPES; j++)
        {
            lnode_t *cur = graph.graph[i].near_roads[j];
            while (cur)
            {
                size_t width = 1, change;
                int in_way;
                two_nodes_inf(graph, i, cur->id, start, finish, cur->cost, &change, &in_way);
                if (in_way)
                    width = 5;
                if (change == 1)
                    fprintf(f, "%zu [shape = \"%s\", penwidth = %d]\n", i, "box", 3);
                else if (change == 2)
                    fprintf(f, "%zu [shape = \"%s\", penwidth = %d]\n", cur->id, "box", 3);
                if (cur->id <= i)
                    fprintf(f, "%zu -- %zu [color = \"%s\", label = \"%zu\", penwidth = \"%zu\"]\n",
                            i, cur->id, colors[j], cur->cost, width);
                cur = cur->next;
            }
        }
    }
    fprintf(f, "}");

    fclose(f);

    system("dot -Tpng viz/graph.gv -o viz/graph.png && libreoffice --draw viz/graph.png");

    return EXIT_SUCCESS;
}