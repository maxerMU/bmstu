#include "display_edge.h"
#include "errors.h"

int to_display_edge(display_edge_t &disp_edge, const edge_t &edge)
{
    int rc = to_display_point(disp_edge.p1, edge.p1);
    if (!rc)
        rc = to_display_point(disp_edge.p2, edge.p2);

    return rc;
}
