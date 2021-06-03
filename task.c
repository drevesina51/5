#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"

    /* массив диагностических сообщений об ошибках */
const char *errmsgs[] = {"Ok", "Duplicate node", "No such nodes", "Input Error", "No path between nodes", "Error try alloc",
			 "No bridges", "No vertex_cut", "No bridges & No vertex_cut"};

int D_Graphviz(Graph *graph){
	Node *node = graph->list;
	Edge *edge = node->list;
	int edges = 0;
        for (int j = 0; j < graph->size; j++){
                edge = node->list;
                while (edge != NULL){
                        edges ++;
                        edge = edge->next;
                }
                node = node->next;
        }
        node = graph->list;
        edge = node->list;
	printf("\ndigraph test{\n");
        for (int i = 0; i < edges; i++){
                while (edge == NULL){
                        node = node->next;
                        edge = node->list;
                }
                printf("   %s -> %s;\n", node->name, edge->end->name);
                edge = edge->next;
        }
	printf("}\n");
	return 1;
}

int D_Find_bridges(Graph *graph){
        int rc = 0, x;
	int flag = 1;
	x = T_Find_bridges(graph, flag);
	if (x == 0) rc = 8;
	else if (x == 1) rc = 6;
		else if (x == 2) rc = 7;
			else rc = 0;
        printf("%s\n", errmsgs[rc]);
        return 1;
}

int D_Add_node(Graph *graph){
	int n, rc = 0;
	int num1, num2;
	char *name = (char *)calloc(15, sizeof(char));
	if (name == NULL) rc = 5;
	printf("Enter name: -->\n");
	n = scanf("%s", name);
        if (n == EOF) return 0;
	printf("Enter x: -->\n");
        n = scanf("%d", &num1);
        if (n == EOF) return 0;
	printf("Enter y: -->\n");
        n = scanf("%d", &num2);
        if (n == EOF) return 0;
	if (check(graph, name) == 1) rc = 1;
	else if (T_Add_node(graph, name, num1, num2) == 0) rc = 5;
	printf("%s\n", errmsgs[rc]);
	return 1;
}

int D_Add_edge(Graph *graph){
        int n, rc = 0;
        char *name1 = (char *)calloc(15, sizeof(char));
	if (name1 == NULL) rc = 5;
        printf("Enter node 1: -->\n");
        n = scanf("%s", name1);
        if (n == EOF) return 0;
        char *name2 = (char *)calloc(15, sizeof(char));
	if (name2 == NULL) rc = 5;
        printf("Enter node 2: -->\n");
        n = scanf("%s", name2);
        if (n == EOF) return 0;
	if (check(graph, name1) == 0 || check(graph, name2) == 0) rc = 2;
        else if (T_Add_edge(graph, name1, name2) == 0) rc = 5;
	printf("%s\n", errmsgs[rc]);
        return 1;
}

int D_Delete_node(Graph *graph){
        int n, rc = 0;
        char *name = (char *)calloc(15, sizeof(char));
	if (name == NULL) rc = 5;
        printf("Enter name: -->\n");
        n = scanf("%s", name);
        if (n == EOF) return 0;
	if (check(graph, name) == 0) rc = 2;
        else T_Delete_node(graph, name);
	free(name);
        printf("%s\n", errmsgs[rc]);
        return 1;
}

int D_Delete_edge(Graph *graph){
        int n, rc = 0;
        char *name1 = (char *)calloc(15, sizeof(char));
	if (name1 == NULL) rc = 5;
        printf("Enter name1: -->\n");
        n = scanf("%s", name1);
        if (n == EOF) return 0;
        char *name2 = (char *)calloc(15, sizeof(char));
	if (name2 == NULL) rc = 5;
        printf("Enter name2: -->\n");
        n = scanf("%s", name2);
        if (n == EOF) return 0;
	if (check(graph, name1) == 0 || check(graph, name2) == 0) rc = 2;
	else T_Delete_edge(graph, name1, name2);
	free(name1);
	free(name2);
	printf("%s\n", errmsgs[rc]);
        return 1;
}

int D_Show(Graph *graph){
	Node *ptr = graph->list;
	Edge *tmp;
	for (int i = 0; i < graph->size; i++){
		tmp = ptr->list;
		printf("\n%d) node name = %s : x = %d, y = %d; edges : ", i, ptr->name, ptr->x, ptr->y);
		while (tmp != NULL) {
			printf("(%s , %s); ", ptr->name, tmp->end->name);
			tmp = tmp->next;
		}
		ptr = ptr->next;
	}
	printf("\n");
        return 1;
}

int D_Breadth_First_Search(Graph *graph){
        int n, rc = 0, flag = 1;
        char *name1 = (char *)calloc(15, sizeof(char));
	if (name1 == NULL) rc = 5;
        printf("Enter node 1: -->\n");
        n = scanf("%s", name1);
        if (n == EOF) return 0;
        char *name2 = (char *)calloc(15, sizeof(char));
	if (name2 == NULL) rc = 5;
        printf("Enter node 2: -->\n");
        n = scanf("%s", name2);
        if (n == EOF) return 0;
	if (check(graph, name1) == 0 || check(graph, name2) == 0) rc = 2;
        else if (T_Breadth_First_Search(graph, name1, name2, flag) == 0) rc = 4;
        free(name1);
	free(name2);
        printf("\n%s\n", errmsgs[rc]);
        return 1;
}

int D_Find_min_path(Graph *graph){
        int n, rc = 0, flag = 1;
        char *name1 = (char *)calloc(15, sizeof(char));
	if (name1 == NULL) rc = 5;
        printf("Enter node 1: -->\n");
        n = scanf("%s", name1);
        if (n == EOF) return 0;
        char *name2 = (char *)calloc(15, sizeof(char));
	if (name2 == NULL) rc = 5;
        printf("Enter node 2: -->\n");
        n = scanf("%s", name2);
        if (n == EOF) return 0;
	if (check(graph, name1) == 0 || check(graph, name2) == 0) rc = 2;
        else if (T_Find_min_path(graph, name1, name2, flag) == 0) rc = 4;
        free(name1);
        free(name2);
        printf("\n%s\n", errmsgs[rc]);
        return 1;
}

int D_Find_min_spanning_tree(Graph *graph){
	int n, rc = 0;
        Graph *tree = (Graph *)calloc(1, sizeof(Graph)); // создание пустого графа
        if(graph == NULL) rc = 5;
        tree->size = 0;
        tree->list = NULL;
	char *name = (char *)calloc(15, sizeof(char));
        if (name == NULL) rc = 5;
        printf("Enter root (name): -->\n");
        n = scanf("%s", name);
        if (n == EOF) return 0;
	if (check(graph, name) == 0) rc = 2;
	else if (T_Find_min_spanning_tree(graph, tree, name) == 0) rc = 4;
	D_Show(tree);
	D_Graphviz(tree);
	free(tree);
	printf("\n%s\n", errmsgs[rc]);
        return 1;
}

int D_Timing(Graph *graph){
        int n, num, rc = 0, var;
        printf("Enter number of nodes: -->\n");
        n = scanf("%d", &num);
        if (n == EOF) return 0;
	printf("Enter function: -->\n1) Breadth_First_Search\n2) Find_min_path\n3) Find_bridges\n");
        n = scanf("%d", &var);
        if (n == EOF) return 0;
        if (T_Random(graph, num) == 0) rc = 5;
	T_Timing(graph, num, var);
        printf("\n%s\n", errmsgs[rc]);
        return 1;
}

int D_Random(Graph *graph){
        int n, num, rc = 0;
        printf("Enter number of nodes: -->\n");
        n = scanf("%d", &num);
        if (n == EOF) return 0;
        if (T_Random(graph, num) == 0) rc = 5;
	printf("\n%s\n", errmsgs[rc]);
	return 1;
}
