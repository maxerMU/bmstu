#include "exit_codes.h"
#include "graph.h"

#define INPUT_FILE "input.txt"

int read_graph(graph_t *graph)
{
    size_t size;
    printf("Input number of nodes in graph: ");
    if (scanf("%zu", &size) != 1)
        return READ_ER;
    int rc = create_graph(graph, size);
    if (rc)
        return rc;
    
    int choise;
    printf("\n1 - read from stdin\n"
           "2 - read from file\n"
           "choose input method: ");
    if (scanf("%d", &choise) != 1 || choise < 1 || choise > 2)
    {
        free_graph(*graph);
        return READ_ER;
    }

    if (choise == 1)
        printf("input edges <edge type> <node from> <node to> <edge cost>\n"
               "to exit input -1 type\n");
    
    FILE *f = (choise == 1) ? stdin : fopen(INPUT_FILE, "r");
    if (!f)
    {
        free_graph(*graph);
        return OPEN_ER;
    }

    rc = fread_graph(f, *graph);
    
    if (choise == 2)
        fclose(f);
    
    if (rc)
        free_graph(*graph);
    
    return rc;
}

int way(graph_t graph, char **colors)
{
    size_t start;
    printf("Input start: ");
    if (scanf("%zu", &start) != 1 || start >= graph.size)
        return READ_ER;

    size_t finish;
    printf("Input finish: ");
    if (scanf("%zu", &finish) != 1 || finish >= graph.size)
        return READ_ER;
    
    size_t min_lenght;
    int rc = find_way(graph, start, finish, &min_lenght, colors);
    if (rc == NOT_FOUND)
        printf("Not found.\n");
    
    if (rc)
        return rc;
    
    printf("min length - %zu\n", min_lenght);
    
    return EXIT_SUCCESS;
}

int main(void)
{
    char *colors[ROAD_TYPES] = {"red", "purple"};
    graph_t graph;
    int choise = 10;
    while (choise)
    {
        printf("\n1 - read graph\n"
               "2 - write graph\n"
               "3 - find way\n"
               "0 - exit\n"
               "Your choise: ");
        if (scanf("%d", &choise) != 1)
            continue;
        if (choise == 1)
        {
            int rc = read_graph(&graph);
            if (rc)
                return rc;
        }
        else if (choise == 2)
            write_graph(graph, colors);
        else if (choise == 3)
            way(graph, colors);
    }

    free_graph(graph);

    return EXIT_SUCCESS;
}