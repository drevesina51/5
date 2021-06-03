#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

int delGraph(Graph *graph){
	if (graph->size == 0){
		free(graph);
        	return 1;
	}
        Node *ptr = graph->list;
        Edge *tmp;
	Node *ptr1;
	Edge *tmp1;
        for (int i = 0; i < graph->size; i++){
		tmp = ptr->list;
                while (tmp != NULL) {
                        tmp1 = tmp->next;
			free(tmp);
			tmp = tmp1;
                }
		ptr1 = ptr->next;
		free(ptr->name);
		free(ptr);
		ptr = ptr1;
        }
	free(graph);
	return 1;
}

List *newlist(){
        List *Q = (List *)calloc(1, sizeof(List));
        if(Q == NULL) return NULL;
        Q->node = NULL;
        Q->next = NULL;
        return Q;
}

int list_put(List *Q, Node *node){
        List *ptr = Q;
        List *par = NULL;
        while(ptr != NULL){
                par = ptr;
                ptr = ptr->next;
        }
        if (par->node == NULL) {
                Q->node = node;
                return 1;
        }
        List *tmp = newlist();
        tmp->node = node;
        par->next = tmp;
        return 1;
}

int is_bridge(Node *node1, Node *node2){
	printf("Bridge: %s -- %s\n", node1->name, node2->name);
	return 1;
}

int is_vertex_cut(List *node_cut, Node *node){
	List *ptr = node_cut;
	if (ptr->node == NULL){
		list_put(node_cut, node);
		return 1;
	}
	while (ptr != NULL){
		if (ptr->node == node) return 1;
		ptr = ptr->next;
	}
	list_put(node_cut, node);
        return 1;
}

Node *find_node(Graph *graph, int n){
	Node *ptr = graph->list;
	for (int j = 0; j < n; j++)
                ptr = ptr->next;
	return ptr;
}

int dfs(Graph *graph, List *node_cut, int *used, int *tin, int *fup, int v, int k, int timer, int p){
	used[v] = 1;
	tin[v] = timer;
	fup[v] = timer;
	timer ++;
	Node *node, *par, *tmp;
	Edge *edge;
	int to;
	node = find_node(graph, v);
	edge = node->list;
	while (edge != NULL){
		par = find_node(graph, p);
		tmp = graph->list;
		for (int s = 0; s < graph->size; s++){
			if (tmp == edge->end){
				to = s;
				break;
			}
			tmp = tmp->next;
		}
		if (par != tmp){
			if (used [to] == 1){
				if (tin[to] < fup[v])
					fup[v] = tin[to];
			} else {
				k = dfs (graph, node_cut, used, tin, fup, to, k, timer, v);
				if (fup[to] < fup[v])
                                        fup[v] = fup[to];
				par = find_node(graph, v);
				if (fup[to] > tin[v]){
					tmp = find_node(graph, to);
					is_bridge(par, tmp);
					k++;
				}
				if (fup[to] >= tin[v] && graph->list != par)
					is_vertex_cut(node_cut, par);
			}
		}
		edge = edge->next;
	}
	return k;
}

int print_node_cut(List *node_cut){
	int p = 0;
	List *ptr = node_cut;
	if (ptr->node == NULL) return p;
	while (ptr != NULL){
		printf("Vertex_cut: %s\n", ptr->node->name);
		ptr = ptr->next;
		p++;
	}
	return p;
}

int T_Find_bridges(Graph *graph, int flag){
	int k = 0, p = 0;
	int q = -1;
	int timer = 0;
	int used[graph->size];
	int tin[graph->size];
	int fup[graph->size];
	List *node_cut = newlist();
	for (int i = 0; i < graph->size; i++)
		used[i] = 0;
	for (int j = 0; j < graph->size; j++)
		if (used[j] == 0)
			k = dfs (graph, node_cut, used, tin, fup, j, k, timer, q);
	if (flag == 1) p = print_node_cut(node_cut);
	free(node_cut);
	if (k == 0 && p == 0) return 0;
	else if (k == 0) return 1;
	     else if (p == 0) return 2;
	return 3;
}

int T_Add_node(Graph *graph, char *name, int num1, int num2){
	Node *node = (Node *)calloc(1, sizeof(Node));
        if(node == NULL) return 0;
	node->name = name;
	node->x = num1;
	node->y = num2;
	node->list = NULL;
	node->next = NULL;
	graph->size++;
	if (graph->list == NULL) {
		graph->list = node;
		return 1;
	}
	Node *ptr = graph->list;
	while(ptr->next != NULL) ptr = ptr->next;
	ptr->next = node;
        return 1;
}

int check(Graph *graph, char *name){
	Node *ptr = graph->list;
	for (int i = 0; i < graph->size; i++){
		if (strcmp(ptr->name, name) == 0) return 1;
		ptr = ptr->next;
	}
	return 0;
}

int T_Add_edge(Graph *graph, char *name1, char *name2){
	Edge *edge1 = (Edge *)calloc(1, sizeof(Edge));
        if(edge1 == NULL) return 0;
        Edge *edge2 = (Edge *)calloc(1, sizeof(Edge));
        if(edge2 == NULL) return 0;
	Node *ptr = graph->list;
	Node *node1;
	Node *node2;
	int flag = 0;
        for (int i = 0; i < graph->size; i++){
		if (strcmp(ptr->name, name1) == 0){
			node1 = ptr;
			flag++;
		}
		if (strcmp(ptr->name, name2) == 0){
			node2 = ptr;
			flag++;
		}
		if (flag == 2) break;
		ptr = ptr->next;
	}
	Edge *tmp;
	tmp = node1->list;
	Edge *prev;
	if (tmp == NULL) node1->list = edge1;
	else {
		while(tmp != NULL){
			prev = tmp;
			tmp = tmp->next;
	        }
	        prev->next = edge1;
	     }
	edge1->end = node2;
	edge1->next = NULL;
        tmp = node2->list;
	if (tmp == NULL) node2->list = edge2;
	else {
        	while(tmp != NULL){
                	prev = tmp;
                	tmp = tmp->next;
		}
		prev->next = edge2;
        }
        edge2->end = node1;
        edge2->next = NULL;
        return 1;
}

int T_Delete_edge(Graph *graph, char *name1, char *name2){
        Node *ptr = graph->list;
        Edge *prev = NULL;
	Edge *tmp;
	Node *node1;
        Node *node2;
        int flag = 0;
        for (int i = 0; i < graph->size; i++){
                if (strcmp(ptr->name, name1) == 0){
                        node1 = ptr;
                        flag++;
                }
                if (strcmp(ptr->name, name2) == 0){
                        node2 = ptr;
                        flag++;
                }
                if (flag == 2) break;
                ptr = ptr->next;
        }
	tmp = node1->list;
	while(tmp->end != node2){
                prev = tmp;
                tmp = tmp->next;
        }
        if (prev == NULL) node1->list = tmp->next;
	else prev->next = tmp->next;
	free(tmp);
	prev = NULL;
	tmp = node2->list;
        while(tmp->end != node1){
                prev = tmp;
                tmp = tmp->next;
        }
        if (prev == NULL) node2->list = tmp->next;
        else prev->next = tmp->next;
        free(tmp);
        return 1;
}

int T_Delete_node(Graph *graph, char *name){
        Node *ptr = graph->list;
        Node *prev = NULL;
        Node *node;
        for (int i = 0; i < graph->size; i++){
                if (strcmp(ptr->name, name) == 0){
                        node = ptr;
                        break;
                }
                prev = ptr;
                ptr = ptr->next;
        }
        Edge *tmp = node->list;
	Edge *par;
        while(tmp != NULL){
		par = tmp;
		tmp = tmp->next;
                T_Delete_edge(graph, name, par->end->name);
        }
        if (prev == NULL) graph->list = node->next;
        else prev->next = node->next;
	graph->size--;
        free(node->name);
        free(node);
        return 1;
}

int init_BFS(Graph *graph, char *name){
	Node *ptr = graph->list;
	Node *node;
	for (int i = 0; i < graph->size; i++){
		if (strcmp(ptr->name, name) == 0) node = ptr;
                ptr->color = 0;
		ptr->d = -1;
		ptr->pred = NULL;
                ptr = ptr->next;
        }
	node->color = 0;
	node->d = 1;
	node->pred = NULL;
	return 1;
}

int find_BFS(List *Q){
	List *tmp;
	Edge *edge;
	while (Q->node != NULL){
                tmp = Q;
                edge = tmp->node->list;
		while (edge != NULL){
			if (edge->end->color == 0){
				edge->end->color = 1;
				edge->end->d = tmp->node->d + 1;
				edge->end->pred = tmp->node;
				list_put(Q, edge->end);
			}
			edge = edge->next;
		}
		tmp->node->color = 2;
		if (Q->next == NULL) Q->node = NULL;
		else {
			Q = Q->next;
		}
	}
	return 1;
}

int print_BFS(Node *node1, Node *node2){
	if (node1 == node2){
		printf("%s", node2->name);
		return 1;
	}
	if (node2->pred == NULL) return 0;
	else {
		print_BFS(node1, node2->pred);
		printf(" -> %s", node2->name);
	}
	return 1;
}

int T_Breadth_First_Search(Graph *graph, char *name1, char *name2, int flag_t){
	Node *ptr = graph->list;
	Node *node1;
	Node *node2;
	init_BFS(graph, name1);
	int flag = 0;
        for (int i = 0; i < graph->size; i++){
                if (strcmp(ptr->name, name1) == 0){
                        node1 = ptr;
                        flag++;
                }
                if (strcmp(ptr->name, name2) == 0){
                        node2 = ptr;
                        flag++;
                }
                if (flag == 2) break;
                ptr = ptr->next;
        }
	List *Q = newlist();
	list_put(Q, node1);
	find_BFS(Q);
	free(Q);
	if (flag_t == 1)
		if (print_BFS(node1, node2) == 0) return 0;
        return 1;
}

int init_find(Graph *graph, char *name){
        Node *ptr = graph->list;
        Node *node;
        for (int i = 0; i < graph->size; i++){
                if (strcmp(ptr->name, name) == 0) node = ptr;
                ptr->d = 1000000;
                ptr->pred = NULL;
                ptr = ptr->next;
        }
        node->d = 0;
        return 1;
}

int find_path(Graph *graph, Node *node1){
        Node *node;
        Edge *edge;
	if (node1->list == NULL) return 1;
        int edges = 0;
	node = graph->list;
        for (int j = 0; j < graph->size; j++){
                edge = node->list;
                while (edge != NULL){
                        edges ++;
                        edge = edge->next;
                }
                node = node->next;
        }
        for (int i = 0; i < graph->size; i++){
		node = graph->list;
		edge = node->list;
                for (int f = 0; f < edges; f++){
			while (edge == NULL){
				node = node->next;
                                while (node->list == NULL){
					node = node->next;
				}
                                edge = node->list;
                        }
			if (edge->end->d > node->d + 1){
                        	edge->end->d = node->d + 1;
				edge->end->pred = node;
                        }
			edge = edge->next;
		}
	}
        return 1;
}

int T_Find_min_path(Graph *graph, char *name1, char *name2, int flag_t){
	Node *ptr = graph->list;
        Node *node1;
        Node *node2;
        init_find(graph, name1);
        int flag = 0;
        for (int i = 0; i < graph->size; i++){
                if (strcmp(ptr->name, name1) == 0){
                        node1 = ptr;
                        flag++;
                }
                if (strcmp(ptr->name, name2) == 0){
                        node2 = ptr;
                        flag++;
                }
                if (flag == 2) break;
                ptr = ptr->next;
        }
	find_path(graph, node1);
	if (flag_t == 1)
		if (print_BFS(node1, node2) == 0) return 0;
        return 1;
}

int T_Find_min_spanning_tree(Graph *graph, Graph *tree, char *name){
	Node *node1;
	Node *node = graph->list;
	for (int i = 0; i < graph->size; i++){
                if (strcmp(node->name, name) == 0){
                        node1 = node;
                        break;
                }
		node = node->next;
	}
	init_BFS(graph, node1->name);
	List *Q = newlist();
        list_put(Q, node1);
        find_BFS(Q);
        free(Q);
	node = graph->list;
	for (int j = 0; j < graph->size; j++){
		T_Add_node(tree, node->name, node->x, node->y);
		node = node->next;
	}
	node = graph->list;
	for (int j = 1; j < graph->size; j++){
		if (node1 == node) node = node->next;
                if (node->pred != NULL) T_Add_edge(tree, node->name, node->pred->name);
                node = node->next;
        }
        return 1;
}

int T_Timing(Graph *graph, int n, int var){
	int q, flag = 0, first, last, j, time = 0;
	if (var == 3){
		first = clock();
		T_Find_bridges(graph, flag);
		last = clock();
		printf("\nnumber of nodes = %d, time = %d\n", n, last - first);
		return 1;
	}
	Node *node1;
	Node *node2;
        node1 = graph->list;
        for (int i = 0; i < graph->size; i++){
		node2 = graph->list;
		q = rand() % graph->size;
		for (j = 0; j < q; j++)
			node2 = node2 -> next;
		first = clock();
		if (var == 1)
                	T_Breadth_First_Search(graph, node1->name, node2->name, flag);
		else T_Find_min_path(graph, node1->name, node2->name, flag);
		last = clock();
		time += last - first;
		node1 = node1->next;
        }
	printf("\nnumber of nodes = %d, time = %d\n", n, time);
        return 1;
}

char *new_name(){
	char *name = (char *)calloc(15, sizeof(char));
	if (name == NULL) return 0;
	return name;
}

int T_Random(Graph *graph, int n){
	int q, s;
	char *name1;
	char *name2;
	int x, y;
	Node *node;
	for (int z = 0; z < n; z++){
		name1 = (char *)calloc(15, sizeof(char));
		if (name1 == 0) return 0;
		s = rand() % 10;
		for (int r = 0; r < s + 1; r++){
			name1[r] = (rand() % 26) + 'A';
		}
		x = rand() % 100;
		y = (rand() * rand()) %100;
		if (T_Add_node(graph, name1, x, y) == 0) return 0;
	}
	for (int i = 0; i < n - 1; i++){
		node = graph->list;
		for (int w = 0; w < i; w++)
			 if (node->next != NULL) node = node->next;
		name1 = node->name;
		q = rand() % (n - i);// кол-во ребер у данной вершины
		for (int j = 0; j < q; j++){
			if (node->next != NULL) node = node->next;
			name2 = node->name;
			if (strcmp(name1, name2) == 0) name1 = graph->list->name;
			if (rand() % 2 > 0)
				if (T_Add_edge(graph, name1, name2) == 0) return 0;
		}
	}
        return 1;
}

int file(Graph *graph){
	FILE *in;
        in = fopen("filein.txt", "r");
        if(in == NULL){
                printf("Файл не найден\n");
                return 0;
        }
	int size, edges;
	char *name;
	char *name2;
	int x, y;
	fscanf(in, "%d", &size);
	for (int i = 0; i < size; i++){
		name = (char *)calloc(15, sizeof(char));
		fscanf(in, "%s", name);
		fscanf(in, "%d", &x);
		fscanf(in, "%d", &y);
		T_Add_node(graph, name, x, y);
	}
	fscanf(in, "%d", &edges);
	for (int i = 0; i < edges; i++){
                name = (char *)calloc(15, sizeof(char));
                name2 = (char *)calloc(15, sizeof(char));
                fscanf(in, "%s", name);
                fscanf(in, "%s", name2);
                T_Add_edge(graph, name, name2);
        }
	fclose(in);
	return 1;
}

int file_end(Graph *graph){
	FILE *in;
        in = fopen("filein.txt", "w");
        if(in == NULL){
                printf("Файл не найден\n");
                return 0;
        }
        int edges, size = graph->size;
	Node *node = graph->list;
	Edge *edge;
        fprintf(in, "%d\n", size);
        for (int i = 0; i < size; i++){
                fprintf(in, "%s\n", node->name);
                fprintf(in, "%d\n", node->x);
                fprintf(in, "%d\n", node->y);
                node = node->next;
        }
	node = graph->list;
	edges = 0;
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
        fprintf(in, "%d\n", edges);
        for (int i = 0; i < edges; i++){
		while (edge == NULL){
                	while (node->list == NULL)
				node = node->next;
			edge = node->list;
		}
		fprintf(in, "%s\n", node->name);
                fprintf(in, "%s\n", edge->end->name);
		edge = edge->next;
        }
	fclose(in);
        return 1;
}
