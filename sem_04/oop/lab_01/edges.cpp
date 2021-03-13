#include "edges.h"
#include "errors.h"

edges_t init_edges()
{
    edges_t edges;
    edges.edges = NULL;
    edges.size = 0;

    return edges;
}

bool are_coorect_edges(const edges_t &edges, size_t max_num)
{
    bool correct = true;
    for (size_t i = 0; i < edges.size && correct; i++)
        correct = is_correct_edge(edges.edges[i], max_num);

    return correct;
}

int scan_edges_size(size_t &size, FILE * const src)
{
    size_t temp;
    if (fscanf(src, "%zu", &temp) != 1)
        return EDGES_READ_ER;

    size = temp;

    return SUCCESS;
}

void print_edges_size(size_t size, FILE * const dst)
{
    fprintf(dst, "%zu\n", size);
}

int scan_edges(edges_t &edges, FILE *const src)
{
    int rc = SUCCESS;
    for (size_t i = 0; i < edges.size && !rc; i++)
        rc = read_edge(edges.edges[i], src);

    return rc;
}

void print_edges(FILE *const dst, const edges_t &edges)
{
    for (size_t i = 0; i < edges.size; i++)
    {
        write_edge(dst, edges.edges[i]);
        fprintf(dst, "\n");
    }
}

int edges_mem_manager(edges_t &edges, const size_t size)
{
    edge_t *temp = (edge_t *) realloc(edges.edges, size * sizeof(edge_t));

    if (!temp)
        return EDGES_ALLOC_ER;

    edges.edges = temp;
    edges.size = size;

    return SUCCESS;
}

int read_edges(edges_t &edges, FILE *const src)
{
    size_t size;
    int rc = scan_edges_size(size, src);
    if (rc)
        return rc;

    rc = edges_mem_manager(edges, size);
    if (rc)
        return rc;

    rc = scan_edges(edges, src);
    if (rc)
        edges_mem_manager(edges, 0);

    return rc;
}

void write_edges(FILE *const dst, const edges_t &edges)
{
    print_edges_size(edges.size, dst);
    print_edges(dst, edges);
}

int edges_dup(edges_t &dst, const edges_t &src)
{
    int rc = edges_mem_manager(dst, src.size);
    if (rc)
        return rc;

    for (size_t i = 0; i < dst.size; i++)
        dst.edges[i] = src.edges[i];

    return SUCCESS;
}
