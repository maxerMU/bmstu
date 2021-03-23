#include "convert.h"
#include "point.h"
#include "edge.h"
#include "errors.h"

int read_edge(edge_t &edge, FILE *const src)
{
    size_t temp1, temp2;
    if (fscanf(src, "%zu %zu", &temp1, &temp2) != 2)
        return EDGE_READ_ER;

    edge.p1 = temp1 - 1;
    edge.p2 = temp2 - 1;

    return SUCCESS;
}

void write_edge(FILE * const dst, const edge_t &edge)
{
    fprintf(dst, "%zu %zu", edge.p1 + 1, edge.p2 + 1);
}

bool is_correct_edge(const edge_t &edge, size_t max_num)
{
    return (edge.p1 < max_num) && (edge.p2 < max_num);
}

/*
int move_edge(edge_t &edge, const move_t &move)
{
    int rc = move_point(edge.p1, move);
    if (!rc)
        rc = move_point(edge.p2, move);

    return rc;
}

int scale_edge(edge_t &edge, const scale_t &scale, const point_t &c)
{
    int rc = scale_point(edge.p1, scale, c);
    if (!rc)
        rc = scale_point(edge.p2, scale, c);

    return rc;
}

int rotate_edge(edge_t &edge, const rotate_t &rotate, const point_t &c)
{
    int rc = rotate_point(edge.p1, rotate, c);
    if (!rc)
        rc = rotate_point(edge.p2, rotate, c);

    return rc;
}
*/
