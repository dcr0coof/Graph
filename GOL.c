#include <stdio.h>
#include <stdlib.h>


typedef struct Glist_node {
    int data;
    int weight;
    struct Glist_node* next;
} Glist_node;

typedef struct Headon {
    Glist_node* head;
} Headon;

typedef struct Graph {
    int id;
    int V;
    int E;
    Headon* next_v;
} Graph;



Graph* creat_graph(int v, int identify) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->id = identify;
    graph->V = v;
    graph->E = 0;
    graph->next_v = (Headon*)malloc(v * sizeof(Headon)); 

    for (int i = 0; i < v; i++) {
        graph->next_v[i].head = NULL;
    }
    return graph;
}

Glist_node* creat_newNode(int data, int weight) {
    Glist_node* new_node = (Glist_node*)malloc(sizeof(Glist_node));
    new_node->data = data;
    new_node->weight = weight;
    new_node->next = NULL;
    return new_node;
}

void insert(int begin, int weight, int end, Graph* graph) {
    Glist_node* p = creat_newNode(end, weight);
    p->next = graph->next_v[begin].head;
    graph->next_v[begin].head = p;

    if (!graph->id) {
        Glist_node* q = creat_newNode(begin, weight);
        q->next = graph->next_v[end].head;
        graph->next_v[end].head = q;
    }

    graph->E++;
}

int count_edges(Graph* graph) {
    return graph->id ? graph->E : graph->E / 2;
}

void print_graph(Graph* graph) {
    for (int v = 0; v < graph->V; ++v) {
        Glist_node* p = graph->next_v[v].head;
        printf("Vertex %d: ", v);
        while (p) {
            printf("-> %d (weight: %d) ", p->data, p->weight);
            p = p->next;
        }
        printf("\n");
    }
}

void Prim(Graph* graph) {
    int selected[100] = { 0 };
    int edges_in_mst[100] = { 0 };
    int total_weight = 0;
    selected[0] = 1; 

    printf("Edges in the Minimum Spanning Tree:\n");

    for (int i = 0; i < graph->V - 1; i++) {
        int min_weight = INT_MAX;
        int u = -1, v = -1;

        // 查找最小权重边
        for (int j = 0; j < graph->V; j++) {
            if (selected[j]) {
                Glist_node* p = graph->next_v[j].head;
                while (p) {
                    if (!selected[p->data] && p->weight < min_weight) {
                        min_weight = p->weight;
                        u = j;
                        v = p->data;
                    }
                    p = p->next;
                }
            }
        }

        if (u != -1 && v != -1) {
            selected[v] = 1; // 标记新顶点
            total_weight += min_weight;
            printf("%d -- %d --> %d\n", u, min_weight, v);
            edges_in_mst[i] = min_weight; // 记录边的信息
        }
    }

    printf("\nTotal weight of MST: %d\n", total_weight);
}

void resorte(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        Glist_node* p = graph->next_v[i].head;

        if (p == NULL) continue; // 如果链表为空，跳过

        Glist_node* sorted_head = NULL; // 新链表的头指针

        while (p != NULL) {
            Glist_node* min_node = p;
            Glist_node* min_prev = NULL;
            Glist_node* current = p;
            Glist_node* prev = NULL;

            // 找到最小权重的节点
            while (current != NULL) {
                if (current->weight < min_node->weight) {
                    min_node = current;
                    min_prev = prev;
                }
                prev = current;
                current = current->next;
            }

            // 从原链表中移除最小节点
            if (min_prev != NULL) {
                min_prev->next = min_node->next;
            }
            else {
                // min_node是头节点
                p = p->next;
            }

            // 插入到新链表的头部
            min_node->next = sorted_head;
            sorted_head = min_node;
        }

        // 将已排序链表赋值回原链表
        graph->next_v[i].head = sorted_head;
    }

    print_graph(graph);
}



//void resorte(Graph* graph) {
//
//    for (int i = 0; i < graph->V; i++) {
//        Glist_node* p = graph->next_v[i].head;
//        Glist_node* q = p;
//
//        int MIN_W = q->weight ;
//        p = p->next;
//
//        while (q) {
//            if (p->weight<MIN_W) {
//
//                MIN_W = p->weight;
//                q->next = p->next;
//                p->next = graph->next_v[i].head->next;
//                graph->next_v[i].head->next = p;
//                
//            }
//            q = q->next;
//            p = p->next;
//
//        }
//    }
//  
//    print_graph(graph);
//}


int main() {
    int V, E, ID;
    printf("请输入顶点集大小，边集大小以及图的种类：");
    scanf_s("%d %d %d", &V, &E, &ID);

    Graph* graph = creat_graph(V, ID);
    printf("图已经成功创建!\n");

    for (int i = 0; i < E; i++) {
        int begin, end, weight;
        printf("输入边%d的起止顶点以及权重：",i);
        scanf_s("%d %d %d", &begin, &end, &weight);
        insert(begin, weight, end, graph);
    }

    print_graph(graph); 
    Prim(graph); 
    resorte(graph);

    return 0;
}
