#ifndef GRAPH_H
#define GRAPH_H
#include <time.h>

typedef struct Graph{
	int size;
	struct Node *list;
}Graph;

typedef struct Node{
	char *name;
	int x, y;
	struct Edge *list;
	struct Node *next;
	int color;
	int d;
	struct Node *pred;
} Node;

typedef struct Edge{//ребро
        struct Node *end;//другая вершина
        struct Edge *next;
} Edge;

typedef struct List{
	struct Node *node;
	struct List *next;
} List;

List *newlist();
int delGraph(Graph *);
int is_bridge(Node *, Node *);
int is_vertex_cut(List *, Node *);
int dfs(Graph *, List *, int *, int *, int *, int, int, int, int);
int T_Find_bridges(Graph *, int);
int T_Add_node(Graph *, char *, int, int);
int check(Graph *, char *);
int T_Add_edge(Graph *, char *, char *);
int T_Delete_node(Graph *, char *);
int T_Delete_edge(Graph *, char *, char *);
int init_BFS(Graph *, char *);
int list_put(List *, Node *);
int find_BFS(List *);
int print_BFS(Node *, Node *);
int find_path(Graph *, Node *);
int T_Breadth_First_Search(Graph *, char *, char *, int);
int init_find(Graph *, char *);
int T_Find_min_path(Graph *, char *, char *, int);
int T_Find_min_spanning_tree(Graph *, Graph *, char *);
int T_Timing(Graph *, int, int);
char *new_name();
int T_Random(Graph *, int);
int file(Graph *);
int file_end(Graph *);

#endif //GRAPH_H
