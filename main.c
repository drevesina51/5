#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"

int dialog(const char *msgs[], int N) {
        char *errmsg = "";
        int rc;
        int i, n;
        do{
                puts(errmsg);
                errmsg = "\nYou are wrong. Repeate, please!";
                for(i = 0; i < N; ++i)
                        puts(msgs[i]);
                puts("Make your choice: --> ");
                n = scanf("%d", &rc);
		if (n == EOF) return 0;
                if(n == 0)
                        rc = 0;
        } while(rc < 0 || rc >= N);
        return rc;
}

int main(){
        Graph *graph = (Graph *)calloc(1, sizeof(Graph)); // создание пустого графа
        if(graph == NULL) {
                   printf("Error try alloc\n");
                   return 0;
        }
        graph->size = 0;
	graph->list = NULL;
	srand(time(NULL));
        const char *msgs[] = {"0. Quit", "1. Add node", "2. Add edge", "3. Delete node", "4. Delete edge", "5. Show", "6. Breadth First Search",
				 "7. Find min path", "8. Find min spanning tree", "9. Timing", "10. Random", "11. Graphviz", "12. Find bridges & vertex_cut"};
        const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
        int dialog(const char *msgs[], int);
        int (*fptr[])(Graph *) = {NULL, D_Add_node, D_Add_edge, D_Delete_node, D_Delete_edge, D_Show, D_Breadth_First_Search,
				D_Find_min_path, D_Find_min_spanning_tree, D_Timing, D_Random, D_Graphviz, D_Find_bridges};
        int rc;
//	file(graph);
        while(rc = dialog(msgs, NMsgs))
                if(!fptr[rc](graph)) // вызов выбранной диалоговой функции
                  break;
        printf("End.\n");
//	file_end(graph);
	delGraph(graph);
	return 0;
}
