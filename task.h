#ifndef TASK_H
#define TASK_H
#include "graph.h"

int D_Graphviz(Graph *);
int D_Find_bridges(Graph *);
int D_Add_node(Graph *);
int D_Add_edge(Graph *);
int D_Delete_node(Graph *);
int D_Delete_edge(Graph *);
int D_Show(Graph *);
int D_Breadth_First_Search(Graph *);
int D_Find_min_path(Graph *);
int D_Find_min_spanning_tree(Graph *);
int D_Timing(Graph *);
int D_Random(Graph *);

#endif // TASK_H
